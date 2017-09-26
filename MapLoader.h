#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <exception>
#include "Map.h"
using namespace std;

class MapLoader
{
	

	public:
		MapLoader(/*const string MAP_NAME*/);
		~MapLoader();
		
		void readMapFile(string &MAP_FILE, Map &mapObject);
	
	private:
		//string MAP_FILE;
		//inline string getMapName() {
		//	return MAP_FILE;
		//};
		
};


#endif