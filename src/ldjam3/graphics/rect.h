
#ifndef FFF_RECT
#define FFF_RECT

#include "../engine/vao.h"

namespace FFF {
	/// a texture enabled rect with
	/// a 0,0 in the bottom left corner
	class Rect : public VAO {
	public:
		Rect();
	};

	/// a texture enabled rect with 
	/// a 0,0 in the bottom center
	class CardRect : public VAO {
	public:
		CardRect();
	};

}

#endif
