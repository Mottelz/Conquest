#pragma once

#include "Player.h"
#include "Map.h"
#include <string>

class Fortification
{
public:
	Fortification();
	~Fortification();

	void moveArmy(string sourceCountry, string targetCountry, Map& map, Player& p);
};