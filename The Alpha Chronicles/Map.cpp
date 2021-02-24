#include "Map.h"
#include <iostream>

Map::Map() {
	int mapWidth, mapHeight, tileID;
	sf::IntRect tileRects[3];
	tileRects[0] = sf::IntRect(672, 160, 32, 32);
	tileRects[1] = sf::IntRect(832, 352, 32, 32);
	tileRects[2] = sf::IntRect(704, 544, 32, 32);

	std::ifstream mapFile;
	mapFile.open("res/maps/map1.map");
	mapFile >> mapWidth >> mapHeight;
	
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			mapFile >> tileID;
			
			tiles.push_back(Tile(tileRects[tileID], sf::Vector2f(x * 32.0f, y * 32.0f), false));
			std::cout << x << " " << y << std::endl;
		}
	}

	width = mapWidth * 32;
	height = mapHeight * 32;

	tileMap.loadFromFile("res/terrain_atlas.png");
}

Map::~Map() {

}

void Map::tick() {
	
}

void Map::render(sf::RenderWindow* window, int xOffset, int yOffset) {

	currentTile.setTexture(tileMap);
	for (int i = 0; i < tiles.size(); i++) {
		currentTile.setTextureRect(tiles.at(i).getTextureRect());
		currentTile.setPosition(sf::Vector2f(tiles.at(i).getLocation().x - xOffset, tiles.at(i).getLocation().y - yOffset));

		window->draw(currentTile);
	}
}

int Map::getWidth() {
	return width;
}

int Map::getHeight() {
	return height;
}