#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include "Map.h"
using namespace std;

class MapLoader
{
	string m_MapFile;

	public:
		MapLoader(const string MAP_NAME);
		~MapLoader();
		inline string getMapName() {
			return m_MapFile;
		};
		void readMapFile(Map& mapObject);
		void testMap();
		int main();

	private: 
		void addTerritory(string territoryName, string coordinateX, string coordinateY, string continentName, vector<string> neighbouringTerritories, Map& mapObject);
};


#endif