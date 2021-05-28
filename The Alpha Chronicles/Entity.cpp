#include "Entity.h"

Entity::Entity() {
	
}

Entity::~Entity() {

}

float Entity::getX() {
	return x;
}

float Entity::getY() {
	return y;
}

sf::FloatRect Entity::getCollisionBoundsWithLocation() {
	return sf::FloatRect(collisionBounds.left + x, collisionBounds.top + y, (float)collisionBounds.width, (float)collisionBounds.height);
}

sf::FloatRect Entity::getCollisionBoundsWithMovement(float xMove, float yMove) {
	return sf::FloatRect(collisionBounds.left + x + xMove, collisionBounds.top + y + yMove, (float)collisionBounds.width, (float)collisionBounds.height);
}

void Entity::setX(float x) {
	this->x = x;
}

void Entity::setY(float y) {
	this->y = y;
}

void Entity::hurt(int damage) {
	health -= damage;
}

int Entity::getHealth() {
	return health;
}