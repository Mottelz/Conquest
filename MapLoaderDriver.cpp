//map driver
#include <iostream>
#include "Map.h"
#include "MapLoader.h"

using namespace std;

int main() {
	//MapLoader worldFile("maps/World.map");
	//Map worldMap;
	//worldFile.readMapFile(worldMap);
	//worldMap.displayConti();
	//worldMap.displayTerri();

	// worldFile.testMap();
	vector<string> mapList;
	vector<int> errorIDList;
	mapList.push_back("maps/World.map");
	mapList.push_back("maps/Earth.map");
	//error maps
	mapList.push_back("maps/Invalid.map");
	//mapList.push_back("maps/Invalid2.map");
	//doesnt exist
	//mapList.push_back("maps/invalid3.map");

	//mapList.push_back("maps/Canada.map");
	
	vector<Map> MAPS;

	MapLoader maploader;

	//Map Earth;
	for(int i=0;i<mapList.size();i++)
		MAPS.push_back( Map(mapList[i]));
	//int offset = 0;
	for (int i = 0; i < mapList.size(); i++)
	{
		//Map temp;
		try {
			maploader.readMapFile(mapList[i], MAPS[i]);
			//MAPS[i].toString();
		}
		catch (const char *e) {
			cout << "*****************************************" << endl;
			cout << "Failed loading map file: " << MAPS[i].getMapNam() << endl;
			cout << e << endl;
			cout << "*****************************************" << endl;
			cout << endl;
			errorIDList.push_back(i);
		}
	}

	

	//very important
	//for (int i = errorIDList.size() - 1; i >= 0; i--)
	//{
	//	MAPS.erase(MAPS.begin()+errorIDList[i]);
	//}

	for (int i = 0; i < MAPS.size(); i++)
	{
		//if no MAPS.erase() above then you need this if statement
		if(MAPS[i].isValid())
		MAPS[i].toString();
	}

	cout << "Number of the invalid map files " << errorIDList.size() << endl;
	cout << endl;

	return 0;
}