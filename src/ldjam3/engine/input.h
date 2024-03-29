
#include "window.h"

#ifndef FFF_INPUT
#define FFF_INPUT

#include "GLFW/glfw3.h"
#include "../Types.h"

namespace FFF {
	class Input {
	public:
		constexpr static u32
			BUTTON_RELEASED  = 0x00,
			BUTTON_UNPRESSED = 0x01,
			BUTTON_PRESSED   = 0x02,
			BUTTON_HELD      = 0x03,
			BUTTON_REPEAT    = 0x04;

		u32 getKeyPressed(i32 key);
		bool getKeyDown(i32 key);

		f64 getCursorX();
		f64 getCursorY();

		u32 getMousePressed(i32 button);

		bool getResized();

		u32 getWidth();
		u32 getHeight();
		
		void update();

		friend class Window;

		f32 getScrollX();
		f32 getScrollY();

	private:
		Input();

		void keyPressedUpdate(i32 key, i32 scancode, i32 action, i32 mods);

		void mousePressedUpdate(i32 button, i32 action, i32 mods);

		void mouseMovedUpdate(f64 x, f64 y);

		void scrollUpdate(f64 scrollX, f64 scrollY);

		u32 keysPressed[GLFW_KEY_LAST + 1];
		u32 mousePressed[GLFW_MOUSE_BUTTON_LAST + 1];

		f64 cursorX;
		f64 cursorY;

		f64 scrollX;
		f64 scrollY;

		bool resized;

		u32 width;
		u32 height;
	};
}

#endif
