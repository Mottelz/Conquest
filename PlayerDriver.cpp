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
	maploader.readMapFile(mapFile, map);
	//Make Deck
	Deck testDeck = Deck(map.getAllTerritoryNames(), map.getTotalNumberOfTerritories());
	//Make Player
	Player Mottel = Player("Mottel");

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
}
