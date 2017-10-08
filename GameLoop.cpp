#include "GameLoop.h"


GameLoop::GameLoop()
{
	m_Startup = Startup();
}

GameLoop::GameLoop(Startup &startup, Map &map)
{
	m_Startup = startup;
	m_Map = map;
}


GameLoop::~GameLoop()
{

}

void GameLoop::loop()
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

		m_Startup.m_Players[index]->reinforce();
		m_Startup.m_Players[index]->attack();
		m_Startup.m_Players[index]->fortify();

		// We explicitely give all territories to player 1, so skip this step if it's player 1's turn
		if (index != 0)
			giveTerritory(*m_Startup.m_Players[index]);
		
		if (m_Startup.m_Players[index]->getNumberOfTerritories() == m_Map.getTotalNumberOfTerritories())
		{
			winnerFound = true;
			cout << "\n************************************" << endl;
			cout << m_Startup.m_Players[index]->getName() << " controls all " << m_Map.getTotalNumberOfTerritories()
				<< " territories." << endl;
			cout << "GAME OVER." << endl;
			cout << "************************************\n" << endl;
		}

		count++;
	}
}

// Method to give every players' territories to player one (for temporary testing)
void GameLoop::giveTerritory(Player &player)
{
	string territory = player.deallocateTerritory(); // Remove a territory from the player
	m_Startup.m_Players[0]->assignTerritory(territory, m_Map); // Gives it to player #1 
}


