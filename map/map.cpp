#include "map.h"



map::map()
{
}

map::map(string nam)
{
	mapNam = nam;
}

//insert a new continent
void map::insertContinent(string nam, int numOfTerri)
{
	Continent _conti;
	_conti.name = nam;
	_conti.numOfAllTerri = numOfTerri;
	CONTINENTS.push_back(_conti);
}

void map::insertTerritory(string nam, float pos[2], string contiNam)
{
	Territory _terri;
	_terri.name = nam;
	_terri.position[0] = pos[0];
	_terri.position[1] = pos[1];
	//link continent pointer
	for (int i = 0; i < CONTINENTS.size(); i++)
	{
		if(CONTINENTS[i].name == contiNam)
			_terri.continent = &CONTINENTS[i];
	}
}

int map::seekTerritoryID(string terriNam)
{
	//int terriID;
	for (int i = 0; i < TERRITORIES.size(); i++)
	{
		if (TERRITORIES[i].name == terriNam)
		{
			//terriID = i;
			return i;
		}
	}
	return -1;
}

void map::linkAdjacentTerri(string terri, string adjacent)
{
	TERRITORIES[seekTerritoryID(terri)].adjacent.push_back(&TERRITORIES[seekTerritoryID(adjacent)]);
}

void map::linkAdjacentTerri(string terri, vector<string> adjacent)
{
	int _id = seekTerritoryID(terri);
	for (int i = 0; i < adjacent.size(); i++) {
		TERRITORIES[_id].adjacent.push_back(&TERRITORIES[seekTerritoryID(adjacent[i])]);
	}
}

void map::assignArmies(int player, string terri)
{
	int _id = seekTerritoryID(terri);
	if ((TERRITORIES[_id].owner == 0) || (TERRITORIES[_id].owner == player))
		TERRITORIES[_id].armies++;
	
}




map::~map()
{
}
