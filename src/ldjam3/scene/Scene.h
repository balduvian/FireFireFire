/*******************************************************************************
 *
 * Copyright (c) 2019 Gnarwhal, Gatcuddy
 *
 * -----------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#ifndef FFF_SCENE
#define FFF_SCENE

#include "../Types.h"
#include "../load/gameState.h"
#include "../load/resource.h"
#include "../engine/loop.h"
#include "../engine/window.h"

#include "../load/Assets.h"

namespace FFF {
	struct SwitchFlags {
		i32 sceneToSwitch;
		i32 loadScreenToUse;
		bool unloadPrevious;
	};

	class Scene {
		private:
			SwitchFlags switchFlags;
			
		protected:
			void switchScene(i32 scene, i32 loadScren, bool unload);

			virtual void resized(u32 width, u32 height) = 0;

			virtual void update(Input* input, Timing* time) = 0;

			virtual void render() = 0;

			Assets* sceneAssets;

		public:
			static constexpr i32 NO_SWITCH = -1;

			Scene(GameState* gameState, Assets* sceneAssets);

			SwitchFlags getSceneSwitch();

			friend class SceneManager;
	};
}

#define FFF_SCENE_FORWARD
#endif // SPARK_SCENE
