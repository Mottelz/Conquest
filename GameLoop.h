/** 
 * \file 
 * The header for the GameLoop.cpp. Includes declaration for GameLoop. 
 **/
#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "Startup.h"

/**
 * This is the main game loop. It is the main object that runs the game.
 * \param m_Startup The Startup object.
 * \param m_Map The map to be used. 
 */
class GameLoop {
public:
	GameLoop();
	GameLoop(Startup &startup);
	~GameLoop();
	void loop(Map* map, Deck& deck);
	string loop(Map* map, Deck& deck, int turns);

private:
	Startup m_Startup;
};


#endif //GameLoop.h