#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "Startup.h"

class GameLoop{

public:
	GameLoop();
	GameLoop(Startup &startup, Map &map);
	~GameLoop();
	void loop();

private:
	Startup m_Startup;
	Map m_Map;
	void giveTerritory(Player &player);
};


#endif //GameLoop.h