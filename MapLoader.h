#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include "Map.h"
using namespace std;

class MapLoader
{
	const string MAP_FILE;

	public:
		MapLoader();
		~MapLoader();
		void readMapFile(Map& mapObject);
		int main();

	private: 
		void addTerritory(string territoryName, string coordinateX, string coordinateY, string continentName, vector<string> neighbouringTerritories, Map& mapObject);
};


#endif