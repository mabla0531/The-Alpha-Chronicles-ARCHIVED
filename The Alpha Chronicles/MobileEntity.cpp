#include "MobileEntity.h"

MobileEntity::MobileEntity(Map* map, std::vector<Entity*>* entities) : Entity() {
	animation = new Animation();
	animationCount = 0;
	currentAnimation = animation;
	this->map = map;
	this->entities = entities;
}

MobileEntity::~MobileEntity() {

}

void MobileEntity::moveX(float xMove) {
	//collision detection on X axis
	if ((xMove < 0.0f && ((map->getTile(x + xMove + (float)collisionBounds.left, y + (float)collisionBounds.top).isSolid()) ||
						  (map->getTile(x + xMove + (float)collisionBounds.left, y + (float)collisionBounds.top + (float)collisionBounds.height).isSolid()))) ||
		(xMove > 0.0f && ((map->getTile(x + xMove + (float)collisionBounds.left + (float)collisionBounds.width, y + (float)collisionBounds.top).isSolid()) ||
						  (map->getTile(x + xMove + (float)collisionBounds.left + (float)collisionBounds.width, y + (float)collisionBounds.top + (float)collisionBounds.height).isSolid())))) {
		movingX = false;
		return;
	}

	for (int i = 0; i < entities->size(); i++) {

		if (entities->at(i) != this && getCollisionBoundsWithMovement(xMove, 0.0f).intersects(entities->at(i)->getCollisionBoundsWithLocation())) {
			movingX = false;
			return;
		}
	}

	x += xMove;
}

void MobileEntity::moveY(float yMove) {
	//collision detection on Y axis
	if ((yMove < 0.0f && ((map->getTile(x + (float)collisionBounds.left, y + yMove + (float)collisionBounds.top).isSolid()) ||
						  (map->getTile(x + (float)collisionBounds.left + (float)collisionBounds.width, y + yMove + (float)collisionBounds.top).isSolid()))) ||
		(yMove > 0.0f && ((map->getTile(x + (float)collisionBounds.left, y + yMove + (float)collisionBounds.top + (float)collisionBounds.height).isSolid()) ||
						  (map->getTile(x + (float)collisionBounds.left + (float)collisionBounds.width, y + yMove + (float)collisionBounds.top + (float)collisionBounds.height).isSolid())))) {
		movingY = false;
		return;
	}

	for (int i = 0; i < entities->size(); i++) {

		if (entities->at(i) != this && getCollisionBoundsWithMovement(0.0f, yMove).intersects(entities->at(i)->getCollisionBoundsWithLocation())) {
			movingY = false;
			return;
		}
	}

	y += yMove;
}

void MobileEntity::render(sf::RenderWindow* window, int xOffset, int yOffset) {
	sprite.setPosition(sf::Vector2f(x - xOffset, y - yOffset)); //center the player sprite exactly in the center of the screen
	sprite.setTextureRect(currentAnimation->frames.at(currentFrame));
	window->draw(sprite);
}
