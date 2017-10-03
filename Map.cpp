#include "Map.h"
#include <exception>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

Territory::Territory()
{
	this->m_Owner = 0;
	this->m_Armies = 0;
}

Continent::Continent() 
{
	this->m_ContinentLinks = 0;
	this->m_ContinentBonus = 0;
	this->m_NumberOfTerritories = 0;
}

Map::Map()
{
	this->m_ValidMap = true;
}

Map::Map(string name)
{
	this->m_MapName = name;
	this->m_ValidMap = true;

}

string Map::getMapName()
{
	return this->m_MapName;
}

int Map::getTotalNumberOfTerritories()
{
	return m_Territories.size();
}

void Map::setMapValidate(bool boln)
{
	this->m_ValidMap = boln;
}

bool Map::isValid()
{
	return this->m_ValidMap;
}

// Insert a new continent
void Map::insertContinent(string name, int continentBonus) throw(string)
{
	if (seekContinentID(name) != -1)
	{
		m_ValidMap = false;
		throw string("Invalid Map: Repeated continent.");
	}
	Continent continent;
	//continent.m_ContinentLinks = 0;
	//continent.m_NumberOfTerritories = 0;
	continent.m_ContinentName = name;
	continent.m_ContinentBonus = continentBonus;
	m_Continents.push_back(continent);
	
}

// Insert Territory, its position, continent name, increase the number of territories in that continent
void Map::insertTerritory(string name, float position[2], string continentName, vector<string> adjacentTerritoriesNames) throw(string)
{
	if (seekTerritoryID(name) != -1)
	{
		m_ValidMap = false;
		throw string("Invalid Map: Repeated Territory. ");
		return;
	}
	Territory territory;
	//territory.m_Owner = 0;
	//territory.m_Armies = 0;
	territory.m_TerritoryName = name;
	territory.m_Position[0] = position[0];
	territory.m_Position[1] = position[1];
	territory.m_AdjacentTerritoriesNames = adjacentTerritoriesNames;

	// Link continent pointer
	
	if (seekContinentID(continentName) > -1)
	{
		int tempContinentID = seekContinentID(continentName);
		territory.m_Continent = &m_Continents[tempContinentID];
		m_Territories.push_back(territory);
		m_Continents[tempContinentID].m_NumberOfTerritories++;
		m_Continents[tempContinentID].m_TerritoryID.push_back(m_Territories.size()-1);
	}
	else
	{
		m_ValidMap = false;
		throw string("Invalid Map: Invalid continent.");
	}
}

int Map::seekContinentID(string continentName) 
{
	for (int i = 0; i < m_Continents.size(); i++)
	{
		if (m_Continents[i].m_ContinentName == continentName)
			return i;
	}
	return -1;
}

//seek territory vector id by territory name
int Map::seekTerritoryID(string territoryName)
{
	//int terriID;
	for (int i = 0; i < m_Territories.size(); i++)
	{
		if (m_Territories[i].m_TerritoryName == territoryName)
		{
			//terriID = i;
			
			return i;
		}
	}
	return -1;
}

// Link one adjacent territory to the current territory
void Map::linkAdjacentTerritory(string territory, string adjacentTerritory)
{
	m_Territories[seekTerritoryID(territory)].m_AdjacentTerritories.push_back(&m_Territories[seekTerritoryID(adjacentTerritory)]);
}

// Link a group of adjacent territories to the current territory
void Map::linkAdjacentTerritories(string territory, vector<string> adjacentTerritories)
{
	int territoryID = seekTerritoryID(territory);
	for (int i = 0; i < adjacentTerritories.size(); i++) {
		m_Territories[territoryID].m_AdjacentTerritories.push_back(&m_Territories[seekTerritoryID(adjacentTerritories[i])]);
	}
}

// Link-adj function for iterator
void Map::linkAdjacentTerritoryID(int territoryID) throw(string)
{
	const vector<string> tempAdjList = m_Territories[territoryID].m_AdjacentTerritoriesNames;
	int territoryIDTest;
	for (int i = 0; i < tempAdjList.size(); i++) {
		territoryIDTest = seekTerritoryID(tempAdjList[i]);
		if (territoryIDTest == -1)
		{
			m_ValidMap = false;
			throw string("Invalid Map: Invalid adjacent territory. ");
		}
		else
		{
			m_Territories[territoryID].m_AdjacentTerritories.push_back(&m_Territories[territoryIDTest]);

		}
	}
}

// Link all the adjacent territories for all territories
void Map::linkAllAdjacentTerritories() 
{
	for (int i = 0; i < m_Territories.size(); i++)
	{
		linkAdjacentTerritoryID(i);
	}
}

// Link all territories together
void Map::linkAllTerritories() 
{
	for (int i = 0; i < m_Continents.size(); i++)
	{
		for (int j = 0; j < m_Continents[i].m_NumberOfTerritories; j++)
		{
			m_Continents[i].m_ContinentTerritories.push_back(&m_Territories[m_Continents[i].m_TerritoryID[j]]);
		}
	}
}


// Assign one army of the current player into current territory if available
void Map::assignArmies(int _player, string territory)
{
	int _id = seekTerritoryID(territory);
	if ((m_Territories[_id].m_Owner == 0) || (m_Territories[_id].m_Owner == _player))
	{
		m_Territories[_id].m_Owner = _player;
		m_Territories[_id].m_Armies++;
	}
	
}

Territory* Map::getTerriAddress(string territory)
{
	int territoryID = seekTerritoryID(territory);
	return &m_Territories[territoryID];
}


vector<Territory*> Map::terriOfPlayer(int _player)
{
	vector<Territory*> myTerri;
	for (int i = 0; i < m_Territories.size(); i++)
	{
		if (m_Territories[i].m_Owner == _player)
		{
			myTerri.push_back(&m_Territories[i]);
		}

	}
	return myTerri;
}

bool Map::seekPath(string startTerri, string endTerri, vector<string> &path)
{
	//vector<string> path;
	if (path.size() == 0)
		path.push_back(startTerri);
	int startID = seekTerritoryID(startTerri);
	for (int i = 0; i < m_Territories[startID].m_AdjacentTerritories.size(); i++)
	{
		if (!isRepeated(path, m_Territories[startID].m_AdjacentTerritories[i]->m_TerritoryName))
		{
			if (m_Territories[startID].m_AdjacentTerritories[i]->m_TerritoryName == endTerri)
			{
				path.push_back(m_Territories[startID].m_AdjacentTerritories[i]->m_TerritoryName);
				return true;
			}
			else
			{
				path.push_back(m_Territories[startID].m_AdjacentTerritories[i]->m_TerritoryName);
				if (seekPath(m_Territories[startID].m_AdjacentTerritories[i]->m_TerritoryName, endTerri, path))
					return true;
				else
					path.pop_back();
			}

		}
	}
	return false;
}


bool Map::isRepeated(vector<string> &list, string obj)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == obj)
			return true;
	}
	return false;
}

bool Map::isBadMap() throw(string)
{
	if (m_ValidMap)
	{
		if (m_Territories.size() == 0 || m_Continents.size() == 0 || (m_Territories.size() <= m_Continents.size()))
		{
			m_ValidMap = false;
			throw string("Invalid Map: Empty territory list or continent list, or invalid data. ");
		}
		else
		{
			for (int i = 0; i < m_Territories.size(); i++)
			{
				//check each Territories must at least have one adj

				if ((m_Territories[i].m_AdjacentTerritoriesNames.size() < 1) || (m_Territories[i].m_AdjacentTerritoriesNames.size() != m_Territories[i].m_AdjacentTerritories.size()))
				{
					m_ValidMap = false;
					throw string("Invalid Map: isolated territory case. ");
					return true;
				}
				for (int j = 0; j < m_Territories[i].m_AdjacentTerritoriesNames.size(); j++)
				{
					if (m_Territories[i].m_AdjacentTerritories[j]->m_Continent->m_ContinentName != m_Territories[i].m_Continent->m_ContinentName)
					{
						m_Territories[i].m_AdjacentTerritories[j]->m_Continent->m_ContinentLinks++;
					}
				}
			}
			for (int i = 0; i < m_Continents.size(); i++)
			{
				if (m_Continents[i].m_ContinentLinks == 0)
				{
					m_ValidMap = false;
					throw string("Invalid Map: Isolated continent. ");

					return true;
				}
			}
		}
	}
	return false;

}

void Map::displayContinents()
{
	cout << endl;

	cout << "All continents: " << endl;
	for (int i = 0; i < m_Continents.size(); i++)
	{
		cout << m_Continents[i].m_ContinentName << " = " << m_Continents[i].m_ContinentBonus << ", contains " << m_Continents[i].m_NumberOfTerritories << " territories" << endl;
	}
	cout << endl;
}

void Map::displayTerritories()
{
	cout << endl;
	cout << "All territories: " << endl;
	for (int i = 0; i < m_Territories.size(); i++)
	{
		cout << m_Territories[i].m_TerritoryName;
		cout << ", " << m_Territories[i].m_Position[0] << ", " << m_Territories[i].m_Position[1];
		cout << ", " << m_Territories[i].m_Continent->m_ContinentName;
		for (int j = 0; j < m_Territories[i].m_AdjacentTerritories.size(); j++)
		{
			cout << ", " << m_Territories[i].m_AdjacentTerritories[j]->m_TerritoryName;
		}
		if (m_Territories[i].m_Owner > 0)
		{
			cout << ", Player " << m_Territories[i].m_Owner;
			cout << ", Armies " << m_Territories[i].m_Armies;

			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}
	cout << endl;
}

vector<string> Map::getAllTerritoryNames() {
	vector<string> toReturn;
	for (int i = 0; i < m_Territories.size(); i++) {
		toReturn.push_back(m_Territories[i].m_TerritoryName);
	}
	return toReturn;
}

void Map::toString()
{
	cout << "=========================================" << endl;
	cout << "Map: " << getMapName() << endl;
	cout << "=========================================" << endl;

	displayContinents();
	cout << "-----------------------------------------" << endl;

	displayTerritories();
	cout << "-----------------------------------------" << endl;
	cout << endl;
}

//destructor
Map::~Map()
{
}

MapLoader::MapLoader(){}

MapLoader::~MapLoader(){}

void MapLoader::readMapFile(string &mapFile,  Map &mapObject) throw(string)
{
	ifstream input(mapFile); // Open the file

	if (input.fail()) // Unable to open the file; may not exist or wrong file name or wrong directory
	{
		mapObject.setMapValidate(false);
		throw std::string("ERROR: Unable to open the file. ");

		return;
	}
	
	string skip;
	getline(input, skip, ']'); // Read until the first ] is encountered (after [Map])
	getline(input, skip, ']'); // Read until the second ] is encountered (after [Continents])
	getline(input, skip); // Read and discard the end of line

	string read;

	string continent;
	vector<string> continents;
	string continentName;
	int continentBonus;
	bool endOfContinentSection = false;

	while (!endOfContinentSection)
	{
		getline(input, read); // Read a line at a time
		if (!read.empty())
		{
			stringstream line(read);
			getline(line, continentName, '=');
			getline(line, continent, '=');
			continentBonus = atoi(continent.c_str());

			mapObject.insertContinent(continentName, continentBonus);
		}
		else // If the line is empty
		{
			while (getline(input, skip) && (skip.empty())); // Check if next line is also empty; skip until the next line is not empty
			endOfContinentSection = true; // Exit loop because we've reached the [Territories] section (assuming a valid map despite the number of empty lines between sections)
		}
			
	}

	vector<string> neighbouringTerritories;
	string neighbouringTerritory;
	string territoryName;
	string coordinateX;
	string coordinateY;
	float position[2];

	while(!input.eof()) // Read until the end of file
	{
		getline(input, read); // Read a line at a time
		if (!read.empty())
		{
			stringstream line(read);
			getline(line, territoryName, ',');
			getline(line, coordinateX, ',');
			getline(line, coordinateY, ',');
			getline(line, continentName, ',');
			while (line.good())  // Splitting every line into strings stored in the elements vector
			{
				getline(line, neighbouringTerritory, ',');
				neighbouringTerritories.push_back(neighbouringTerritory);
			}
			
			position[0] = stof(coordinateX);
			position[1] = stof(coordinateY);
			mapObject.insertTerritory(territoryName, position, continentName, neighbouringTerritories); // Add a territory for every line read
			neighbouringTerritories.clear(); // Clear the vector for new iteration
		}
	}

	input.close(); // We're done reading the file

	mapObject.linkAllAdjacentTerritories();

	mapObject.linkAllTerritories();

	mapObject.isBadMap();

	cout << "Map File: " << mapObject.getMapName() << " is loaded successfully. " << endl;
	cout << endl;
}

