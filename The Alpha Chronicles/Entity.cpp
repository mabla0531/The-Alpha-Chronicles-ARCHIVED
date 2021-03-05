#include "Entity.h"
#include <iostream>

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

void Entity::setX(float x) {
	this->x = x;
}

void Entity::setY(float y) {
	this->y = y;
}