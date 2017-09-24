#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>

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
	int owner = 0;
	int armies = 0;
};
//struct Territory;
//continent
struct Continent {
	string name;
	//number of all territories in the continent
	int numOfAllTerri = 0;
	int continentBonus = 0;
	vector<int> terri_id;
	vector<Territory*> territories;
};




class Map
{
public:
	Map();
	Map(string nam);
	void insertContinent(string nam, int contiBonus);
	void insertTerritory(string nam, float pos[2], string contiNam, vector<string> adjNam);
	int seekTerritoryID(string terriNam);
	void linkAdjacentTerri(string terri, string adjacent);
	void linkAdjacentTerri(string terri, vector<string> adjacent);
	void linkAdjacentTerri(int terriID);
	void linkAdj();

	void LinkAllTerri();

	void assignArmies(int player, string terri);
	void displayConti();
	void displayTerri();

	~Map();


private:
	vector<Territory> TERRITORIES;
	vector<Continent> CONTINENTS;
	string mapNam;
	

};

#endif // MAP_H