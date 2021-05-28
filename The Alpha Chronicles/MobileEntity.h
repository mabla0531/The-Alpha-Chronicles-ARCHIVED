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

	std::vector<Entity*>* entities; //entities vector for doing entity collision detection during movement
	Map* map; //map object for doing tile collision detection

	float speed = 1.0f;
	float runningSpeed = 2.0f;

public:

	MobileEntity(Map* map, std::vector<Entity*>* entities);
	~MobileEntity();

	void moveX(float xMove);
	void moveY(float yMove);

	virtual void tick() = 0;
	void render(sf::RenderWindow* window, int xOffset, int yOffset);
};

