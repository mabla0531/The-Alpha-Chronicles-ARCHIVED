#include "StaticEntity.h"
#include <iostream>

StaticEntity::StaticEntity() : Entity() {

}

StaticEntity::~StaticEntity() {

}

void StaticEntity::render(sf::RenderWindow* window, int xOffset, int yOffset) {
	sprite.setPosition(x - xOffset, y - yOffset);
	window->draw(sprite);
}