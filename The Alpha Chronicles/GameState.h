#pragma once
#include "State.h"
#include "Player.h"
#include "Map.h"

class GameState : public State {
private:
	sf::RenderWindow* window;
	Player player;
	Map testMap;
	int gameCameraOffsetX, gameCameraOffsetY;

public:
	GameState();
	GameState(sf::RenderWindow* window);
	~GameState();

	void tickGameCamera();
	void tick();
	void render();
	void render(sf::RenderWindow* window);
};
