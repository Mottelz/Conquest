#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

using namespace std;

// call back
struct Continent;

//territory
struct Territory {
	string name;
	float position[2];
	//continent that the territory belongs to 
	Continent* continent;
	//node pointer
	vector<Territory*> adjacent;
	int owner = 0;
	int armies = 0;
};

//continent
struct Continent {
	string name;
	//number of all territories in the continent
	int numOfAllTerri;
	int continentBonus;
	vector<Territory*> territories;
};




class Map
{
public:
	Map();
	Map(string nam);
	void insertContinent(string nam, int contiBonus);
	void insertTerritory(string nam, float pos[2], string contiNam);
	int seekTerritoryID(string terriNam);
	void linkAdjacentTerri(string terri, string adjacent);
	void linkAdjacentTerri(string terri, vector<string> adjacent);

	void assignArmies(int player, string terri);

	~Map();


private:
	vector<Territory> TERRITORIES;
	vector<Continent> CONTINENTS;
	string mapNam;

};

#endif // MAP_H