#pragma once

#ifndef DJAM3_BUILDERSCENE
#define DJAM3_BUILDERSCENE

#include "../Scene.h"

#include "../../graphics/rect.h"
#include "../../engine/texture.h"
#include "../../graphics/textureShader.h"
#include "../../graphics/colorShader.h"
#include "../../graphics/fadeShader.h"
#include "../../engine/camera.h"
#include "../../engine/tileGrid.h"
#include "../../Types.h"
#include "../../blocks/map.h"
#include "../../utils/aspect.h"
#include "../../blocks/player.h"
#include "../../blocks/fire.h"

namespace FFF {
	class GameScene : public Scene {
	private:
		f32 screenWidth, screenHeight;

		f32 centerX;
		f32 centerY;

		uptr<Player> player;
		uptr<FireHolder> fires;

		TileGrid* blockTexture;
		TileGrid* fireTexture;
		TextureShader* textureShader;
		Rect* rect;
		Map* level1;
		TileGrid* playerTexture;
		GateShader* gateShader;

		Camera camera;
		Aspect aspect;

		Map* currentLevel;

		void startLevel(Map* level);

	protected:
		void resized(u32, u32);

		void update(Input*, Timing*);

		void render();

	public:
		GameScene(GameState* gameState, Assets* gameAssets);

	};
}

#endif