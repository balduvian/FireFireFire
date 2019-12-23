
#ifndef FFF_LOADSCREEN
#define FFF_LOADSCREEN

#include "Assets.h"

namespace FFF {
	class LoadScreen {
	public:
		LoadScreen(Assets* loadAssets);

		virtual void resized(u32 width, u32 height) = 0;

		virtual void render(i32 outOf, i32 total) = 0;

	protected:
		Assets* loadAssets;

	};

}

#endif
