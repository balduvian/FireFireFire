#pragma once

#ifndef FFF_COLORSHADER
#define FFF_COLORSHADER

#include "../engine/shader.h"
#include "../Types.h"

namespace FFF {
	class ColorShader : public Shader {
	private:
		i32 colorLoc;

	public:
		ColorShader();

		void getUniforms();

		void giveColor(f32, f32, f32, f32);
	};
}

#endif