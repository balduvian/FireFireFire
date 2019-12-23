
#include "gameLoadScreen.h"
#include <iostream>
#include "../sceneCollection.h"

namespace FFF {
	GameLoadScreen::GameLoadScreen(Assets* loadAssets)
		: LoadScreen(loadAssets),
		rect((Rect*)loadAssets->loads[SceneCollection::INDEX_LOAD_ASSETS_RECT]),
		colorShader((ColorShader*)loadAssets->loads[SceneCollection::INDEX_LOAD_ASSETS_COLOR_SHADER]),
		camera(), aspect(32, 18, 32, 18)
	{}

	void GameLoadScreen::resized(u32 width, u32 height) {
		aspect.update(width, height);
		camera.setOrtho(aspect.getGameWidth(), aspect.getGameHeight());

		glViewport(aspect.getLeft(), aspect.getTop(), aspect.getWidth(), aspect.getHeight());
	}

	void GameLoadScreen::render(i32 outOf, i32 total) {
		// add black bars
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		// black background
		colorShader->enable(Transform::defaultModel, Transform::defaultProjview);
		colorShader->giveColor(0, 0, 0, 1);
		rect->render();

		// outline
		colorShader->enable(Transform::toModel(9, 6, 0, 14, 6), camera.getProjection());
		colorShader->giveColor(1, 1, 1, 1);
		rect->render();

		// inner black
		colorShader->enable(Transform::toModel(10, 7, 0, 12, 4), camera.getProjection());
		colorShader->giveColor(0, 0, 0, 1);
		rect->render();

		auto along = (f32)outOf / total;

		// innter white progress
		colorShader->enable(Transform::toModel(10, 7, 0, along * 12, 4), camera.getProjection());
		colorShader->giveColor(1, 1, 1, 1);
		rect->render();
	}

}
