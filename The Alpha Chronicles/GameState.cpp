#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) {
	this->window = window;
	gameCameraOffsetX = 0;
	gameCameraOffsetY = 0;
}

GameState::~GameState() {
	
}

void GameState::tickGameCamera() {
	gameCameraOffsetX = player.getX() - (window->getSize().x / 2);
	gameCameraOffsetY = player.getY() - (window->getSize().y / 2);

	if (gameCameraOffsetX < 0)
		gameCameraOffsetX = 0;
	if (gameCameraOffsetX + window->getSize().x > testMap.getWidth())
		gameCameraOffsetX = testMap.getWidth() - window->getSize().x;
	
	if (gameCameraOffsetY < 0)
		gameCameraOffsetY = 0;
	if (gameCameraOffsetY + window->getSize().y > testMap.getHeight())
		gameCameraOffsetY = testMap.getHeight() - window->getSize().y;
}

void GameState::tick() {
	tickGameCamera();

	testMap.tick();
	player.tick();
}

void GameState::render() {
	testMap.render(window, gameCameraOffsetX, gameCameraOffsetY);
	player.render(window, gameCameraOffsetX, gameCameraOffsetY);
}

void GameState::render(sf::RenderWindow* window) {
	testMap.render(window, gameCameraOffsetX, gameCameraOffsetY);
	player.render(window, gameCameraOffsetX, gameCameraOffsetY);
}
