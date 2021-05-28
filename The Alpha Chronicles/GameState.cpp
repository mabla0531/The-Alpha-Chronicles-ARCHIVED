#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) {
	this->window = window;
	gameCameraOffsetX = 0;
	gameCameraOffsetY = 0;

	player = new Player(&testMap, &entities, window, &gameCameraOffsetX, &gameCameraOffsetY);
	/*Tree* tree1 = new Tree();
	Tree* tree2 = new Tree();
	Tree* tree3 = new Tree();
	Tree* tree4 = new Tree();
	Tree* tree5 = new Tree();
	Tree* tree6 = new Tree();
	Tree* tree7 = new Tree();
	Tree* tree8 = new Tree();
	Tree* tree9 = new Tree();*/
	HostileEntity* robot = new HostileEntity(&testMap, &entities, player);

	/*tree1->setX(300);
	tree1->setY(300);
	tree2->setX(400);
	tree2->setY(300);
	tree3->setX(600);
	tree3->setY(200);
	tree4->setX(500);
	tree4->setY(700);
	tree5->setX(700);
	tree5->setY(200);
	tree6->setX(100);
	tree6->setY(800);
	tree7->setX(200);
	tree7->setY(600);
	tree8->setX(400);
	tree8->setY(200);
	tree9->setX(100);
	tree9->setY(400);*/

	entities.push_back(player);
	/*entities.push_back(tree1);
	entities.push_back(tree2);
	entities.push_back(tree3);
	entities.push_back(tree4);
	entities.push_back(tree5);
	entities.push_back(tree6);
	entities.push_back(tree7);
	entities.push_back(tree8);
	entities.push_back(tree9);*/
	entities.push_back(robot);
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

	//sort Entities by Y value to give a 3d perspective
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
