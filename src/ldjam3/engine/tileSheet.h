
#ifndef FFF_TILESHEET
#define FFF_TILESHEET

#include "texture.h"

#include "../types.h"

namespace FFF {
	class TileSheet : public Texture {
	private:
		u32 numPositions;
		const i32* inputPositions;

		f32* calculatedPositions[4];

	public:
		TileSheet(const char* path, const u32 numPositions, const i32* positions);

		void customProcess();
		void customUnload();

		f32* getSheet(u32 tile);

		~TileSheet();
	};
}

#endif