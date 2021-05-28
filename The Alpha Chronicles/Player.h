#pragma once
#include "MobileEntity.h"
#include "ACMath.h"

class Player : public MobileEntity {
private:
	sf::RenderWindow* window;
	int* cameraXOffset;
	int* cameraYOffset;
public:
	Player(Map* map, std::vector<Entity*>* entities, sf::RenderWindow* window, int* cameraXOffset, int* cameraYOffset);
	~Player();

	void render(sf::RenderWindow* window, int xOffset, int yOffset);
	void tick();
};
