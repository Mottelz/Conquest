#include <iostream>

#include <ctime>

#include "Player.h"
//#include "AttackPhase.h"
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


	gameMap.toString();

	
	vector<string> cards = gameMap.getAllTerritoryNames();
	
	Deck gameDeck(cards, cards.size());
	

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
				gameMap.assignArmies(&playerList[j], gameMap.getTerritoryNam(temp));
			}
			else
			{
				while (gameMap.isAssigned(temp)) {
					temp = rand() % gameMap.getTotalNumberOfTerritories();
				}
				gameMap.assignArmies(&playerList[j], gameMap.getTerritoryNam(temp));
			}
		}
	}
//	for()
	gameMap.toString();

	//AttackPhase myAtkPhase(gameMap);

	while (true)
	{

		for (int i = 0; i < playerList.size(); i++)
		{
			cout << endl;
			cout << "==============================================================================" << endl;
			cout << "Player " << playerList[i].getPlayerID() << ", " << playerList[i].getName() << ", Reinforcement Phase: " << endl;
			cout << "------------------------------------------------------------------------------" << endl;
			int my_card = rand() % 6 + 1;
			for (int j = 0; j < my_card; j++)
			{
				playerList[i].drawCard(gameDeck);

			}
		//	playerList[i].test_REIN_setCards(my_card);
			playerList[i].REINFORCEMENT(&gameMap, gameDeck);
			
		}
	}


	return 0;
}
