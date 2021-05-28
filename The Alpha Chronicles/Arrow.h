#pragma once
#include <SFML/Graphics.hpp>

class Arrow {
private:
	sf::Texture spriteSheet;
	sf::Sprite sprite;

	float x, y;
	int rotation; //in degrees
	int speed = 1;

public:
	Arrow(float x, float y, int rotation);
	~Arrow();

	void tick();
	void render(sf::RenderWindow* window);

};