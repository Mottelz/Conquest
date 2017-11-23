/** 
 * \file 
 * The cpp for the Map.h. Includes definitions for Map,  Territory, Continent, and MapLoader. 
 * */
#include "Map.h"
#include <exception>
#include <sstream>
//#include <string>
//#include <vector>
//#include <iostream>
#include <fstream>
//using namespace std;



/**
 * Constrcutor sets everything to zero and NULL.
 */
Territory::Territory()
{
	this->m_OwnerID = 0;
	this->m_Armies = 0;
	this->m_Owner = NULL;
}

/**
 * Checks if any nerby territories are not owned by the owner of this country.
 */
bool Territory::enemyNeighbourExists()
{
	for (int i = 0; i < m_AdjacentTerritories.size(); i++)
	{
		if (this->m_Owner != this->m_AdjacentTerritories[i]->getOwnerPointer())
			return true;
	}
	return false;
}

/**
 * Prints out the territories owned by someone else and prints out the ones not already conqured. 
 */
void Territory::enemyNeighboursDisplay()
{
	cout << "Enemy Adjacent Territories of " << this->m_TerritoryName << ": " << endl;
	for (int i = 0; i < this->m_AdjacentTerritories.size(); i++)
	{
		if (this->getOwnerPointer() != this->m_AdjacentTerritories[i]->getOwnerPointer())
		{
			printf("[%03d]|%s|Armies: %d \n", this->m_AdjacentTerritories[i]->getTerriID(), this->m_AdjacentTerritories[i]->getTerriName().c_str(), this->m_AdjacentTerritories[i]->getNumOfArmies());
		}
	}
	cout << endl;
}

/**
 * Checks if any neighbours are ruled by the same evil dictator. 
 */
bool Territory::friendNeighbourExists()
{
	for (int i = 0; i < m_AdjacentTerritories.size(); i++)
	{
		if (this->m_Owner == this->m_AdjacentTerritories[i]->getOwnerPointer())
			return true;
	}
	return false;
}

/**
 * Basic constructor sets everything to zero and NULL.
 */
Continent::Continent() 
{
	this->m_ContinentLinks = 0;
	this->m_ContinentBonus = 0;
	this->m_NumberOfTerritories = 0;
	this->m_OwnerID = 0;
	this->m_Owner = NULL;
}

/**
 * Checks if the owner of a territory owns the continent. NOT SURE NEEDS VERIFICATION!!!
 */
bool Continent::contiUpdate(Territory * terri)
{
	Player *tempP = terri->getOwnerPointer();
	if (tempP == this->getOwnerPointer())
		return false;
	else {
		for (int i = 0; i < m_NumberOfTerritories; i++)
		{
			if (tempP != m_ContinentTerritories[i]->getOwnerPointer())
			{
				if (this->getOwnerPointer() == NULL)
					return false;
				else
				{
					this->m_Owner = NULL;
					this->m_OwnerID = 0;

					return true;
				}
			}
		}
		this->m_Owner = tempP;
		this->m_OwnerID = m_ContinentTerritories[0]->getOwnerID();
		return true;
	}
}

/**
 * Declares the empty map valid.
 */
Map::Map()
{
	this->m_ValidMap = true;
}

/**
 * Names the map and declares the map to be valid.
 */
Map::Map(string name)
{
	this->m_MapName = name;
	this->m_ValidMap = true;

}

/**
 * Returns map name.
 */
string Map::getMapName()
{
	return this->m_MapName;
}

/**
 * Returns total number of territories.
 */
int Map::getTotalNumberOfTerritories()
{
	return m_Territories.size();
}

/**
 * Returns number of continents on the map.
 */
int Map::getTotalNumberOfContinents()
{
	return this->m_Continents.size();
}

/**
 * Assigns the country to a player.
 * \param territory The name of the country being assigned. 
 * \param player Pointer to the player that is conquring. 
 */
void Map::setTerritoryOwner(string territory, Player* player)
{
	int _id = seekTerritoryID(territory);
	m_Territories[_id].m_Owner = player;
	m_Territories[_id].m_OwnerID = player->getPlayerID();
}
/**
 * Sets m_ValidMap.
 * \param isValid the bool to be set.
 */
void Map::setMapValidate(bool isValid)
{
	this->m_ValidMap = isValid;
}

/**
 * Returns true if map is valid false otherwise.
 */
bool Map::isValid()
{
	return this->m_ValidMap;
}

/**
 * Checks if the given countries are next to each other.
 * \param terriID_1 ID of one country.
 * \param terriID_2 ID of other country.
 */
bool Map::isAdjacent(int terriID_1, int terriID_2)
{
	for(int i=0; i<m_Territories[terriID_1].m_AdjacentTerritories.size();i++)
	{
		if (m_Territories[terriID_1].m_AdjacentTerritories[i] == &m_Territories[terriID_2])
			return true;
	}
	return false;
}

/**
 * Insert a new continent. Throws exception if the continent already exists.
 * \param name Name of continent.
 * \param continentBonus Amount of armies given for owning continent.
 */
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

/**
 * Insert Territory, its position, continent name, increase the number of territories in that continent.
 * \param name Name of new country.
 * \param position Postion of new country.
 * \param continentName Name of new continent. 
 * \param adjacentTerritoriesNames Names of the adjacent countries.
 */
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
		territory.m_TerritoryID = m_Territories.size();
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
/**
 * Returns continent's ID based on name.
 * \param continentName the name of the continent.
 */
int Map::seekContinentID(string continentName) 
{
	for (int i = 0; i < m_Continents.size(); i++)
	{
		if (m_Continents[i].m_ContinentName == continentName)
			return i;
	}
	return -1;
}

/**
 * Returns country ID based on name.
 * \param territoryName The name.
 */
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

/**
 * Returns country name.
 * \param terriID ID of territory.
 */
string Map::getTerritoryName(int terriID)
{
	return m_Territories[terriID].m_TerritoryName;
}

/**
 * Returns owner ID.
 * \param terriID The country ID.
 */
int Map::getOwnerIDOfTheTerritory(int terriID)
{
	return this->m_Territories[terriID].getOwnerID();
}

/**
 * Returns owner pointer.
 * \param terriID The country ID.
 */
Player * Map::getOwnerOfTheTerritory(int terriID)
{
	return this->m_Territories[terriID].getOwnerPointer();
}

/**
 * Returns owner ID.
 * \param contiID The continent ID.
 */
int Map::getOwnerIDOfTheContinent(int contiID)
{
	return this->m_Continents[contiID].getOwnerID();
}

/**
 * Returns owner pointer.
 * \param contiID The continent ID.
 */
Player * Map::getOwnerOfTheContinent(int contiID)
{
	return this->m_Continents[contiID].getOwnerPointer();
}

/**
 * Returns number of occupying troop.
 * \param terriID The country ID.
 */
int Map::getArmyNumOfTheTerritory(int terriID)
{
	return this->m_Territories[terriID].getNumOfArmies();
}

/**
 * Link one adjacent territory to the current territory.
 * \param territory The current country.
 * \param adjacentTerritory The new country.
 */
void Map::linkAdjacentTerritory(string territory, string adjacentTerritory)
{
	m_Territories[seekTerritoryID(territory)].m_AdjacentTerritories.push_back(&m_Territories[seekTerritoryID(adjacentTerritory)]);
}

/** Link a group of adjacent territories to the current territory
 * \param territory The current country.
 * \param adjacentTerritories List of the countries being added.
 */
void Map::linkAdjacentTerritories(string territory, vector<string> adjacentTerritories)
{
	int territoryID = seekTerritoryID(territory);
	for (int i = 0; i < adjacentTerritories.size(); i++) {
		m_Territories[territoryID].m_AdjacentTerritories.push_back(&m_Territories[seekTerritoryID(adjacentTerritories[i])]);
	}
}

/** Link Adjacent function for iterator
 * \param territoryID The ID of the main territory. 
 */
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

/**
 * Link all the adjacent territories for all territories.
 */ 
void Map::linkAllAdjacentTerritories() 
{
	for (int i = 0; i < m_Territories.size(); i++)
	{
		linkAdjacentTerritoryID(i);
	}
}

/** 
 * Link all territories together
 */
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


/**
 * Assign one army of the current player into current territory if available
 * \param _player pointer to player.
 * \param territory name of the territory.
 */
bool Map::assignArmies(Player *_player, string territory)
{
	int _id = seekTerritoryID(territory);
	if ((m_Territories[_id].m_Owner == NULL) || (m_Territories[_id].m_Owner == _player)) 
	{
		m_Territories[_id].m_Owner = _player;
		m_Territories[_id].m_OwnerID = _player->getPlayerID();
		m_Territories[_id].m_Armies++;
		_player->myTerriUpdate(this);
		if (m_Territories[_id].m_Continent->contiUpdate(&m_Territories[_id]))
			_player->myContiUpdate(this);

		return true;
	}
	return false;
	
}

/**
 * Remove all the troops from the country.
 * \param _player pointer to player.
 * \param territory name of the territory.
 */
bool Map::removeArmies(Player * _player, string territory)
{
	int _id = seekTerritoryID(territory);
	if ((m_Territories[_id].m_Armies > 0) && (m_Territories[_id].m_Owner == _player))
	{
		m_Territories[_id].m_Armies--;
		if (m_Territories[_id].m_Armies == 0)
		{
			m_Territories[_id].m_Owner = NULL;
			m_Territories[_id].m_OwnerID = 0;
		}
		_player->myTerriUpdate(this);
		if (m_Territories[_id].m_Continent->contiUpdate(&m_Territories[_id]))
			_player->myContiUpdate(this);

		return true;
	}
	return false;
}

/**
 * Checks if all countries are assigned.
 */
bool Map::allTerriAssigned()
{
	for (int i = 0; i < m_Territories.size(); i++)
	{
		if (m_Territories[i].getOwnerPointer() == NULL)
			return false;
	}
	return true;
}

/**
 * Check is a country is assigned.
 * \param terriID The ID of the country.
 */
bool Map::isAssigned(int terriID)
{
	if(this->m_Territories[terriID].getOwnerPointer() == NULL)
		return false;
	else
	{
		return true;
	}
}


/** 
 * Returns the total bonus a player gets for owning one or more continents.
 * \param playerID ID of the player whose bonus we're checking.
 */
int Map::computeTotalBonus(int playerID)
{
	int totalBonus = 0;
	bool ownsContinent;
	for (int i = 0; i < m_Continents.size(); i++)
	{
		ownsContinent = true;
		for (int j = 0; j < m_Continents[i].m_ContinentTerritories.size(); i++)
		{
			if (m_Continents[i].m_ContinentTerritories[j]->m_OwnerID != playerID)
			{
				ownsContinent = false;  
				break; // If one of the territories from this continent doesn't belong to the player then the player doesn't own the territory
			}
		}

		if (ownsContinent == true) // If we didn't break from the loop then the player owned all the territories from this continent
			totalBonus += m_Continents[i].m_ContinentBonus;  // Add the bonus of this continent to the total
	}

	return totalBonus;
}

/**
 * Returns pointer of a country based on name.
 * \param territory Name of country.
 */
Territory* Map::getTerriAddress(string territory)
{
	int territoryID = seekTerritoryID(territory);
	return &m_Territories[territoryID];
}
/**
 * Returns pointer of a country based on ID.
 * \param terriID ID of country.
 */
Territory * Map::getTerriAddress(int terriID)
{
	return &m_Territories[terriID];
}

/**
 * Returns Contitnet pointer based on ID.
 * \param contiID ID of desired continent. 
 */
Continent * Map::getContiAddress(int contiID)
{
	return &m_Continents[contiID];
}

/**
 * Returns a vector of all the countries owned by this player.
 * \param _player the player's ID.
 */
vector<Territory*> Map::terriOfPlayer(int _player)
{
	vector<Territory*> myTerri;
	for (int i = 0; i < m_Territories.size(); i++)
	{
		if (m_Territories[i].m_OwnerID == _player)
		{
			myTerri.push_back(&m_Territories[i]);
		}

	}
	return myTerri;
}

/**
 * Checks for enemies. 
 * \param terriID ID of country we're checking.
 */
bool Map::enemyNeighbourExists(int terriID)
{
	return m_Territories[terriID].enemyNeighbourExists();
}

/**
 * Checks for friends. 
 * \param terriID ID of country we're checking.
 */
bool Map::friendNeighbourExists(int terriID)
{
	return  m_Territories[terriID].friendNeighbourExists();
}

/**
 * Checks if there is a path between two countries owned by a player.
 * \param _player Pointer to the general.
 * \param startTerri The name of the country we're starting from.
 * \param endTerri The name of the country we're ending at.
 * \param path The path you can use to traverse. 
 */
bool Map::seekPath(Player * _player, string startTerri, string endTerri, vector<string> &path)
{
	//vector<string> path;
	if (path.size() == 0)
		path.push_back(startTerri);
	int startID = seekTerritoryID(startTerri);
	if ((m_Territories[startID].getOwnerPointer() == _player) && (m_Territories[seekTerritoryID(endTerri)].getOwnerPointer() == _player))
	{
		for (int i = 0; i < m_Territories[startID].m_AdjacentTerritories.size(); i++)
		{
			if ((m_Territories[startID].m_AdjacentTerritories[i]->getOwnerPointer() == _player) 
				&& (!isRepeated(path, m_Territories[startID].m_AdjacentTerritories[i]->m_TerritoryName)))
			{
				if (m_Territories[startID].m_AdjacentTerritories[i]->m_TerritoryName == endTerri)
				{
					path.push_back(m_Territories[startID].m_AdjacentTerritories[i]->m_TerritoryName);
					return true;
				}
				else
				{
					path.push_back(m_Territories[startID].m_AdjacentTerritories[i]->m_TerritoryName);
					if (seekPath(_player, m_Territories[startID].m_AdjacentTerritories[i]->m_TerritoryName, endTerri, path))
						return true;
					else
						path.pop_back();
				}

			}
		}
	}
	return false;
}

/**
 * Checks for repeats of string.
 * \param list The complete list of all the stuff we're looking at.
 * \param obj The new thing we're hoping isn't already there.
 */
bool Map::isRepeated(vector<string> &list, string obj)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == obj)
			return true;
	}
	return false;
}

/**
 * Throws an error if the map isn't valid.
 */
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

/**
 * Prints out all the continents. 
 */
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

/**
 * Prints out all the territories. 
 */
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
		if (m_Territories[i].m_OwnerID > 0)
		{
			cout << ", Player " << m_Territories[i].m_OwnerID;
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

/**
 * Returns a vector with all the country's names.
 */
vector<string> Map::getAllTerritoryNames() {
	vector<string> toReturn;
	for (int i = 0; i < m_Territories.size(); i++) {
		toReturn.push_back(m_Territories[i].m_TerritoryName);
	}
	return toReturn;
}

/**
 * Prints out all the map related data.
 */
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

/**
 * Prints neighbouring enemies of a country.
 * \param terriID ID of place we're checking from.
 */
void Map::enemyTerriOf(int terriID)
{
	m_Territories[terriID].enemyNeighboursDisplay();
}

/**
* Return neighbouring enemies of a country (as a vector of strings).
*/
vector<string> Map::getEnemyAdjacentTerritoryNames(int territoryID)
{
	vector<string> toReturn;
	Territory* territory = getTerriAddress(territoryID);
	for (int i = 0; i < territory->m_AdjacentTerritories.size(); i++) {
		if (territory->m_Owner != territory->m_AdjacentTerritories[i]->m_Owner)
			toReturn.push_back(territory->m_AdjacentTerritories[i]->m_TerritoryName);
	}
	return toReturn;
}

/**
* Return neighbouring friends of a country (as a vector of strings).
*/
vector<string> Map::getFriendlyAdjacentTerritoryNames(int territoryID)
{
	vector<string> toReturn;
	Territory* territory = getTerriAddress(territoryID);
	for (int i = 0; i < territory->m_AdjacentTerritories.size(); i++) {
		if (territory->m_Owner == territory->m_AdjacentTerritories[i]->m_Owner)
			toReturn.push_back(territory->m_AdjacentTerritories[i]->m_TerritoryName);
	}
	return toReturn;
}

/**
 * Destructor, doesn't do anything special.
 */
Map::~Map(){}

/**
 * Basic construstor which creates nothing.
 */ 
MapLoader::MapLoader(){}

/**
 * Basic destructor which destroys nothing.
 */ 
MapLoader::~MapLoader(){}

/**
 * Loads a map into a map object. Uses a relative path.
 * \param mapFile Relative path to mapfile.
 * \param mapObject Map object.
 */
void MapLoader::readMapFile(string &mapFile,  Map &mapObject) throw(string)
{
	ifstream input(mapFile); // Open the file

	if (input.fail()) // Unable to open the file; may not exist or wrong file name or wrong directory
	{
		mapObject.setMapValidate(false);
		throw string("ERROR: Unable to open the file. ");
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

