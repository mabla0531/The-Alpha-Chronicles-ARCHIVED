#pragma once
#include <vector>
#include <fstream>
#include "Tile.h"

class Map {
private:
	std::vector<Tile> tiles;
	sf::Texture tileMap;
	sf::Sprite currentTile;

	int width, height;

public:
	Map();
	~Map();

	void tick();
	void render(sf::RenderWindow* window, int xOffset, int yOffset);

	Tile getTile(float x, float y);

	int getWidth();
	int getHeight();
};
