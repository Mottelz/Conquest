#include "Startup.h"


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

	//TEST THE STARTUP CLASS
	Startup startup(players);

	startup.distributeTerritories(map);
	startup.placeArmies(map);

	int numberOfTerritoriesDistributed = 0;

	//DISPLAY THE RESULTS AFTER DISTRIBUTION OF COUNTRIES (Proves that the right number of armies was distributed)
	for (int i = 0; i < players.size(); i++)
	{
		cout << players[i].getName() << " (Player # " << players[i].getPlayerID() << ") has "
			<< players[i].getNumberOfTerritories() << " territories, and distributed "
			<< players[i].numberOfArmiesAssigned() << " armies! \n" << endl;
		players[i].displayPlayerTerritories();
		cout << "\n======================\n" << endl;

		// Counts the number of countries distributed while traversing the vector
		numberOfTerritoriesDistributed += players[i].getNumberOfTerritories();
	}

	// Prove that all countried were assigned (otherwise the number of countries distributed would be smaller then the number of countries on the map)
	// Also prove that no country was assigned twice (otherwise the number of countries distributed would be larger than the number of countries on the map)
	cout << "The total number of countries on the map is : " << map.getTotalNumberOfTerritories() << endl;
	cout << "The number of countries distributed is: " << numberOfTerritoriesDistributed << endl;

	return 0;
}
