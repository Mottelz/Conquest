/** 
 * \file 
 * The cpp for the GameLoop.h. Includes definitions for GameLoop. 
 **/
#include "GameLoop.h"

/**
 * Constructor creates the Startup object. 
 * \see Startup.Startup()
 */
GameLoop::GameLoop()
{
	m_Startup = Startup();
}

/**
 * Constrcutor if you already have the Startup and Map objects.
 * \param startup The Startup object.
 * \param map The Map.
 */
GameLoop::GameLoop(Startup &startup)
{
	m_Startup = startup;
}

/**
 * Destructor. No special things removed.
 */
GameLoop::~GameLoop() {}

/**
 * The main game loop. This goes through the entire game.
 */
void GameLoop::loop(Map* map, Deck& deck)
{
	int index;
	int count = m_Startup.m_NumberOfPlayers;
	int numberOfPlayers = m_Startup.m_NumberOfPlayers;
	bool winnerFound = false;

	while (!winnerFound)
	{
		index = count % numberOfPlayers;  // For the round-robin rotation
		
		if (m_Startup.m_Players[index]->getNumberOfTerritories() == 0)
			continue;  // When a player has no more countries, he's out of the game

		cout << "\n===================================" << endl;
		cout << "It's " << m_Startup.m_Players[index]->getName() << "'s turn to play!" << endl;
		cout << "===================================\n" << endl;

		m_Startup.m_Players[index]->play(m_Startup.m_Players[index], map, deck);
		
		if (m_Startup.m_Players[index]->getNumberOfTerritories() == map->getTotalNumberOfTerritories())
		{
			winnerFound = true;
			cout << "\n************************************" << endl;
			cout << m_Startup.m_Players[index]->getName() << " controls all " << map->getTotalNumberOfTerritories()
				<< " territories." << endl;
			cout << "GAME OVER." << endl;
			cout << "************************************\n" << endl;
		}

		count++;
	}
}


