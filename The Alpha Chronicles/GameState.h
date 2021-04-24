#pragma once
#include <vector>
#include "State.h"
#include "Player.h"
#include "Tree.h"
#include "HostileEntity.h"
#include "Map.h"

class GameState : public State {
private:
	sf::RenderWindow* window;
	Map testMap;

	Player* player;
	std::vector<Entity*> entities;

	int gameCameraOffsetX, gameCameraOffsetY;

public:
	GameState(sf::RenderWindow* window);
	~GameState();

	void tickGameCamera();
	void tick();
	void render();
	void render(sf::RenderWindow* window);
};
