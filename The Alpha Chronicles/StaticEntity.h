#pragma once
#include "Entity.h"

class StaticEntity : public Entity {
protected:


public:
	StaticEntity();
	~StaticEntity();

	virtual void tick() = 0;
	virtual void render(sf::RenderWindow* window, int xOffset, int yOffset);

};