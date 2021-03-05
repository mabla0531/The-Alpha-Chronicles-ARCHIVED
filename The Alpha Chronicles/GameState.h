#pragma once
#include "State.h"
#include "Player.h"
#include "Tree.h"
#include "Map.h"

class GameState : public State {
private:
	sf::RenderWindow* window;
	Map testMap;
	Player player = Player(&testMap);
	Tree tree;
	int gameCameraOffsetX, gameCameraOffsetY;

public:
	GameState(sf::RenderWindow* window);
	~GameState();

	void tickGameCamera();
	void tick();
	void render();
	void render(sf::RenderWindow* window);
};
