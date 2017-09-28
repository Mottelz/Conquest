#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
using namespace std;

int main() {
	//Load map
	string mapFile = "maps/World.map";
	Map map;
	MapLoader maploader;
	try {
		maploader.readMapFile(mapFile, map);
	}
	catch (string e) {
		cout << "*****************************************" << endl;
		cout << "Failed loading map file: " << map.getMapName() << endl;
		cout << e << endl;
		cout << "*****************************************" << endl;
		cout << endl;
	}
	map.toString();

	//Make Deck
	Deck testDeck = Deck(map.getAllTerritoryNames(), map.getTotalNumberOfTerritories());
	//Make Player
	Player Mottel = Player("Mottel");


	vector<string> myTerriList;
	myTerriList.push_back("Alaska");
	myTerriList.push_back("Greenland");
	myTerriList.push_back("Alaska");
	myTerriList.push_back("Ontario");
	myTerriList.push_back("Western");
	//myTerriList.push_back("Quebec");
	//myTerriList.push_back("Quebec");
	//myTerriList.push_back("Quebec");
	//myTerriList.push_back("Quebec");
	//myTerriList.push_back("Quebec");
	//myTerriList.push_back("Western");
	//myTerriList.push_back("Western");
	//myTerriList.push_back("Western");


	for (int i = 0; i < myTerriList.size(); i++)
	{
		Mottel.assignTerritory(myTerriList[i], map);
	}
	//Player Picks Cards
	//for (int i = 0; i < 5; ++i) {
	//	Mottel.drawCard(testDeck);
	//}

	////Display Player's Hand
	//cout << "Mottel's cards: " << endl;
	//Mottel.displayHand();


	////Player Rolls Dice
	//cout << "\nMottel's dice: " << endl;
	//Mottel.rollDice(3);
	//

	////Player does the other things
	//Mottel.reinforce();
	//Mottel.fortify();
	//Mottel.attack();

	//map.toString();

	system("PAUSE");
}
