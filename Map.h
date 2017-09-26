#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>

using namespace std;

// call back
struct Continent;
//struct Territory;
//territory
struct Territory {
	string name;
	float position[2];
	//continent that the territory belongs to 
	Continent* continent;
	vector<string> adjacentNam;
	//node pointer
	vector<Territory*> adjacent;
	int owner;
	int armies;
	Territory();
};
//struct Territory;
//continent
struct Continent {
	string name;
	//number of all territories in the continent
	int numOfAllTerri;
	int continentBonus;
	int contiLinks;
	vector<int> terri_id;
	vector<Territory*> territories;
	Continent();
};




class Map
{
public:
	Map();
	Map(string nam);
	string getMapNam();
	void setMapValidate(bool boln);
	bool isValid();
	void insertContinent(string nam, int contiBonus);
	void insertTerritory(string nam, float pos[2], string contiNam, vector<string> adjNam);
	int seekContinentID(string contiNam);
	int seekTerritoryID(string terriNam);
	void linkAdjacentTerri(string terri, string adjacent);
	void linkAdjacentTerri(string terri, vector<string> adjacent);
	void linkAdjacentTerri(int terriID);
	void linkAdj();

	void LinkAllTerri();

	void assignArmies(int player, string terri);

	bool isBadMap();

	void displayConti();
	void displayTerri();
	void toString();

	~Map();


private:
	vector<Territory> TERRITORIES;
	vector<Continent> CONTINENTS;
	string mapNam;
	bool validMap = true;

};

#endif // MAP_H