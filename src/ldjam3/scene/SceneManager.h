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

#ifndef FFF_SCENE_MANAGER
#define FFF_SCENE_MANAGER

#include "../load/AssetsManager.h"
#include "../Types.h"
#include "Scene.h"
#include "SceneFactory.h"
#include "../load/loadScreen.h"
#include "../load/gameState.h"
#include "../engine/window.h"

namespace FFF {
	class SceneManager {
		private:
			constexpr static i32 UPDATE_MODE_LOADING = 0;
			constexpr static i32 UPDATE_MODE_NORMAL = 1;

			i32 updateMode;

			AssetsManager* assetsManager;
			GameState* gameState;
			Input* input;

			Scene* currentScene;
			SceneFactory* currentSceneFactory;
			SceneFactory** scenes;

			LoadScreen* currentLoadScreen;
			LoadScreen** loadScreens;

		public:
			SceneManager(GameState*, Input*, AssetsManager*, SceneFactory** scenes, LoadScreen** loadScreens);

			void start(SwitchFlags initial);

			void update(Timing* timing);
	};
}

#define FFF_SCENE_MANAGER_FORWARD
#endif // FFF_SCENE_MANAGER
