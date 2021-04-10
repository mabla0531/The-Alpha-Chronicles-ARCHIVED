#include "Tree.h"

Tree::Tree() {
	spriteSheet.loadFromFile("res/terrain_atlas.png");
	sprite.setTexture(spriteSheet);
	sprite.setTextureRect(sf::IntRect(352, 800, 32, 32));

	collisionBounds.left = 10;
	collisionBounds.top = 22;
	collisionBounds.width = 6;
	collisionBounds.height = 10;

}

Tree::~Tree() {

}

void Tree::tick() {

}