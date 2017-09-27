// MapLoader.cpp : Defines the entry point for the console application.

#include <exception>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "MapLoader.h"

using namespace std;

MapLoader::MapLoader(){}

MapLoader::~MapLoader(){}

void MapLoader::readMapFile(string &mapFile,  Map &mapObject) throw(string)
{
	ifstream input(mapFile); // Open the file

	if (input.fail()) // Unable to open the file; may not exist or wrong file name or wrong directory
	{
		mapObject.setMapValidate(false);
		throw std::string("ERROR: Unable to open the file. ");

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
	float position[2];

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
			
			position[0] = stof(coordinateX);
			position[1] = stof(coordinateY);
			mapObject.insertTerritory(territoryName, position, continentName, neighbouringTerritories); // Add a territory for every line read
			neighbouringTerritories.clear(); // Clear the vector for new iteration
		}
	}

	input.close(); // We're done reading the file

	mapObject.linkAllAdjacentTerritories();

	mapObject.linkAllTerritories();

	mapObject.isBadMap();

	cout << "Map File: " << mapObject.getMapName() << " is loaded successfully. " << endl;
	cout << endl;


}

