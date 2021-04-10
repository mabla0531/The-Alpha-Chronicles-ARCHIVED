#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) {
	this->window = window;
	gameCameraOffsetX = 0;
	gameCameraOffsetY = 0;

	player = new Player(&testMap, &entities);
	Tree* tree = new Tree();

	tree->setX(300);
	tree->setY(300);

	entities.push_back(player);
	entities.push_back(tree);
}

GameState::~GameState() {
	
}

void GameState::tickGameCamera() {
	gameCameraOffsetX = (int)(player->getX() - (window->getSize().x / 2));
	gameCameraOffsetY = (int)(player->getY() - (window->getSize().y / 2));

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

	//sort Entities by Y value to give a 3d look
	std::sort(entities.begin(), entities.end(), [](Entity* e1, Entity* e2) {
		return e1->getY() < e2->getY();
	});

	for (int e = 0; e < entities.size(); e++) {
		entities.at(e)->tick();
	}
}

void GameState::render() {
	testMap.render(window, gameCameraOffsetX, gameCameraOffsetY);
	
	for (int e = 0; e < entities.size(); e++) {
		entities.at(e)->render(window, gameCameraOffsetX, gameCameraOffsetY);
	}
}

void GameState::render(sf::RenderWindow* window) { //for rendering to an alternate window
	testMap.render(window, gameCameraOffsetX, gameCameraOffsetY);

	for (int e = 0; e < entities.size(); e++) {
		entities.at(e)->render(window, gameCameraOffsetX, gameCameraOffsetY);
	}
}
