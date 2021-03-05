#include "MobileEntity.h"

MobileEntity::MobileEntity(Map* map) : Entity() {
	animation = new Animation();
	animationCount = 0;
	currentAnimation = animation;
	this->map = map;
}

MobileEntity::~MobileEntity() {

}

void MobileEntity::move(float xMove, float yMove) {
	//collision detection
	moving = false;
	if (xMove < 0.0f && !(map->getTile(x + xMove + collisionBounds.left, y + collisionBounds.top).isSolid()) &&
						!(map->getTile(x + xMove + collisionBounds.left, y + collisionBounds.top + collisionBounds.height).isSolid())) {
		x += xMove;
		moving = true;
	}
	else if (xMove > 0.0f && !(map->getTile(x + xMove + collisionBounds.left + collisionBounds.width, y + collisionBounds.top).isSolid()) &&
							 !(map->getTile(x + xMove + collisionBounds.left + collisionBounds.width, y + collisionBounds.top + collisionBounds.height).isSolid())) {
		x += xMove;
		moving = true;
	}
	if (yMove < 0.0f && !(map->getTile(x + collisionBounds.left, y + yMove + collisionBounds.top).isSolid()) &&
						!(map->getTile(x + collisionBounds.left + collisionBounds.width, y + yMove + collisionBounds.top).isSolid())) {
		y += yMove;
		moving = true;
	}
	else if (yMove > 0.0f && !(map->getTile(x + collisionBounds.left, y + yMove + collisionBounds.top + collisionBounds.height).isSolid()) &&
							 !(map->getTile(x + collisionBounds.left + collisionBounds.width, y + yMove + collisionBounds.top + collisionBounds.height).isSolid())) {
		y += yMove;
		moving = true;
	}
}

void MobileEntity::render(sf::RenderWindow* window, int xOffset, int yOffset) {
	sprite.setPosition(sf::Vector2f(x - xOffset, y - yOffset)); //center the player sprite exactly in the center of the screen
	sprite.setTextureRect(currentAnimation->frames.at(currentFrame));
	window->draw(sprite);
}
