#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
	sf::Texture playerSpriteSheet;
	sf::Sprite playerSprite;
	float x = 10.0f, y = 10.0f;
	float speed = 1.0f, runningSpeed = 2.0f;

public:
	Player();
	~Player();

	void tick();
	void render(sf::RenderWindow* window, int xOffset, int yOffset);

	float getX();
	float getY();

};
