
#ifndef FFF_TILEGRID
#define FFF_TILEGRID

#include "texture.h"

#include "../types.h"

namespace FFF {
	class TileGrid : public Texture {
	private:
		u32 tilesWide;
		u32 tilesTall;

		f32 widthFraction;
		f32 heightFraction;

	public:
		TileGrid(const char* path, u32 tilesWide, u32 tilesTall);
		TileGrid(const char* path, u32 tilesWide);

		void customProcess();

		f32* getSheet(u32 x, u32 y);
		f32* getSheet(u32 x);

	};

}

#endif
