#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>

#include "Player.h"

using namespace std;


class Player;

struct Continent; // Forward declaration

struct Territory {
	string m_TerritoryName;
	float m_Position[2];
	Continent* m_Continent; // Continent that the territory belongs to 
	vector<string> m_AdjacentTerritoriesNames;
	vector<Territory*> m_AdjacentTerritories; // Node pointer
	int m_TerritoryID;
	int m_OwnerID;
	int m_Armies;
	Player * m_Owner;
	Territory();
	string getTerriName() { return this->m_TerritoryName; }
	int getTerriID() { return this->m_TerritoryID; }
	int getOwnerID(){ return this->m_OwnerID; }
	int getNumOfArmies() { return this->m_Armies; }
	Player* getOwnerPointer() { return this->m_Owner; }
	bool enemyNeighbourExists();
	void enemyNeighboursDisplay();
	bool friendNeighbourExists();
};

struct Continent {
	string m_ContinentName;
	int m_NumberOfTerritories; 	// Number of all territories in the continent
	int m_ContinentBonus;
	int m_ContinentLinks;
	int m_ContinentID;
	int m_OwnerID;
	Player * m_Owner;

	vector<int> m_TerritoryID;
	vector<Territory*> m_ContinentTerritories;
	Continent();
	string getContiName() { return this->m_ContinentName; }
	int getContiID() { return this->m_ContinentID; }
	int getOwnerID() { return this->m_OwnerID; }
	Player* getOwnerPointer() { return this->m_Owner; }
	int getContiBonus() { return this->m_ContinentBonus; }
	bool contiUpdate(Territory * terri);//return true if the owner info changed, otherwise false
};




class Map
{
public:
	Map();
	Map(string name);
	string getMapName();
	int getTotalNumberOfTerritories();
	int getTotalNumberOfContinents();
	void setTerritoryOwner(string territory, Player* player);
	void setMapValidate(bool boln);
	bool isValid();
	bool isAdjacent(int terriID_1, int terriID_2);
	void insertContinent(string name, int continentBonus) throw(string);
	void insertTerritory(string name, float position[2], string continentName, vector<string> adjacentTerritoriesNames) throw(string);
	int seekContinentID(string continentName);
	int seekTerritoryID(string territoryName);
	string getTerritoryName(int terriID);
	int getOwnerIDOfTheTerritory(int terriID);
	Player* getOwnerOfTheTerritory(int terriID);
	int getOwnerIDOfTheContinent(int contiID);
	Player* getOwnerOfTheContinent(int contiID);
	int getArmyNumOfTheTerritory(int terriID);
	void linkAdjacentTerritory(string territory, string adjacentTerritory);
	void linkAdjacentTerritories(string territory, vector<string> adjacentTerritories);
	void linkAdjacentTerritoryID(int territoryID) throw(string);
	void linkAllAdjacentTerritories();
	void linkAllTerritories();

	bool assignArmies(Player *_player, string territory);
	bool removeArmies(Player *_player, string territory);
	bool allTerriAssigned();
	bool isAssigned(int terriID);

	int Map::computeTotalBonus(int playerID);

	Territory* getTerriAddress(string territory);
	Territory* getTerriAddress(int territory);
	Continent* getContiAddress(int contiID);
	vector<Territory*> terriOfPlayer(int _player);

	bool enemyNeighbourExists(int terriID);
	bool friendNeighbourExists(int terriID);

	bool seekPath(Player * _player, string startTerri, string endTerri, vector<string> &path);
	bool isRepeated(vector<string> &list, string obj);

	bool isBadMap() throw(string);
	vector<string> getAllTerritoryNames();

	void displayContinents();
	void displayTerritories();
	void toString();
	void enemyTerriOf(int terriID);

	~Map();


private:
	vector<Territory> m_Territories;
	vector<Continent> m_Continents;
	string m_MapName;
	bool m_ValidMap;

};

class MapLoader
{
	public:
		MapLoader();
		~MapLoader();
		
		void readMapFile(string &mapFile, Map &mapObject) throw(string);
};


#endif // MAP_H