#include "StrategyPattern.h"
#include "Player.h"
#include "Startup.h"
#include <ctime>
#include "GameObserver.h"

using namespace std;

int main() {

	//LOAD THE MAP
	Map map;
	MapLoader maploader;
	string mapFile = "maps/World.map";
	maploader.readMapFile(mapFile, map);

	//CREATE PLAYERS
	// Comment or uncomment to test with different number of players
	vector<Player*> players;
	players.push_back(new Player("Jon", &map));
	players.push_back(new Player("Daenerys", &map));
	players.push_back(new Player("Cersei", &map));
	players.push_back(new Player("Tyrion", &map));
	//players.push_back(new Player("Arya", &map));
	//players.push_back(new Player("Sansa", &map));

	//TEST THE STARTUP CLASS
	Startup startup(players);

	startup.distributeTerritories(map);
	startup.placeArmies(map);

	vector<string> cards = map.getAllTerritoryNames();
	Deck deck(cards, cards.size());

	Player* player = players[0];
	Map* mapp = &map;
	HumanPlayer* human = new HumanPlayer();
	AggressiveAI* aggressive = new AggressiveAI();
	BenevolentAI* benevolent = new BenevolentAI();
	string type, redo;
	bool again;
	int playerCards;

	srand((unsigned)time(NULL));

	do
	{
		again = false;

		cout << "\n***************************************" << endl;
		cout << "Please select your type of player:" << endl;
		cout << "(1) : Human Player" << endl;
		cout << "(2) : Aggressive AI Player" << endl;
		cout << "(3) : Benevolent AI Player" << endl;
		cout << "***************************************\n" << endl;

		cin >> type;

		playerCards = rand() % 6 + 1;

		for (int i = 0; i < playerCards; i++)
		{
			players[0]->drawCard(deck);
		}

		vector<PhaseObserver*> playerPhaseObservers;
		gameStatistics* gameObserver;

		for (unsigned int i = 0; i < players.size(); i++)
		{
			playerPhaseObservers.push_back(new PhaseObserver(players.at(i), mapp));

		}
		gameObserver = new gameStatistics(&players, mapp);

		if (type == "1")
		{
			players[0]->setStrategy(human);
			players[0]->play(player, mapp, deck);
		}
		else if (type == "2")
		{
			players[0]->setStrategy(aggressive);
			players[0]->play(player, mapp, deck);
		}
		else if (type == "3")
		{
			players[0]->setStrategy(benevolent);
			players[0]->play(player, mapp, deck);
		}
		else
		{
			cout << "Invalid type. Please enter a number between 1, 2 and 3 only." << endl;
			again = true;
		}

		if (again == false)
		{
			cout << "\n***************************************" << endl;
			cout << "Do you want to change your type of player?" << endl;
			cout << "(1) : YES" << endl;
			cout << "(2) : NO" << endl;
			cout << "***************************************\n" << endl;
			cin >> redo;

			if (redo == "1")
				again = true;
			else if (redo == "2")
				cout << "End of program" << endl;
			else
				cout << "Invalid number. End of program." << endl;
		}
			
	} while (again == true);


	return 0;
}