#pragma once
#include "MobileEntity.h"

class Player : public MobileEntity {

public:
	Player(Map* map);
	~Player();

	void tick();
};
