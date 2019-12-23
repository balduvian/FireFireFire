
#pragma once

#include "../image/image.h"

#include "../load/resource.h"

namespace FFF {
	class Texture : public Resource {
	public:
		Texture(const char*);

		static float defaultTileValues[4];

		void bind(int);
		void bind();

		int get();

		~Texture();

	protected:
		static float tileValues[4];

		virtual void customGather();
		virtual void customProcess();
		virtual void customDiscard();
		virtual void customUnload();

		u32 width;
		u32 height;

	private:
		const char* assetPath;
		std::unique_ptr<Image1D> assetImage;

		using pixel = unsigned char;
		unsigned int texture;
	};

}
