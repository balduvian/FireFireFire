
#ifndef FFF_FADESHADER
#define FFF_FADESHADER

#include "../engine/shader.h"
#include "../Types.h"

namespace FFF {
	class FadeShader : public Shader {
	private:
		i32 colorLoc;
		i32 texModifLoc;
		i32 planeLoc;

	public:
		FadeShader();

		void getUniforms();

		void givePlane(f32, f32, f32, f32);

		void giveParams(f32, f32, f32, f32, f32[]);
	};
}

#endif