
#ifndef FFF_GATESHADER
#define FFF_GATESHADER

#include "../engine/shader.h"
#include "../Types.h"

namespace FFF {
	class GateShader : public Shader {
	private:
		i32 colorLoc;
		i32 texModifLoc;

	public:
		GateShader();

		void getUniforms();

		void giveParams(f32, f32, f32, f32, f32[]);
	};
}

#endif
