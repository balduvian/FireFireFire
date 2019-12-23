
#include "sceneCollection.h"

namespace FFF {
	Assets* SceneCollection::getAssets(u32 index) {
		return assets[index];
	}

	SceneFactory* SceneCollection::getScene(u32 index) {
		return scenes[index];
	}

	LoadScreen* SceneCollection::getLoadScreen(u32 index) {
		return loadScreens[index];
	}

	Assets** SceneCollection::getAssets() {
		return assets;
	}

	SceneFactory** SceneCollection::getScenes() {
		return scenes;
	}

	LoadScreen** SceneCollection::getLoadScreens() {
		return loadScreens;
	}

}
