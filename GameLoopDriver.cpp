#include "GameLoop.h"

int main()
{
	//LOAD THE MAP
	Map map;
	MapLoader maploader;
	string mapFile = "maps/World.map";
	maploader.readMapFile(mapFile, map);

	//CREATE PLAYERS
	// Comment or uncomment to test with different number of players
	vector<Player> players;
	players.push_back(Player("Jon"));
	players.push_back(Player("Daenerys"));
	players.push_back(Player("Cersei"));
	players.push_back(Player("Tyrion"));
	players.push_back(Player("Arya"));
	players.push_back(Player("Sansa"));

	//STARTUP PHASE
	Startup startup(players);
	startup.distributeTerritories(map);
	startup.placeArmies(map);

	//TESTING THE MAIN GAME LOOP
	GameLoop gameloop(startup, map);
	gameloop.loop();

	return 0;
}