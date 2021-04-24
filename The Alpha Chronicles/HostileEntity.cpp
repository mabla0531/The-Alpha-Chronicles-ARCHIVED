#include "HostileEntity.h"
#include <math.h>
#include <iostream>

HostileEntity::HostileEntity(Map* map, std::vector<Entity*>* entities, Player* player) : MobileEntity(map, entities) {
	speed = 0.5f;
	this->player = player;

	//set sprite for rendering
	spriteSheet.loadFromFile("res/male_01-1.png");
	sprite.setTexture(spriteSheet);

	//construct animations
	animation = new Animation[4];
	animationCount = 4;
	for (int i = 0; i < animationCount; i++) {
		animation[i].length = 4;
		animation[i].frames.push_back(sf::IntRect(32, (32 * i), 32, 32));
		animation[i].frames.push_back(sf::IntRect(0,  (32 * i), 32, 32));
		animation[i].frames.push_back(sf::IntRect(32, (32 * i), 32, 32));
		animation[i].frames.push_back(sf::IntRect(64, (32 * i), 32, 32));
	}

	currentAnimation = animation;
	sprite.setTextureRect(currentAnimation->frames.at(0));

	//set entity's starting location
	x = 500.0f;
	y = 500.0f;

	//set collision bounds of the entity
	collisionBounds.left = 4;
	collisionBounds.top = 8;
	collisionBounds.width = 24;
	collisionBounds.height = 24;
}

HostileEntity::~HostileEntity() {

}

void HostileEntity::tick() {
	movingX = false;
	movingY = false;

	float xMove = 0.0f, yMove = 0.0f;

	dormant = true;
	//if the distance between the entity and the player is less than 150 pixels, start moving towards the player
	if (std::abs(player->getX() - x) < 200 && std::abs(player->getY() - y) < 200) dormant = false;

	if (!dormant) {
		//find the difference between the entity and player locations
		sf::Vector2f deltaLocation = sf::Vector2f(player->getX(), player->getY()) - sf::Vector2f(x, y);
		//create a move ratio from 0 to 1 based on pythagorean theorem
		sf::Vector2f moveRatio = sf::Vector2f(deltaLocation.x / std::sqrt(std::pow(deltaLocation.x, 2) + std::pow(deltaLocation.y, 2)), 
											  deltaLocation.y / std::sqrt(std::pow(deltaLocation.x, 2) + std::pow(deltaLocation.y, 2)));
		//create the final xmove/ymove from the speed and move ratio
		xMove = moveRatio.x * speed;
		yMove = moveRatio.y * speed;

		std::cout << moveRatio.x << " " << moveRatio.y << std::endl;

		if (xMove != 0.0f) movingX = true;
		if (yMove != 0.0f) movingY = true;

		//move the entity
		if (movingX) moveX(xMove);
		if (movingY) moveY(yMove);

		//set the current animation for the direction of movement
		if (moveRatio.y > 0.0f) currentAnimation = &animation[0];
		else if (moveRatio.y < 0.0f) currentAnimation = &animation[3];
		if (moveRatio.x < -0.85f) currentAnimation = &animation[1];
		else if (moveRatio.x > 0.85f) currentAnimation = &animation[2];

		//cycle animation, and if the entity isn't moving set the currentFrame to idle
		if (cycleClock.getElapsedTime().asMilliseconds() >= animationCycleSpeed) {
			if (movingX || movingY) {
				cycleClock.restart();
				currentFrame++;
				if (currentFrame >= currentAnimation->length) currentFrame = 0;
			} else currentFrame = 0; //the first frame in the vector doubles as the stagnant frame
		}
	}
}
