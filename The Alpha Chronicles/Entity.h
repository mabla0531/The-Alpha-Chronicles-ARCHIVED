#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Entity {
protected:
	sf::Texture spriteSheet;
	sf::Sprite sprite;

	float x = 10.0f, y = 10.0f;

	sf::IntRect collisionBounds;

public:
	Entity();
	~Entity();

	virtual void tick() = 0;
	virtual void render(sf::RenderWindow* window, int xOffset, int yOffset) = 0;

	float getX();
	float getY();

	void setX(float x);
	void setY(float y);
};