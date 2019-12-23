#include <iostream>

#include "colorShader.h"

namespace FFF {
	ColorShader::ColorShader() : Shader("res/shaders/color/vert.glsl", "res/shaders/color/frag.glsl") {};

	void ColorShader::getUniforms() {
		colorLoc = getUniform("inColor");
	}

	void ColorShader::giveColor(f32 r, f32 g, f32 b, f32 a) {
		giveVector4(colorLoc, r, g, b, a);
	}
}
