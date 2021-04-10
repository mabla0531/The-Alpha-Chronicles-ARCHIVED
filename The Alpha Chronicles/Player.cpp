#include "Player.h"

Player::Player(Map* map, std::vector<Entity*>* entities) : MobileEntity(map, entities) {
	//set spriteSheet and sprite
	spriteSheet.loadFromFile("res/male_01-1.png");
	sprite.setTexture(spriteSheet);

	//construct animations, 0, 1, 2, 3 is down, left, right, up respectively
	animation = new Animation[4];
	animationCount = 4;

	for (int i = 0; i < animationCount; i++) {
		animation[i].length = 4;

		animation[i].frames.push_back(sf::IntRect(32, (32 * i), 32, 32));
		animation[i].frames.push_back(sf::IntRect(0, (32 * i), 32, 32));
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
	movingX = false;
	movingY = false;
	//handle input
	float moveInterval = speed;
	animationCycleSpeed = 250.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		moveInterval = runningSpeed;
		animationCycleSpeed = 125.0f;
	}

	float xMove = 0.0f, yMove = 0.0f; //stores the movement that needs to be done

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		yMove = -moveInterval;
		movingY = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		xMove = -moveInterval;
		movingX = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		yMove = moveInterval;
		movingY = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		xMove = moveInterval;
		movingX = true;
	}

	//special diagonal movement that ensures the player will not move faster diagonally
	float diagonalMove = sqrt((moveInterval * moveInterval) / 2);
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
	
	//apply the movement if any was done
	if (movingX)
		moveX(xMove);
	if (movingY)
		moveY(yMove);

	//set the current animation for the direction of movement
	if (yMove > 0.0f)
		currentAnimation = &animation[0];
	else if (yMove < 0.0f)
		currentAnimation = &animation[3];
	else if (xMove < 0.0f && yMove == 0.0f)
		currentAnimation = &animation[1];
	else if (xMove > 0.0f && yMove == 0.0f)
		currentAnimation = &animation[2];

	//cycle animation, and if the player isn't moving set the currentFrame to idle
	if (cycleClock.getElapsedTime().asMilliseconds() >= animationCycleSpeed) {
		if (movingX || movingY) {
			cycleClock.restart();
			currentFrame++;
			if (currentFrame >= currentAnimation->length) //if the current frame is larger than the size of the vector, set it to the beginning again
				currentFrame = 0;
		} else {
			currentFrame = 0; //the first frame in the vector doubles as the stagnant frame
		}
	}
}

