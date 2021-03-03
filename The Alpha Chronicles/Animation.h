#pragma once
#include "SFML/Graphics/Rect.hpp"
#include <vector>

struct Animation {
	int length;
	std::vector<sf::IntRect> frames;
};