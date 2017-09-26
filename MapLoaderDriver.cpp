#include "Map.h"
#include "MapLoader.h"
#include "Drivers.h"

int mapLoaderMain()
{
	MapLoader worldFile("World.map");
	Map worldMap;
	worldFile.readMapFile(worldMap);
	worldMap.displayTerri();
	// worldFile.testMap();

	MapLoader canadaFile("Canada.map");
	Map canadaMap;
	canadaFile.readMapFile(canadaMap);
	// canadaFile.testMap();

	MapLoader caribbeanFile("Caribbean.map");
	Map caribbeanMap;
	caribbeanFile.readMapFile(caribbeanMap);
	// caribbeanFile.testMap();

	MapLoader invalidFile("Invalid.map");
	Map invalidMap;
	invalidFile.readMapFile(invalidMap);
	// invalidFile.testMap();
	
	MapLoader invalidFile2("Invalid2.map");
	Map invalidMap2;
	invalidFile2.readMapFile(invalidMap2);
	// invalidFile2.testMap();
	invalidMap2.displayTerri();

    return 0;
}