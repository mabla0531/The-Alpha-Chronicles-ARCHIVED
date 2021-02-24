#include "Player.h"

Player::Player() {
	playerSpriteSheet.loadFromFile("res/male_01-1.png");
	playerSprite.setTexture(playerSpriteSheet);
	playerSprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
}

Player::~Player() {

}

void Player::tick() {
	float moveInterval = speed;
	//handle input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		moveInterval = runningSpeed;

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
	x += xMove;
	y += yMove;
}

void Player::render(sf::RenderWindow* window, int xOffset, int yOffset) {
	playerSprite.setPosition(sf::Vector2f(x - xOffset, y - yOffset));
	window->draw(playerSprite);
}

float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}
