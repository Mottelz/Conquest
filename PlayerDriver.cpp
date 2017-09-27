#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
using namespace std;

int main() {
	
	string mapFile = "maps/Canada.map";
	Map map;
	MapLoader maploader;
	maploader.readMapFile(mapFile, map);

	// SHOW THAT PLAYER HAS CARDS
	cout << "Mottel's cards: " << endl;
	std::string cities[] = { "Montreal", "New York", "Ottawa", "Boston", "Tel Aviv", "London", "Hell", "Hogwarts", "Blooper Land" };
	Deck testDeck = Deck(cities, 9);
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
