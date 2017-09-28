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
	myTerriList.push_back("Western United States");
	myTerriList.push_back("Quebec");
	myTerriList.push_back("Quebec");
	myTerriList.push_back("Quebec");
	myTerriList.push_back("Quebec");
	myTerriList.push_back("Quebec");
	myTerriList.push_back("Western United States");
	myTerriList.push_back("Western United States");
	myTerriList.push_back("Western United States");


	for (int i = 0; i < myTerriList.size()-1; ++i)
	{
		Mottel.assignTerritory(myTerriList[i], map);
		cout << 1 << endl;;
	}
	//Player Picks Cards
	for (int i = 0; i < 5; ++i) {
		Mottel.drawCard(testDeck);
	}

	//Display Player's Hand
	cout << "Mottel's cards: " << endl;
	Mottel.displayHand();


	//Player Rolls Dice
	cout << "\nMottel's dice: " << endl;
	Mottel.rollDice(3);
	

	//Player does the other things
	Mottel.reinforce();
	Mottel.fortify();
	Mottel.attack();

	//check whole map
	map.toString();

	//check my territory
	Mottel.displayPlayerTerritories();

	//system("PAUSE");
	cout << endl;
}
