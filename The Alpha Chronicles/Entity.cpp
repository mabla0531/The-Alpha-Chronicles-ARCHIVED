#include "Entity.h"

Entity::Entity(Map* map) {
	this->map = map;
}

Entity::~Entity() {

}

void Entity::move(float xMove, float yMove) {
	x += xMove;
	y += yMove;
}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}
