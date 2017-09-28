#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>
//#include "Player.h"

using namespace std;


struct Continent; // Forward declaration

struct Territory {
	string m_TerritoryName;
	float m_Position[2];
	Continent* m_Continent; // Continent that the territory belongs to 
	vector<string> m_AdjacentTerritoriesNames;
	vector<Territory*> m_AdjacentTerritories; // Node pointer
	int m_Owner;
	int m_Armies;
	Territory();
};

struct Continent {
	string m_ContinentName;
	int m_NumberOfTerritories; 	// Number of all territories in the continent
	int m_ContinentBonus;
	int m_ContinentLinks;
	vector<int> m_TerritoryID;
	vector<Territory*> m_ContinentTerritories;
	Continent();
};




class Map
{
public:
	Map();
	Map(string name);
	string getMapName();
	int getTotalNumberOfTerritories();
	void setMapValidate(bool boln);
	bool isValid();
	void insertContinent(string name, int continentBonus) throw(string);
	void insertTerritory(string name, float position[2], string continentName, vector<string> adjacentTerritoriesNames) throw(string);
	int seekContinentID(string continentName);
	int seekTerritoryID(string territoryName);
	void linkAdjacentTerritory(string territory, string adjacentTerritory);
	void linkAdjacentTerritories(string territory, vector<string> adjacentTerritories);
	void linkAdjacentTerritoryID(int territoryID) throw(string);
	void linkAllAdjacentTerritories();
	void linkAllTerritories();

	void assignArmies(int _player, string territory);

	Territory* getTerriAddress(string territory);
	vector<Territory*> terriOfPlayer(int _player);

	bool seekPath(string startTerri, string endTerri, vector<string> &path);
	bool isRepeated(vector<string> &list, string obj);

	bool isBadMap() throw(string);
	vector<string> getAllTerritoryNames();

	void displayContinents();
	void displayTerritories();
	void toString();

	~Map();


private:
	vector<Territory> m_Territories;
	vector<Continent> m_Continents;
	string m_MapName;
	bool m_ValidMap;

};

#endif // MAP_H