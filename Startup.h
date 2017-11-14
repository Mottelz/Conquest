/** 
 * \file 
 * The header for the Startup.cpp. Includes declaration for Startup. 
 * */
#ifndef STARTUP_H
#define STARTUP_H

#include "Map.h"
#include "Player.h"
#include <vector>

/**
 * The class that starts up the game.
 * \param m_NumberOfPlayers Number of players. 
 * \param m_Players Vector of Players to be used. 
 */

class Startup {
	friend class GameLoop;
public:
	Startup();
	Startup(vector<Player*> &players);
	~Startup();
	void distributeTerritories(Map &map);
	void placeArmies(Map &map);

private:
	int m_NumberOfPlayers;
	vector<Player*> m_Players;

};

#endif //Startup.h