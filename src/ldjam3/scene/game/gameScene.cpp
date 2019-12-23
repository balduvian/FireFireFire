
#include <iostream>
#include <cmath>

#include "gameScene.h"
#include "../sceneCollection.h"
#include <algorithm>
#include "../../blocks/ccd.h"

namespace FFF {
	void GameScene::resized(u32 width, u32 height) {
		aspect.update(width, height);

		screenWidth = aspect.getGameWidth();
		screenHeight = aspect.getGameHeight();

		glViewport(aspect.getLeft(), aspect.getTop(), aspect.getWidth(), aspect.getHeight());

		camera.setOrtho(aspect.getGameWidth(), aspect.getGameHeight());
	}

	void GameScene::update(Input* input, Timing* timing) {
		// update player if she's around
		if (player) {
			player->update(timing, input, currentLevel, fires.get());

			centerX = player->getX() + 0.5_f32;
			centerY = player->getY() + 0.5_f32;

			if (player->shouldCreateFire()) {
				auto position = player->getFirePos();
				fires->add(Fire(position.getX(), position.getY(), 1));
			}
		}

		//reset all gates
		// set all first bits to 0
		auto numgates = currentLevel->getNumGates();
		auto gateCheck = new bool[numgates] {};

		for (auto i = 0; i < numgates; ++i) {
			auto receiverX = currentLevel->getReceiverX(i);
			auto receiverY = currentLevel->getReceiverY(i);

			auto gateX = currentLevel->getGateX(i);
			auto gateY = currentLevel->getGateY(i);

			currentLevel->getBlock(receiverX, receiverY).state &= 0b01111111;
			currentLevel->getBlock(gateX, gateY).state &= 0b01111111;
		}

		fires->iterateKill([this, timing, input, gateCheck, numgates](Fire* fire) {
			fire->update(timing, input);

			if (fire->getShouldDie()) {
				return true;
			} else {
				/// fire CCD

				auto end = Vector2f(fire->getX() + 0.5_f32, fire->getY() + 0.5_f32);

				for (auto i = 0; i < numgates; ++i) {
					if (!gateCheck[i]) {
						auto receiverX = currentLevel->getReceiverX(i);
						auto receiverY = currentLevel->getReceiverY(i);

						auto gateX = currentLevel->getGateX(i);
						auto gateY = currentLevel->getGateY(i);

						auto start = Vector2f(receiverX + 0.5_f32, receiverY + 0.5_f32);

						// which direction we are moving determines what we can collide with
						auto movingRight = end.getX() > start.getX();
						auto movingUp = end.getY() > start.getY();
						auto movingLeft = end.getX() < start.getX();
						auto movingDown = end.getY() < start.getY();

						auto boundingBox = BoundingBox(start, end);

						auto checkRight = [this, start, end, boundingBox]() {
							for (auto i = boundingBox.minX; i <= boundingBox.maxX; ++i) {
								for (auto j = boundingBox.minY; j <= boundingBox.maxY; ++j) {
									if (currentLevel->getRightLine(i, j) && horizontalTest(start, end, i + 1, j, j + 1))
										return true;
								}
							}
							return false;
						};
						auto checkLeft = [this, start, end, boundingBox]() {
							for (auto i = boundingBox.minX; i <= boundingBox.maxX; ++i) {
								for (auto j = boundingBox.minY; j <= boundingBox.maxY; ++j) {
									if (currentLevel->getLeftLine(i, j) && horizontalTest(start, end, i, j, j + 1))
										return true;
								}
							}
							return false;
						};
						auto checkUp = [this, start, end, boundingBox]() {
							for (auto i = boundingBox.minX; i <= boundingBox.maxX; ++i) {
								for (auto j = boundingBox.minY; j <= boundingBox.maxY; ++j) {
									if (currentLevel->getTopLine(i, j) && verticalTest(start, end, j + 1, i, i + 1))
										return true;
								}
							}
							return false;
						};
						auto checkDown = [this, start, end, boundingBox]() {
							for (auto i = boundingBox.minX; i <= boundingBox.maxX; ++i) {
								for (auto j = boundingBox.minY; j <= boundingBox.maxY; ++j) {
									if (currentLevel->getBottomLine(i, j) && verticalTest(start, end, j, i, i + 1))
										return true;
								}
							}
							return false;
						};

						// if we hit a wall
						if (
							!((movingRight && checkRight())
							|| (movingLeft && checkLeft())
							|| (movingUp && checkUp())
							|| (movingDown && checkDown()))
						) {
							// set first bit to 1
							currentLevel->getBlock(receiverX, receiverY).state |= 0b10000000;
							currentLevel->getBlock(gateX, gateY).state |= 0b10000000;

							gateCheck[i] = true;
						}
					}
				}
			}

			return false;
		});
		
		delete[] gateCheck;

		// move camera to be in the center of where we want
		camera.transform.translation.setXY(centerX - camera.width / 2, centerY - camera.height / 2);
		camera.update();

		// TODO update 
	}

	void GameScene::render() {
		// black bars
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	
		auto viewW = camera.width / 2;
		auto viewH = camera.height / 2;

		auto left = (i32)floor(centerX - viewW);
		auto right = (i32)ceil(centerX + viewW);
		auto down = (i32)floor(centerY - viewH);
		auto up = (i32)ceil(centerY + viewH);

		currentLevel->render(left, down, right, up, &camera, rect, textureShader, blockTexture, gateShader);
		
		fires->iterate([this](Fire* fire) {
			fire->render(&camera, rect, textureShader, fireTexture);
		});

		if (player) {
			player->render(&camera, rect, textureShader, playerTexture);
		}
	}

	void GameScene::startLevel(Map* level) {
		// set it as current
		currentLevel = level;

		// and place the player
		player = 0;
		player = std::make_unique<Player>(currentLevel->getSpawnX(0), currentLevel->getSpawnY(0) - 1);

		// place the fires!
		fires = 0;
		fires = std::make_unique<FireHolder>(currentLevel->getMaxFires());
		auto numFires = currentLevel->getNumSpawns();

		for (auto i = 0; i < numFires; ++i) {
			fires->add(Fire(currentLevel->getSpawnX(i), currentLevel->getSpawnY(i), currentLevel->getSpawnStrength(i)));
		}
	}

	GameScene::GameScene(GameState* gameState, Assets* gameAssets)
		: Scene(gameState, gameAssets), camera(), aspect(16, 9, 16, 9), screenWidth(0), screenHeight(0), fires() {

		camera.transform.scale = { 1, 1 };
		camera.transform.translation = { 0.f, 0.f };

		blockTexture = (TileGrid*)gameAssets->loads[SceneCollection::INDEX_GAME_ASSETS_BLOCK_TEXTURE];
		fireTexture = (TileGrid*)gameAssets->loads[SceneCollection::INDEX_GAME_ASSETS_FIRE_TEXTURE];
		textureShader = (TextureShader*)gameAssets->loads[SceneCollection::INDEX_GAME_ASSETS_TEXTURE_SHADER];
		rect = (Rect*)gameAssets->loads[SceneCollection::INDEX_GAME_ASSETS_RECT];
		level1 = (Map*)gameAssets->loads[SceneCollection::INDEX_GAME_ASSETS_LEVEL1];
		playerTexture = (TileGrid*)gameAssets->loads[SceneCollection::INDEX_GAME_ASSETS_PLAYER_TEXTURE];
		gateShader = (GateShader*)gameAssets->loads[SceneCollection::INDEX_GAME_ASSETS_GATE_SHADER];

		startLevel(level1);
	}
}
