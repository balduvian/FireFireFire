
#include <iostream>

#include "../load/resource.h"

#include "SceneManager.h"

namespace FFF {
	SceneManager::SceneManager(GameState* gameState, Input* input, AssetsManager* assetsManager, SceneFactory** scenes, LoadScreen** loadScreens)
	: gameState(gameState), input(input), currentScene(nullptr), currentSceneFactory(nullptr), scenes(scenes), updateMode(UPDATE_MODE_LOADING),
		assetsManager(assetsManager), loadScreens(loadScreens), currentLoadScreen(*loadScreens) {}
	
	/// starts a scene
	/// you may use this as the initial start
	void SceneManager::start(SwitchFlags switchFlags) {
		updateMode = UPDATE_MODE_LOADING;

		// if we're unloading
		auto oldSceneFactory = currentSceneFactory;

		currentSceneFactory = scenes[switchFlags.sceneToSwitch];
		currentLoadScreen = loadScreens[switchFlags.loadScreenToUse];

		currentLoadScreen->resized(input->getWidth(), input->getHeight());

		// if unloading, place in previous scene's assets
		// this will error if you have no old scene and you attempt to unload precvious scene
		assetsManager->load(currentSceneFactory->getAssets(), false, switchFlags.unloadPrevious ? oldSceneFactory->getAssets() : nullptr, false);
	}

	/// updates and renders the current scene
	/// allows the scene update function to
	/// tell this to switch the scene
	void SceneManager::update(Timing* timing) {
		switch (updateMode) {
		case UPDATE_MODE_LOADING:
			if (input->getResized())
				currentLoadScreen->resized(input->getWidth(), input->getHeight());

			assetsManager->update();
			currentLoadScreen->render(assetsManager->getLoaded(), assetsManager->getTotal());

			// see if we are done loading
			if (assetsManager->getLoadMode() == AssetsManager::LOAD_MODE_DONE) {
				updateMode = UPDATE_MODE_NORMAL;

				// create the scene
				currentScene = currentSceneFactory->create(gameState);
				// resize the scene
				currentScene->resized(input->getWidth(), input->getHeight());
			}

			break;

		case UPDATE_MODE_NORMAL:
			// first resize the scene
			if (input->getResized())
				currentScene->resized(input->getWidth(), input->getHeight());

			currentScene->update(input, timing);
			currentScene->render();

			// check if we need to switch scenes
			auto sceneSwitch = currentScene->getSceneSwitch();

			if (sceneSwitch.sceneToSwitch != Scene::NO_SWITCH) {
				// destroy old scene
				currentSceneFactory->destroy();

				// and go to new scene
				start(sceneSwitch);
			}

			break;
		}
	}

}
