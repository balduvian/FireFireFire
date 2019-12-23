
#include "Scene.h"

namespace FFF {
	Scene::Scene(GameState* gameState, Assets* sceneAssets)
		: sceneAssets(sceneAssets), switchFlags({ NO_SWITCH, 0, false }) {
	}

	void Scene::switchScene(i32 scene, i32 loadScreen, bool unload) {
		switchFlags.sceneToSwitch = scene;
		switchFlags.loadScreenToUse = loadScreen;
		switchFlags.unloadPrevious = unload;
	}

	SwitchFlags Scene::getSceneSwitch() {
		return switchFlags;
	}
}
