
#include <GL/glew.h>

#include "rect.h"
#include "../Types.h"

namespace FFF {
	Rect::Rect() : VAO(
		GL_TRIANGLES,
		FFF::Attribute::createVertexAttribute(12, new f32[12] {
			0, 0, 0,
			0, 1, 0,
			1, 1, 0,
			1, 0, 0
		}),
		6, new u32[6] {
			0, 3, 2,
			0, 2, 1
		},
		1, new FFF::Attribute[1] {
			FFF::Attribute(2, 8, new f32[8] {
				0, 1,
				0, 0,
				1, 0,
				1, 1
			})
		}
	) {}

	CardRect::CardRect() : VAO(
		GL_TRIANGLES,
		FFF::Attribute::createVertexAttribute(12, new f32[12] {
			-.5, 0, 0,
			.5, 0, 0,
			.5, 1, 0,
			-.5, 1, 0
		}),
		6, new u32[6] {
			0, 1, 2,
			0, 2, 3
		},
		1, new FFF::Attribute[1] {
			FFF::Attribute(2, 8, new f32[8] {
				0, 1,
				1, 1,
				1, 0,
				0, 0
			})
		}
	) {}

}
