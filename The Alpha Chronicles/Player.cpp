#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(Map* map, std::vector<Entity*>* entities, sf::RenderWindow* window, int* cameraXOffset, int* cameraYOffset) : MobileEntity(map, entities) {
	this->window = window;
	this->cameraXOffset = cameraXOffset;
	this->cameraYOffset = cameraYOffset;
	
	//set spriteSheet and sprite
	spriteSheet.loadFromFile("res/player.png");
	sprite.setTexture(spriteSheet);

	//construct animations, 0, 1, 2, 3 is down, left, right, up respectively
	animation = new Animation[4];
	animationCount = 4;

	for (int i = 0; i < animationCount; i++) {
		animation[i].length = 4;

		animation[i].frames.push_back(sf::IntRect(32, (32 * i), 32, 32));
		animation[i].frames.push_back(sf::IntRect(0,  (32 * i), 32, 32));
		animation[i].frames.push_back(sf::IntRect(32, (32 * i), 32, 32));
		animation[i].frames.push_back(sf::IntRect(64, (32 * i), 32, 32));
	}

	currentAnimation = &animation[0];
	sprite.setTextureRect(currentAnimation->frames.at(0));

	//set player's starting location
	x = 100.0f;
	y = 100.0f;

	//set collision bounds of the player
	collisionBounds.left = 4;
	collisionBounds.top = 8;
	collisionBounds.width = 24;
	collisionBounds.height = 24;
}

Player::~Player() {

}

void Player::tick() {
	
	float xMove = 0.0f, yMove = 0.0f; //stores the movement that needs to be done
	float moveSpeed = speed;
	animationCycleSpeed = 250.0f;

	//keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		moveSpeed = runningSpeed;
		animationCycleSpeed = 125.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		yMove = -moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		xMove = -moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		yMove = moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		xMove = moveSpeed;
	}

	//special diagonal movement that ensures the player will not move faster diagonally
	float diagonalMove = sqrt((moveSpeed * moveSpeed) / 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		yMove = -diagonalMove;
		xMove = -diagonalMove;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		yMove = -diagonalMove;
		xMove = diagonalMove;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		yMove = diagonalMove;
		xMove = -diagonalMove;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		yMove = diagonalMove;
		xMove = diagonalMove;
	}
	
	//apply the movement
	moveX(xMove);
	moveY(yMove);

	//mouse input
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		FloatPoint mouseXY = getLengthRatio(x + 16 - *cameraXOffset, y + 16 - *cameraYOffset, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

		for (int e = 0; e < entities->size(); e++) {
			if (entities->at(e) != this) {
				for (int step = 16; step <= 64; step += 16) { //TODO FIX THIS RETARDED FUCKING JERRYRIG LATER BUT IT WORKS FOR NOW I GUESS
					if (entities->at(e)->getCollisionBoundsWithLocation().contains(sf::Vector2f(x + 16 - (step * mouseXY.x), y + 16 - (step * mouseXY.y)))) {
						entities->at(e)->hurt(1);
						std::cout << entities->at(e)->getHealth() << std::endl;
					}
				}
			}
		}
	}

	//set the current animation for the direction of movement
	if (yMove > 0.0f)						currentAnimation = &animation[0];
	else if (yMove < 0.0f)					currentAnimation = &animation[3];
	else if (xMove < 0.0f && yMove == 0.0f) currentAnimation = &animation[1];
	else if (xMove > 0.0f && yMove == 0.0f) currentAnimation = &animation[2];

	//cycle animation, and if the entity isn't moving set the currentFrame to idle
	if (cycleClock.getElapsedTime().asMilliseconds() >= animationCycleSpeed) {
		if (xMove != 0.0f || yMove != 0.0f) {
			cycleClock.restart();
			currentFrame++;
			if (currentFrame >= currentAnimation->length) currentFrame = 0; //if the current frame is larger than the size of the vector, set it to the beginning again
		} else currentFrame = 0; //the first frame in the vector doubles as the stagnant frame
	}
}

void Player::render(sf::RenderWindow* window, int xOffset, int yOffset) {
	sprite.setPosition(sf::Vector2f(x - xOffset, y - yOffset)); //center the player sprite exactly in the center of the screen
	sprite.setTextureRect(currentAnimation->frames.at(currentFrame));

	window->draw(sprite);
}
