#include "Tile.h"

Tile::Tile() {
    textureRect = sf::IntRect(672, 160, 32, 32);
    location = sf::Vector2f(0.0f, 0.0f);
    solid = false;
}

Tile::Tile(sf::IntRect textureRect, sf::Vector2f location, bool solid) {
    this->textureRect = textureRect;
    this->location = location;
    this->solid = solid;
}

Tile::~Tile() {

}

void Tile::tick() {

}

sf::Vector2f Tile::getLocation() {
    return location;
}

void Tile::setLocation(sf::Vector2f location) {
    this->location = location;
}

sf::IntRect Tile::getRect()
{
    return sf::IntRect(location.x, location.y, 32, 32);
}

sf::IntRect Tile::getTextureRect() {
    return textureRect;
}

void Tile::setTextureRect(sf::IntRect textureRect) {
    this->textureRect = textureRect;
}

bool Tile::isSolid() {
    return solid;
}

void Tile::setSolid(bool solid) {
    this->solid = solid;
}
