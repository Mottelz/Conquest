// MapLoader.cpp : Defines the entry point for the console application.
//

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "MapLoader.h"

using namespace std;

MapLoader::MapLoader(const string MAP_NAME)
{
	MAP_FILE = MAP_NAME;
}

MapLoader::~MapLoader()
{

}

void MapLoader::readMapFile(Map& mapObject)
{
	ifstream input(MAP_FILE); // Open the file

	if (input.fail()) // Does the file exist? If not, exit the program
	{
		cout << "The file provided does not exist." << endl;
		return;
	}

	string skip;
	getline(input, skip, ']'); // Read until the first ] is encountered (after [Map])
	getline(input, skip, ']'); // Read until the second ] is encountered (after [Continents])
	getline(input, skip); // Read and discard the end of line

	string read;

	string continent;
	vector<string> continents;
	string continentName;
	int continentBonus;
	bool endOfContinentSection = false;

	while (!endOfContinentSection)
	{
		getline(input, read); // Read a line at a time
		if (!read.empty())
		{
			stringstream line(read);
			getline(line, continentName, '=');
			getline(line, continent, '=');
			continentBonus = atoi(continent.c_str());

			mapObject.insertContinent(continentName, continentBonus); 
		}
		else // If the line is empty
		{
			while (getline(input, skip) && (skip.empty())); // Check if next line is also empty; skip until the next line is not empty
			endOfContinentSection = true; // Exit loop because we've reached the [Territories] section (assuming a valid map despite the number of empty lines between sections)
		}
			
	}

	vector<string> neighbouringTerritories;
	string neighbouringTerritory;
	string territoryName;
	string coordinateX;
	string coordinateY;

	while(!input.eof()) // Read until the end of file
	{
		getline(input, read); // Read a line at a time
		if (!read.empty())
		{
			stringstream line(read);
			getline(line, territoryName, ',');
			getline(line, coordinateX, ',');
			getline(line, coordinateY, ',');
			getline(line, continentName, ',');
			while (line.good())  // Splitting every line into strings stored in the elements vector
			{
				getline(line, neighbouringTerritory, ',');
				neighbouringTerritories.push_back(neighbouringTerritory);
			}

			addTerritory(territoryName, coordinateX, coordinateY, continentName, neighbouringTerritories, mapObject); // Add a territory for every line read
			neighbouringTerritories.clear(); // Clear the vector for new iteration
		}
	}

	input.close(); // We're done reading the file

	mapObject.linkAdjacentTerritories();
}

void MapLoader::addTerritory(string territoryName, string coordinateX, string coordinateY, string continentName, vector<string> neighbouringTerritories, Map& mapObject)
{
	float position[2];
	position[0] = stof(coordinateX);
	position[1] = stof(coordinateY);

	mapObject.insertTerritory(territoryName, position, continentName, neighbouringTerritories); // Insert the new territory
}

/*void MapLoader::testMap()
{
	// if (mapObject VALID)
	//	cout << "The map " << maploader.getMapName() << " has been successfully created! " << endl;
	// else
	//	{
	//		cout << "The map " << maploader.getMapName() << " is invalid. " << endl;
	//		cout << "Please select another Map. " << endl;
	// }
}*/

int main()
{
	MapLoader worldFile("World.map");
	Map worldMap;
	worldFile.readMapFile(worldMap);
	worldMap.toString();
	// worldFile.testMap();

	MapLoader canadaFile("Canada.map");
	Map canadaMap;
	canadaFile.readMapFile(canadaMap);
	canadaMap.toString();
	// canadaFile.testMap();

	MapLoader caribbeanFile("Caribbean.map");
	Map caribbeanMap;
	caribbeanFile.readMapFile(caribbeanMap);
	// caribbeanFile.testMap();
	caribbeanMap.toString();

	MapLoader invalidFile("Invalid.map");
	Map invalidMap;
	invalidFile.readMapFile(invalidMap);
	// invalidFile.testMap();
	invalidMap.toString();
	
	MapLoader invalidFile2("Invalid2.map");
	Map invalidMap2;
	invalidFile2.readMapFile(invalidMap2);
	// invalidFile2.testMap();
	invalidMap2.toString();

    return 0;
}

