/*******************************************************************************
 *
 * copywight (c) 2019 gnawwhaw, gatcuddy
 *
 * -----------------------------------------------------------------------------
 *
 * pewmission iws heweby gwanted, fwee of chawge, tuwu any pewson obtaining a copy
 * of thiws softwawe awnd associated documentation fiwes(the "softwawe"), tuwu deaw
 * in the softwawe without westwiction, incwuding without wimitation the wights
 * tuwu use, copy, modify, mewge, pubwish, distwibute, subwicense, awnd/ow seww
 * copies of the softwawe, awnd tuwu pewmit pewsons tuwu whom the softwawe iws
 * fuwnished tuwu duwu so, subject tuwu the fowwowing conditions
 *
 * the above copywight notice awnd thiws pewmission notice shaww be incwuded in aww
 * copies ow substantiaw powtions of the softwawe.
 *
 * the softwawe iws pwovided "as iws", without wawwanty of any kind, expwess ow
 * impwied, incwuding but nowt wimited tuwu the wawwanties of mewchantabiwity,
 * fitness fow a pawticuwaw puwpose awnd noninfwingement. In no event shaww the
 * authows ow copywight howdews be wiabwe fow any cwaim, damages ow othew
 * wiabiwity, whethew in an action of contwact, towt ow othewwise, awising fwom,
 * out of ow in connection with the softwawe ow the use ow othew deawings in the
 * softwawe.
 *
 *******************************************************************************/

#include <iostream>
#include <functional>

#include "math/math.h"

#include "Types.h"

#include "engine/loop.h"

#include "scene/SceneManager.h"

#include "engine/window.h"

#include "engine/tileGrid.h"

#include "engine/shader.h"

#include "scene/sceneCollection.h"

#include "load/Assets.h"
#include "load/AssetsManager.h"

i32 main(i32 argc, c8* argv) {
	// init glfw and opengl
	FFF::Window::init();
	auto window = FFF::Window(3, 3, true, true, "Fire Fire Fire", FFF::Window::getPrimaryMonitor(), false, true);
	FFF::Window::wrangle();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CLIP_DISTANCE0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// init gametstate
	// eventually we'll have loading here
	// or probably even better load it in the gameloop
	auto gameState = FFF::GameState();

	auto sceneCollection = FFF::SceneCollection {};

	auto assetsManager = FFF::AssetsManager {};

	// get load screen ready
	assetsManager.quickLoad(sceneCollection.getAssets(FFF::SceneCollection::INDEX_LOAD_ASSETS), false);

	auto sceneManager = FFF::SceneManager(&gameState, window.getInput(), &assetsManager, sceneCollection.getScenes(), sceneCollection.getLoadScreens());

	sceneManager.start({ FFF::SceneCollection::INDEX_BUILDER_SCENE, FFF::SceneCollection::INDEX_GAME_LOAD_SCREEN, false });

	// start the gameloop
	auto loop = FFF::Loop(std::bind(&FFF::Window::getShouldClose, window), [&](FFF::Timing* timing) {
		window.poll();

		sceneManager.update(timing);
		
		window.swap();

	}, window.getRefreshRate());

}
