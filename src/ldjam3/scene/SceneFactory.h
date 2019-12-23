
#ifndef FFF_SCENE_FACTORY
#define FFF_SCENE_FACTORY

#include "Scene.h"
#include "../load/Assets.h"

namespace FFF {
	class SceneFactory {
	private:
		Scene* scenePointer;
		Assets* sceneAssets;

		std::function<Scene*(GameState*, Assets*)> factory;
		
	public:
		SceneFactory(Assets* sceneAssets, std::function<Scene*(GameState*, Assets*)> factory);

		Scene* create(GameState* gameState);
		Assets* getAssets();

		void destroy();
	};

}

#endif
