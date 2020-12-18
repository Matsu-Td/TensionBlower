#pragma once
#include "appframe.h"

class PlayerData : public JsonBase{
public:
	PlayerData();
	~PlayerData();

private:
	int hitpoint;
	int attack;
	int energy;
};
