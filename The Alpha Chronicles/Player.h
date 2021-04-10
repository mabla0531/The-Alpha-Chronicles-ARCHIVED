#pragma once
#include "MobileEntity.h"

class Player : public MobileEntity {

public:
	Player(Map* map, std::vector<Entity*>* entities);
	~Player();

	void tick();
};
