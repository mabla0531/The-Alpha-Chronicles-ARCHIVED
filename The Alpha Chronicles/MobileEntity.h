#pragma once
#include "Entity.h"
#include "Animation.h"

class MobileEntity : public Entity {
protected:
	Animation* animation;
	Animation* currentAnimation;
	int animationCount;
	int currentFrame = 0;
	float animationCycleSpeed = 250.0f;
	sf::Clock cycleClock;

	std::vector<Entity*>* entities;
	Map* map;
	bool movingX = false;
	bool movingY = false;

	float speed = 1.5f;
	float runningSpeed = 2.5f;

public:

	MobileEntity(Map* map, std::vector<Entity*>* entities);
	~MobileEntity();

	void moveX(float xMove);
	void moveY(float yMove);

	virtual void tick() = 0;
	void render(sf::RenderWindow* window, int xOffset, int yOffset);
};

