#pragma once

#ifndef FFF_GAMESTATE
#define FFF_GAMESTATE

#include "../graphics/rect.h"
#include "../graphics//textureShader.h"

namespace FFF {
	class GameState {
	private:
		Rect rect;
		TextureShader textureShader;

	public:
		GameState();
	};
}

#endif
