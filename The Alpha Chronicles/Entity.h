#pragma once
#include <SFML/Graphics.hpp>

class Entity {
protected:
	sf::Texture spriteSheet;
	sf::Sprite sprite;

	float speed = 1.25f, runningSpeed = 2.0f;
	float x = 10.0f, y = 10.0f;

public:
	Entity();
	~Entity();

	virtual void tick() = 0;
	virtual void render(sf::RenderWindow* window, int xOffset, int yOffset) = 0;

	float getX();
	float getY();
};