
#ifndef FFF_TEXTURESHADER
#define FFF_TEXTURESHADER

#include "../engine/shader.h"
#include "../Types.h"

namespace FFF {
	class TextureShader : public Shader {
	private:
		i32 colorLoc;
		i32 texModifLoc;
		
	public:
		TextureShader();

		void getUniforms();

		void giveParams(f32, f32, f32, f32, f32[]);
	};
}

#endif
