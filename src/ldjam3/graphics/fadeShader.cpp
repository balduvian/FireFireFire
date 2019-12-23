
#include "fadeShader.h"

namespace FFF {
	FadeShader::FadeShader() : Shader("res/shaders/fade/vert.glsl", "res/shaders/fade/frag.glsl") {};

	void FadeShader::getUniforms() {
		colorLoc = getUniform("inColor");
		texModifLoc = getUniform("texModif");
		planeLoc = getUniform("plane");
	}

	void FadeShader::givePlane(f32 px, f32 py, f32 pz, f32 pw) {
		giveVector4(planeLoc, px, py, pz, pw);
	}

	void FadeShader::giveParams(f32 r, f32 g, f32 b, f32 a, f32 texModif[]) {
		giveVector4(colorLoc, r, g, b, a);
		giveVector4(texModifLoc, texModif);
	}
}
