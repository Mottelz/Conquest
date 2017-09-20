#include "Map.h"



Map::Map()
{
}

Map::Map(string nam)
{
	mapNam = nam;
}

//insert a new continent
void Map::insertContinent(string nam, int contiBonus)
{
	Continent _conti;
	_conti.name = nam;
	_conti.continentBonus = contiBonus;
	CONTINENTS.push_back(_conti);
}

//insert Territory, its position, continent name, increase the number of territories in that continent
void Map::insertTerritory(string nam, float pos[2], string contiNam)
{
	Territory _terri;
	_terri.name = nam;
	_terri.position[0] = pos[0];
	_terri.position[1] = pos[1];
	//link continent pointer
	for (int i = 0; i < CONTINENTS.size(); i++)
	{
		if (CONTINENTS[i].name == contiNam)
		{
			_terri.continent = &CONTINENTS[i];
			TERRITORIES.push_back(_terri);
			CONTINENTS[i].numOfAllTerri++;
		}
		break;
	}
}

//seek territory vector id by territory name
int Map::seekTerritoryID(string terriNam)
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

//link one adjacent territory to the current territory
void Map::linkAdjacentTerri(string terri, string adjacent)
{
	TERRITORIES[seekTerritoryID(terri)].adjacent.push_back(&TERRITORIES[seekTerritoryID(adjacent)]);
}

//link a group of adjacent territories to the current territory
void Map::linkAdjacentTerri(string terri, vector<string> adjacent)
{
	int _id = seekTerritoryID(terri);
	for (int i = 0; i < adjacent.size(); i++) {
		TERRITORIES[_id].adjacent.push_back(&TERRITORIES[seekTerritoryID(adjacent[i])]);
	}
}

//assign one army of the current player into current territory if available
void Map::assignArmies(int player, string terri)
{
	int _id = seekTerritoryID(terri);
	if ((TERRITORIES[_id].owner == 0) || (TERRITORIES[_id].owner == player))
		TERRITORIES[_id].armies++;
	
}



//destructor
Map::~Map()
{
}
