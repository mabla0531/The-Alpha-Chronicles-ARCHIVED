#pragma once
#include <SFML/Graphics.hpp>

class State {
private:
	bool finished = false;

public:
	virtual void tick() = 0;
	virtual void render(sf::RenderWindow* window) = 0;

	bool isFinished();
};
