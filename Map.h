#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>

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
	void setMapValidate(bool boln);
	bool isValid();
	void insertContinent(string name, int continentBonus) throw(char);
	void insertTerritory(string name, float position[2], string continentName, vector<string> adjacentTerritoriesNames) throw(char);
	int seekContinentID(string continentName);
	int seekTerritoryID(string territoryName);
	void linkAdjacentTerritory(string territory, string adjacentTerritory);
	void linkAdjacentTerritories(string territory, vector<string> adjacentTerritories);
	void linkAdjacentTerritoryID(int territoryID) throw(char);
	void linkAllAdjacentTerritories();
	void linkAllTerritories();

	void assignArmies(int player, string terri);

	bool isBadMap() throw(char);

	void displayContinents();
	void displayTerritories();
	void toString();

	~Map();


private:
	vector<Territory> m_Territories;
	vector<Continent> m_Continents;
	string m_MapName;
	bool m_ValidMap = true;

};

#endif // MAP_H