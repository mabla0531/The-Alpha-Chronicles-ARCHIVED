#pragma once
#include <SFML/Graphics.hpp>

class Tile {
private:
	sf::IntRect textureRect;
	sf::Vector2f location;
	bool solid;

public:
	Tile();
	Tile(sf::IntRect textureRect, sf::Vector2f location, bool solid);
	~Tile();

	void tick();
	sf::Vector2f getLocation();
	void setLocation(sf::Vector2f location);
	sf::IntRect getTextureRect();
	void setTextureRect(sf::IntRect textureRect);
	bool isSolid();
	void setSolid(bool solid);
};
