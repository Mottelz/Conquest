/** 
 * \file 
 * The code for the Startup.h. Includes definitions for Startup. 
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "Startup.h"
using namespace std;


/**
 * Constructor with zero players.
 */
Startup::Startup()
{
	m_NumberOfPlayers = 0;
}

/**
 * Constructor with Players.
 * \param players A vector of players to be used. 
 */
Startup::Startup(vector<Player*> &players)
{
	// Shuffles the content of the Player vector so that the order of play is determined randomly
	auto rng = (default_random_engine ());
	shuffle(begin(players), end(players), rng);

	m_NumberOfPlayers = players.size();
	
	// Copies the reference to the players in the Player pointer vector
	for (int i = 0; i < m_NumberOfPlayers; i++)
	{
		m_Players.push_back(players[i]);	
		m_Players[i]->setPlayerID(i + 1);
	}

}

/**
 * Destructor. Destroys nothing special. 
 */
Startup::~Startup() {}

/**
 * Randomly distribute territories/countries between the players. 
 * \param map The Map being used for the game.
 */
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
		
		// Assign the territory in round-robin fashion. Starts at index 0then we increment the count.
		m_Players[count % m_NumberOfPlayers]->assignTerritory(randomTerritory, map); 
		map.assignArmies(m_Players[count % m_NumberOfPlayers], randomTerritory);

		// Puts the randomly selected territory in the last position, then delete it from container
		swap(territories[randomIndex], territories[territories.size() - 1]);
		territories.pop_back();

		// Increment the count: next iteration will assign another territory to the next player
		count++;
	}

}

/**
 * Randomly places armies in a round robin fashion. 
 * \param map The Map where the stuff will be placed.
 */
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
	int armiesToPlace = (armiesAtStart - 1)*m_NumberOfPlayers;
	
	int count = m_NumberOfPlayers;
	int playerNumberOfTerritories;
	int index;
	int randomTerritory;

	srand(time(0));
	vector<string> playerTerritories;

	while (armiesToPlace > 0)
	{
		index = count % m_NumberOfPlayers; // For rotation in round-robin fashion
		playerNumberOfTerritories = m_Players[index]->getNumberOfTerritories(); // Players might not have the same number of territories
		playerTerritories = m_Players[index]->getPlayerTerritoryNames(); // Retrieve the player's territories
		randomTerritory = rand() % playerNumberOfTerritories; // Chooses a random territory from the individual player's list

		// Assign one army to one territory
		map.assignArmies(m_Players[index], playerTerritories[randomTerritory]);

		armiesToPlace--;
		count++;
	}
	
}
