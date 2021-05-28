#include "Arrow.h"
#include "ACMath.h"

Arrow::Arrow(float x, float y, int rotation) {
	spriteSheet.loadFromFile("res/ammo/arrow_02.png");
	sprite.setTexture(spriteSheet);

	float PI = 3.14159265;
	float RAD = 180 / PI;
	rotation = RAD / 2;

	x = 250.0f;
	y = 250.0f;
}

Arrow::~Arrow() {

}

void Arrow::tick() {

}

void Arrow::render(sf::RenderWindow* window) {
	sprite.setPosition(x, y);
	window->draw(sprite);
}
