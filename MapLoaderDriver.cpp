
#include <iostream>
#include "Map.h"
#include "MapLoader.h"

using namespace std;

int main() {

	vector<string> mapList;
	vector<int> errorIDList;
	//Testing valid maps
	mapList.push_back("maps/World.map");
	mapList.push_back("maps/Earth.map");
	mapList.push_back("maps/Canada.map");
	//Maps with errors
	mapList.push_back("maps/Invalid.map");
	mapList.push_back("maps/Invalid2.map");
	//This map doesn't exist
	mapList.push_back("maps/invalid3.map");
	
	vector<Map> maps;

	MapLoader maploader;

	//Map Earth;
	for(int i=0;i<mapList.size();i++)
		maps.push_back( Map(mapList[i]));

	for (int i = 0; i < mapList.size(); i++)
	{

		try {
			maploader.readMapFile(mapList[i], maps[i]);

		}
		catch (const char *e) {
			cout << "*****************************************" << endl;
			cout << "Failed loading map file: " << maps[i].getMapName() << endl;
			cout << e << endl;
			cout << "*****************************************" << endl;
			cout << endl;
			errorIDList.push_back(i);
		}
	}

	for (int i = 0; i < maps.size(); i++)
	{
		//if no maps.erase() above then you need this if statement
		if(maps[i].isValid())
		maps[i].toString();
	}

	cout << "Number of the invalid map files " << errorIDList.size() << endl;
	cout << endl;

	return 0;
}