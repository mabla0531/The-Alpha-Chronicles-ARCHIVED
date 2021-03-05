#include "Tree.h"

Tree::Tree() {
	spriteSheet.loadFromFile("res/terrain_atlas.png");
	sprite.setTexture(spriteSheet);
	sprite.setTextureRect(sf::IntRect(352, 800, 32, 32));
}

Tree::~Tree() {

}

void Tree::tick() {

}