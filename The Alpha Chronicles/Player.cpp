#include "Player.h"

Player::Player(Map* map) : Entity(map) {
	spriteSheet.loadFromFile("res/male_01-1.png");
	sprite.setTexture(spriteSheet);

	//construct animations, 0, 1, 2, 3 is down, left, right, up respectively
	for (int i = 0; i < 4; i++) {
		animation[i].length = 4;

		animation[i].frames.push_back(sf::IntRect(32, (32 * i), 32, 32));
		animation[i].frames.push_back(sf::IntRect(0, (32 * i), 32, 32));
		animation[i].frames.push_back(sf::IntRect(32, (32 * i), 32, 32));
		animation[i].frames.push_back(sf::IntRect(64, (32 * i), 32, 32));
	}
	currentAnimation = &animation[0];
	sprite.setTextureRect(currentAnimation->frames.at(0));

	x = 100.0f;
	y = 100.0f;
}

Player::~Player() {

}

void Player::tick() {

	//handle input
	float moveInterval = speed;
	animationCycleSpeed = 250.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		moveInterval = runningSpeed;
		animationCycleSpeed = 125.0f;
	}

	float xMove = 0.0f, yMove = 0.0f; //stores the movement that needs to be done

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		yMove = -moveInterval;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		xMove = -moveInterval;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		yMove = moveInterval;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		xMove = moveInterval;

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
	
	//apply the movement
	move(xMove, yMove);

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
	if (cycleClock.getElapsedTime().asMilliseconds() >= animationCycleSpeed && moving) {
		if (xMove != 0.0f || yMove != 0.0f) {
			cycleClock.restart();
			currentFrame++;
			if (currentFrame >= currentAnimation->length) //if the current frame is larger than the size of the vector, set it to the beginning again
				currentFrame = 0;
		} else {
			currentFrame = 0; //the first frame in the vector doubles as the stagnant frame
		}
	}
}

void Player::render(sf::RenderWindow* window, int xOffset, int yOffset) {
	sprite.setPosition(sf::Vector2f(x - xOffset, y - yOffset)); //center the player sprite exactly in the center of the screen
	sprite.setTextureRect(currentAnimation->frames.at(currentFrame));
	window->draw(sprite);
}
