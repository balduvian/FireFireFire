
#ifndef FFF_GAME_LOAD_SCREEN
#define FFF_GAME_LOAD_SCREEN

#include "../../utils/aspect.h"
#include "../../graphics/rect.h"
#include "../../graphics/colorShader.h"
#include "../../load/loadScreen.h"
#include "../../engine/camera.h"

namespace FFF {
	class GameLoadScreen : public LoadScreen {
	private:
		Camera camera;
		Aspect aspect;

		Rect* rect;
		ColorShader* colorShader;

	public:
		GameLoadScreen(Assets* loadAssets);

		void resized(u32 width, u32 height);

		void render(i32 outOf, i32 total);

	};

}

#endif
