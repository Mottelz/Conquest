#include "Map.h"

using namespace std;

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
void Map::insertTerritory(string nam, float pos[2], string contiNam, vector<string> adjNam)
{
	Territory _terri;
	_terri.name = nam;
	_terri.position[0] = pos[0];
	_terri.position[1] = pos[1];
	_terri.adjacentNam = adjNam;

	//link continent pointer
	for (int i = 0; i < CONTINENTS.size(); i++)
	{
		if (CONTINENTS[i].name == contiNam)
		{
			_terri.continent = &CONTINENTS[i];
			TERRITORIES.push_back(_terri);
			CONTINENTS[i].numOfAllTerri = CONTINENTS[i].numOfAllTerri+1;
			CONTINENTS[i].terri_id.push_back(TERRITORIES.size()-1);
			//cout << "size: " << TERRITORIES.size();
			//cout << CONTINENTS[i].name << " = " << CONTINENTS[i].continentBonus << ", contains " << CONTINENTS[i].numOfAllTerri << endl;
			//for (int j = 0; j < CONTINENTS[i].numOfAllTerri; ++j)
			//{
			//	cout << CONTINENTS[i].territories[j]->name << ", ";
			//	cout << CONTINENTS[i].territories[j]->position[0] << ", ";
			//	cout << CONTINENTS[i].territories[j]->position[1] << ", ";
			//}
			//break;
			//continue;
		}
		
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

//link-adj function for literator
void Map::linkAdjacentTerri(int terriID)
{
	const vector<string> tempAdjList = TERRITORIES[terriID].adjacentNam;
	for (int i = 0; i < tempAdjList.size(); i++) {
		TERRITORIES[terriID].adjacent.push_back(&TERRITORIES[seekTerritoryID(tempAdjList[i])]);
	}
}

//link all adj for each terri
void Map::linkAdj()
{
	for (int i = 0; i < TERRITORIES.size(); i++)
	{
		
		linkAdjacentTerri(i);
	}
}

void Map::LinkAllTerri()
{
	for (int i = 0; i < CONTINENTS.size(); i++)
	{
		for (int j = 0; j < CONTINENTS[i].numOfAllTerri; j++)
		{
			CONTINENTS[i].territories.push_back(&TERRITORIES[CONTINENTS[i].terri_id[j]]);
		}
	}
}


//assign one army of the current player into current territory if available
void Map::assignArmies(int player, string terri)
{
	int _id = seekTerritoryID(terri);
	if ((TERRITORIES[_id].owner == 0) || (TERRITORIES[_id].owner == player))
		TERRITORIES[_id].armies++;
	
}

void Map::displayConti()
{
	cout << "All continents: " << endl;
	for (int i = 0; i < CONTINENTS.size(); i++)
	{
		cout << CONTINENTS[i].name << " = " << CONTINENTS[i].continentBonus << ", contains " << CONTINENTS[i].numOfAllTerri << " territories" << endl;
	}
}

void Map::displayTerri()
{
	//cout << "All territoies from CONTINENTS: " << endl;
	//for (int i = 0; i < CONTINENTS.size(); i++)
	//{
	//	for (int j = 0; j < CONTINENTS[i].territories.size(); j++) 
	//	{
	//		cout << CONTINENTS[i].territories[j]->name << ", ";
	//		cout << (CONTINENTS[i].territories[j]->position[0]) << ", ";
	//		cout << CONTINENTS[i].territories[j]->position[1] << ", ";
	//		cout << CONTINENTS[i].name;
	//		for (int k = 0; CONTINENTS[i].territories[j]->adjacent.size();k++)
	//		{
	//			cout << ", " << CONTINENTS[i].territories[j]->adjacent[k]->name;
	//		}
	//		if (CONTINENTS[i].territories[j]->owner == 0)
	//			cout << endl;
	//		else
	//		{
	//			cout << ", Player " << CONTINENTS[i].territories[j]->owner;
	//			cout << ", Armies " << CONTINENTS[i].territories[j]->armies;
	//			cout << endl;
	//		}
	//		
	//	}
	//}
	cout << endl;
	cout << "All territoies from TERRITORIES: " << endl;
	for (int i = 0; i < TERRITORIES.size(); i++)
	{
		cout << TERRITORIES[i].name;
		cout << ", " << TERRITORIES[i].position[0] << ", " << TERRITORIES[i].position[1];
		cout << ", " << TERRITORIES[i].continent->name;
		for (int j = 0; j < TERRITORIES[i].adjacent.size(); j++)
		{
			cout << ", " << TERRITORIES[i].adjacent[j]->name;
			//cout << ", " << TERRITORIES[i].adjacent[j]->continent->name;

		}
		if (TERRITORIES[i].owner == 0)
			cout << endl;
		else
		{
			cout << ", Player " << TERRITORIES[i].owner;
			cout << ", Armies " << TERRITORIES[i].armies;
			cout << endl;
		}
		
	}
}






//destructor
Map::~Map()
{
}
