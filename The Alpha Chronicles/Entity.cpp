#include "Entity.h"
#include <iostream>

Entity::Entity(Map* map) {
	this->map = map;
	collisionBounds.left = 0;
	collisionBounds.top = 0;
	collisionBounds.width = 32;
	collisionBounds.height = 32;
}

Entity::~Entity() {

}

void Entity::move(float xMove, float yMove) {
	//collision detection
	moving = false;

	if (xMove < 0.0f && !(map->getTile(x + xMove + collisionBounds.left, y + collisionBounds.top).isSolid()) && 
						!(map->getTile(x + xMove + collisionBounds.left, y + collisionBounds.top + collisionBounds.height).isSolid())) {
		x += xMove;
		moving = true;
	} else if (xMove > 0.0f && !(map->getTile(x + xMove + collisionBounds.left + collisionBounds.width, y + collisionBounds.top).isSolid()) &&
							   !(map->getTile(x + xMove + collisionBounds.left + collisionBounds.width, y + collisionBounds.top + collisionBounds.height).isSolid())) {
		x += xMove;
		moving = true;
	}
	if (yMove < 0.0f && !(map->getTile(x + collisionBounds.left, y + yMove + collisionBounds.top).isSolid()) &&
						!(map->getTile(x + collisionBounds.left + collisionBounds.width, y + yMove + collisionBounds.top).isSolid())) {
		y += yMove;
		moving = true;
	} else if (yMove > 0.0f && !(map->getTile(x + collisionBounds.left, y + yMove + collisionBounds.top + collisionBounds.height).isSolid()) &&
							 !(map->getTile(x + collisionBounds.left + collisionBounds.width, y + yMove + collisionBounds.top + collisionBounds.height).isSolid())) {
		y += yMove;
		moving = true;
	}
}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}
