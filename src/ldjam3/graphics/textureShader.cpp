
#include "textureShader.h"

namespace FFF {
	TextureShader::TextureShader() : Shader("res/shaders/texture/vert.glsl", "res/shaders/texture/frag.glsl") {};

	void TextureShader::getUniforms() {
		colorLoc = getUniform("inColor");
		texModifLoc = getUniform("texModif");
	}

	void TextureShader::giveParams(f32 r, f32 g, f32 b, f32 a, f32 texModif[]) {
		giveVector4(colorLoc, r, g, b, a);
		giveVector4(texModifLoc, texModif);
	}
}
