#ifndef STARTUP_H
#define STARTUP_H

#include "Map.h"
#include "Player.h"
#include <vector>

class Startup {

	friend class GameLoop;

public:
	Startup();
	Startup(vector<Player> &players);
	~Startup();
	void distributeTerritories(Map &map);
	void placeArmies(Map &map);

private:
	int m_NumberOfPlayers;
	vector<Player*> m_Players;

};

#endif //Startup.h