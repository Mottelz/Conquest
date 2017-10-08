#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <stdlib.h> 
#include <time.h> 
#include <chrono> 
#include "Startup.h"


Startup::Startup()
{
	m_NumberOfPlayers = 0;
}

Startup::Startup(vector<Player> &players)
{
	m_NumberOfPlayers = players.size();
	
	// Copies the reference to the players in the Player pointer vector
	for (int i = 0; i < m_NumberOfPlayers; i++)
	{
		m_Players.push_back(&players[i]);
	}

	// Shuffles the content of the Player pointer vector so that the order of play is determined randomly
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // seed
	std::shuffle(std::begin(m_Players), std::end(m_Players), std::default_random_engine(seed));

	// After the shuffling, assign an ID to the players (corresponds to the order of play)
	for (int i = 0; i < m_NumberOfPlayers; i++)
	{
		m_Players[i]->setPlayerID(i + 1);
	}

}

Startup::~Startup() {}

void Startup::distributeTerritories(Map &map)
{
	srand(time(0)); // Seed for the random number generator
	
	vector<string> territories(map.getAllTerritoryNames());
	int count = m_NumberOfPlayers;
	string randomTerritory;
	int randomIndex;

	while (!territories.empty()) // While the vector is not empty
	{
		// Select random territory from array
		randomIndex = rand() % territories.size();
		randomTerritory = territories[randomIndex]; 
		
		// Assign the territory in round-robin fashion. Starts at index 0 (m_NumberOfPlayers % m_NumberOfPLayers) then we increment the count.
		m_Players[count % m_NumberOfPlayers]->assignTerritory(randomTerritory, map); 

		// Puts the randomly selected territory in the last position, then delete it from container
		swap(territories[randomIndex], territories[territories.size() - 1]);
		territories.pop_back();

		// Increment the count: next iteration will assign another territory to the next player
		count++;
	}

}

void Startup::placeArmies(Map &map)
{
	int armiesAtStart;
	// Assign the number of armies depending on the number of players
	switch (m_NumberOfPlayers) {
	case 2:
		armiesAtStart = 40;
		break;
	case 3:
		armiesAtStart = 35;
		break;
	case 4:
		armiesAtStart = 30;
		break;
	case 5:
		armiesAtStart = 25;
		break;
	case 6:
		armiesAtStart = 20;
		break;
	}
	
	// The total number of armies to place is the initial number of armies multiplied by the number of players 
	int armiesToPlace = armiesAtStart*m_NumberOfPlayers;
	
	int count = m_NumberOfPlayers;
	int playerNumberOfTerritories;
	int index;
	int randomTerritory;

	vector<string> playerTerritories;

	while (armiesToPlace > 0)
	{
		index = count % m_NumberOfPlayers; // For rotation in round-robin fashion
		playerNumberOfTerritories = m_Players[index]->getNumberOfTerritories(); // Players might not have the same number of territories
		playerTerritories = m_Players[index]->getPlayerTerritoryNames(); // Retrieve the player's territories
		randomTerritory = rand() % playerNumberOfTerritories; // Chooses a random territory from the individual player's list

		// Assign one army to one territory
		map.assignArmies(m_Players[index]->getPlayerID(), playerTerritories[randomTerritory]);

		armiesToPlace--;
		count++;
	}
	
}
