#include <iostream>

#include <ctime>

#include "Player.h"

using namespace std;

int main() {
	MapLoader loader;
	string filePath = "maps/World.map";

	Map gameMap("World.map");

	try {
		loader.readMapFile(filePath, gameMap);
	}
	catch (string e) {
		cout << "*****************************************" << endl;
		cout << "Failed loading map file: " <<gameMap.getMapName() << endl;
		cout << e << endl;
		cout << "*****************************************" << endl;
		cout << endl;
		
	}

	vector<Player> playerList;
	playerList.push_back(Player("Melodie"));
	playerList.push_back(Player("Mottel"));
	playerList.push_back(Player("Vickel"));
	playerList.push_back(Player("Yefei"));


	for (int i = 0; i < playerList.size(); i++)
	{
		playerList[i].setPlayerID(i+1);
		cout << "Player " << playerList[i].getPlayerID() << ", " << playerList[i].getName() << endl;
	}

	cout << endl;


	//initial rand seed
	srand((unsigned)time(NULL));

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < playerList.size(); j++)
		{
			int temp = rand() % gameMap.getTotalNumberOfTerritories();
			if (gameMap.allTerriAssigned())
			{
				gameMap.assignArmies(&playerList[j], gameMap.getTerritoryName(temp));
			}
			else
			{
				while (gameMap.isAssigned(temp)) {
					temp = rand() % gameMap.getTotalNumberOfTerritories();
				}
				playerList[j].assignTerritory(gameMap.getTerritoryName(temp), gameMap);
				gameMap.assignArmies(&playerList[j], gameMap.getTerritoryName(temp));
			}
		}
	}

	gameMap.toString();

	for (int i = 0; i < playerList.size(); i++)
	{
		cout << endl;
		cout << "==============================================================================" << endl;
		cout << "Player " << playerList[i].getPlayerID() << ", " << playerList[i].getName() << ", Attack Phase: " << endl;
		cout << "------------------------------------------------------------------------------" << endl;

		playerList[i].attack(&gameMap);
	}


	return 0 ;
}
