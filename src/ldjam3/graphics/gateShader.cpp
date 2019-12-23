
#include "gateShader.h"

namespace FFF {
	GateShader::GateShader() : Shader("res/shaders/gate/vert.glsl", "res/shaders/gate/frag.glsl") {};

	void GateShader::getUniforms() {
		colorLoc = getUniform("inColor");
		texModifLoc = getUniform("texModif");
	}

	void GateShader::giveParams(f32 r, f32 g, f32 b, f32 a, f32 texModif[]) {
		giveVector4(colorLoc, r, g, b, a);
		giveVector4(texModifLoc, texModif);
	}

}
