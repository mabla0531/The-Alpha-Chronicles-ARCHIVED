#pragma once
#include "Entity.h"
#include "Animation.h"

class Player : public Entity {
private:
	Animation animation[4];
	Animation* currentAnimation;
	int currentFrame = 0;
	float animationCycleSpeed = 250.0f;
	sf::Clock cycleClock;

public:
	Player(Map* map);
	~Player();

	void tick();
	void render(sf::RenderWindow* window, int xOffset, int yOffset);
};
