
#include "GL/glew.h"
#include "GL/gl.h"

#include "png.h"

#include "texture.h"

namespace FFF {
	float Texture::tileValues[4]{ 1, 1, 0, 0 };
	float Texture::defaultTileValues[4]{ 1, 1, 0, 0 };

	/* loading */

	/// this will be a regular texture
	Texture::Texture(const char* path)
	: Resource(true), assetPath(path), assetImage(), width(), height(), texture() {}

	void Texture::customGather() {
		assetImage = std::make_unique<Image1D>(assetPath);

		width = assetImage->getWidth();
		height = assetImage->getHeight();
	}

	void Texture::customProcess() {
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);

		bind();

		// set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//auto skek = new u8[16] {2, 255, 87, 126, 45, 62, 0, 203, 233, 0, 0, 78, 125, 34, 255, 9};

		// load texture      assetImage->getPixels()
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, assetImage->getPixels());
	}

	void Texture::customDiscard() {
		assetImage = 0;
	}

	void Texture::customUnload() {
		glDeleteTextures(1, &texture);
	}

	/* use */

	void Texture::bind() {
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void Texture::bind(int slot) {
		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	int Texture::get() {
		return texture;
	}

	Texture::~Texture() {
		unload();
	}

}
