#include "Entity.h"
#include <iostream>

Entity::Entity(Map* map) {
	this->map = map;
}

Entity::~Entity() {

}

void Entity::move(float xMove, float yMove) {

	if ((xMove != 0.0f) && !(map->getTile(x + xMove - 8, y).isSolid())) {
		x += xMove;
	}
	if ((yMove != 0.0f) && !(map->getTile(x, y + yMove - 12).isSolid())) {
		y += yMove;
	}
}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}
