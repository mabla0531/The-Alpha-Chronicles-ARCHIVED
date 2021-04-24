#pragma once
#include "Player.h"

class HostileEntity : public MobileEntity {
protected:
	bool dormant = false;
	Player* player;

public:
	HostileEntity(Map* map, std::vector<Entity*>* entities, Player* player);
	~HostileEntity();

	void tick();
};