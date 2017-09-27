#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <exception>
#include "Map.h"
using namespace std;

class MapLoader
{
	public:
		MapLoader();
		~MapLoader();
		
		void readMapFile(string &mapFile, Map &mapObject) throw(char);
};


#endif