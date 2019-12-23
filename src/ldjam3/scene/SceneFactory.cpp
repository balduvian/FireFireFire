
#include "SceneFactory.h"

namespace FFF {
	SceneFactory::SceneFactory(Assets* sceneAssets, std::function<Scene*(GameState*, Assets*)> factory)
	: sceneAssets(sceneAssets), factory(factory), scenePointer(nullptr) {}

	Scene* SceneFactory::create(GameState* gameState) {
		scenePointer = factory(gameState, sceneAssets);
		return scenePointer;
	}

	Assets* SceneFactory::getAssets() {
		return sceneAssets;
	}

	void SceneFactory::destroy() {
		delete scenePointer;
	}

}
