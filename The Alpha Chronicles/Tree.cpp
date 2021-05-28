#include "Tree.h"

Tree::Tree() {
	spriteSheet.loadFromFile("res/trees.png");
	sprite.setTexture(spriteSheet);
	sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));

	collisionBounds.left = 10;
	collisionBounds.top = 22;
	collisionBounds.width = 6;
	collisionBounds.height = 10;

}

Tree::~Tree() {

}

void Tree::tick() {

}