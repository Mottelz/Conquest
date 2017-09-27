#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
using namespace std;

int main() {
	
	string mapFile = "maps/World.map";
	Map map;
	MapLoader maploader;
	maploader.readMapFile(mapFile, map);

	// SHOW THAT PLAYER HAS CARDS
	cout << "Mottel's cards: " << endl;
	Deck testDeck = Deck(map.getAllTerritoryNames(), map.getTotalNumberOfTerritories());
	Player Mottel = Player();
	for (int i = 0; i < 5; ++i) {
		Mottel.drawCard(testDeck);
	}
	Mottel.displayHand();
	
	// SHOW THAT PLAYER HAS DICE
	cout << "\nMottel's dice: " << endl;
	Mottel.rollDice(3);
	return 0;
}
