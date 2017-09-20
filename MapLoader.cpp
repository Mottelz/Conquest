// MapLoader.cpp : Defines the entry point for the console application.
//

#include <stdafx.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "MapLoader.h"

using namespace std;

const string MAP_FILE = "World.map";
const string MAP_FILETEST = "C:\\Users\\Nyxeia\\Documents\\COMP 345\\Risk\\MapLoader\\MapLoader\\World.map";

MapLoader::MapLoader()
{

}


MapLoader::~MapLoader()
{

}


void MapLoader::readMapFile(Map& mapObject)
{
	ifstream input(MAP_FILETEST); // Open the file

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
	//stringstream line;

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

			//continentBonus = atoi(continents[1].c_str()); // continent[1] contains the bonus - convert to int
			mapObject.insertContinent(continentName, continentBonus);  // continent[0] contains the continent name
			//continents.clear(); // Clear the vector for new iteration
		}
		else // If the line is empty
		{
			getline(input, skip); // Read past the [Territories] line
			endOfContinentSection = true; // Exit loop
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

int main()
{
	MapLoader maploader;
	Map mapObject;

	maploader.readMapFile(mapObject);
	mapObject.toString();

    return 0;
}

