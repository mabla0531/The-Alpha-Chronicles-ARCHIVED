#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) {
	this->window = window;
	gameCameraOffsetX = 0;
	gameCameraOffsetY = 0;

	tree.setX(300);
	tree.setY(300);
}

GameState::~GameState() {
	
}

void GameState::tickGameCamera() {
	gameCameraOffsetX = player.getX() - (window->getSize().x / 2);
	gameCameraOffsetY = player.getY() - (window->getSize().y / 2);

	if (gameCameraOffsetX < 0) //make sure the game camera isn't rendering blank space
		gameCameraOffsetX = 0;
	if (gameCameraOffsetX + window->getSize().x > testMap.getWidth())
		gameCameraOffsetX = testMap.getWidth() - window->getSize().x;
	
	if (gameCameraOffsetY < 0) //same as above, but for Y axis
		gameCameraOffsetY = 0;
	if (gameCameraOffsetY + window->getSize().y > testMap.getHeight())
		gameCameraOffsetY = testMap.getHeight() - window->getSize().y;
}

void GameState::tick() {
	tickGameCamera();

	testMap.tick();
	player.tick();

	tree.tick();
}

void GameState::render() {
	testMap.render(window, gameCameraOffsetX, gameCameraOffsetY);
	player.render(window, gameCameraOffsetX, gameCameraOffsetY);

	tree.render(window, gameCameraOffsetX, gameCameraOffsetY);
}

void GameState::render(sf::RenderWindow* window) {
	testMap.render(window, gameCameraOffsetX, gameCameraOffsetY);
	player.render(window, gameCameraOffsetX, gameCameraOffsetY);

	tree.render(window, gameCameraOffsetX, gameCameraOffsetY);
}
