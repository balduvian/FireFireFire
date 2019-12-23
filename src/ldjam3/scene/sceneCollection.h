
#ifndef FFF_SCENE_COLLECTION
#define FFF_SCENE_COLLECTION

#include "../load/loadScreen.h"
#include "game/gameLoadScreen.h"
#include "../graphics/colorShader.h"
#include "../graphics/gateShader.h"
#include "game/gameScene.h"
#include "../engine/tileGrid.h"
#include "SceneFactory.h"
#include "../blocks/map.h"

namespace FFF {

	class SceneCollection {
	public:
		constexpr static u32 NUM_SCENES = 1;
		constexpr static u32 NUM_ASSETS = 2;
		constexpr static u32 NUM_LOAD_SCREENS = 1;

	/// ASSETS
	private:
		TileGrid blockTexture = { "res/blocks.png", 4, 4 };
		TileGrid fireTexture = { "res/fire.png", 4, 4 };
		TileGrid playerTexture = { "res/player.png", 4, 4 };

		TextureShader textureShader = {};
		ColorShader colorShader = {};
		GateShader gateShader = {};

		Rect rect {};

		Map level1 {"res/levels/level1.png"};

		constexpr static u32 NUM_LOAD_ASSETS = 2;
		Resource* assetList_lsa[NUM_LOAD_ASSETS] { &rect, &colorShader };
		Assets loadAssets {NUM_LOAD_ASSETS, assetList_lsa};

		constexpr static u32 NUM_GAME_ASSETS = 8;
		Resource* assetList_game[NUM_GAME_ASSETS] { &blockTexture, &fireTexture, &textureShader, &colorShader, &rect, &level1, &playerTexture, &gateShader };
		Assets gameAssets {NUM_GAME_ASSETS, assetList_game};

		Assets* assets[NUM_ASSETS] { &loadAssets, &gameAssets };

	/// LOAD SCREENS
	private:
		GameLoadScreen gameLoadScreen { &loadAssets };

		LoadScreen* loadScreens[NUM_LOAD_SCREENS] { &gameLoadScreen };

	/// SCENES
	private:
		SceneFactory gameSceneFactory{&gameAssets, [](GameState* gameState, Assets* assets) {
			return new GameScene(gameState, assets);
		}};

		SceneFactory* scenes[NUM_SCENES] { &gameSceneFactory };

	public:
		/// indices for assets
		constexpr static u32 INDEX_LOAD_ASSETS = 0;
		constexpr static u32 INDEX_GAME_ASSETS = 1;

		/// indices inside of load assets
		constexpr static u32 INDEX_LOAD_ASSETS_RECT = 0;
		constexpr static u32 INDEX_LOAD_ASSETS_COLOR_SHADER = 1;

		/// indices inside of game assets
		constexpr static u32 INDEX_GAME_ASSETS_BLOCK_TEXTURE = 0;
		constexpr static u32 INDEX_GAME_ASSETS_FIRE_TEXTURE = 1;
		constexpr static u32 INDEX_GAME_ASSETS_TEXTURE_SHADER = 2;
		constexpr static u32 INDEX_GAME_ASSETS_COLOR_SHADER = 3;
		constexpr static u32 INDEX_GAME_ASSETS_RECT = 4;
		constexpr static u32 INDEX_GAME_ASSETS_LEVEL1 = 5;
		constexpr static u32 INDEX_GAME_ASSETS_PLAYER_TEXTURE = 6;
		constexpr static u32 INDEX_GAME_ASSETS_GATE_SHADER = 7;

		/// indices for load screens
		constexpr static u32 INDEX_GAME_LOAD_SCREEN = 0;

		/// indices for scenes
		constexpr static u32 INDEX_BUILDER_SCENE = 0;

		Assets* getAssets(u32 index);
		SceneFactory* getScene(u32 index);
		LoadScreen* getLoadScreen(u32 index);

		Assets** getAssets();
		SceneFactory** getScenes();
		LoadScreen** getLoadScreens();
	};

}

#endif
