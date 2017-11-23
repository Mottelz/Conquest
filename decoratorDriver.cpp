#include "StrategyPattern.h"
#include "Player.h"
#include "Startup.h"
#include <ctime>
#include "GameObserver.h"

using namespace std;

int main() {

	//LOAD THE MAP
	Map * map;
	MapLoader maploader;
	string mapFile = "maps/World.map";
	map = new Map(mapFile);
	maploader.readMapFile(mapFile, *map);

	//CREATE PLAYERS
	// Comment or uncomment to test with different number of players
	vector<Player*> players;
	players.push_back(new Player("Jon", map));
	players.push_back(new Player("Daenerys", map));
	players.push_back(new Player("Cersei", map));
	players.push_back(new Player("Tyrion", map));
	//players.push_back(new Player("Arya", map));
	//players.push_back(new Player("Sansa", map));

	//TEST THE STARTUP CLASS
	Startup startup(players);

	startup.distributeTerritories(*map);
	startup.placeArmies(*map);

	vector<string> cards = map->getAllTerritoryNames();
	Deck deck(cards, cards.size());

	Player* player = players[0];
	Map* mapp = map;
	HumanPlayer* human = new HumanPlayer();
	AggressiveAI* aggressive = new AggressiveAI();
	BenevolentAI* benevolent = new BenevolentAI();
	RandomAI* random = new RandomAI();
	CheaterAI* cheater = new CheaterAI();

	string type, redo, decoratorOption;
	bool again, again_with_same_type;
	int playerCards;
	int decorator[3] = { 0,0,0 };
	vector<int*> lastAddedDecorator;
	srand((unsigned)time(NULL));

	do
	{
		again = false;

		cout << "\n***************************************" << endl;
		cout << "Please select your type of player:" << endl;
		cout << "(1) : Human Player" << endl;
		cout << "(2) : Aggressive AI Player" << endl;
		cout << "(3) : Benevolent AI Player" << endl;
		cout << "(4) : Random Player" << endl;
		cout << "(5) : Cheater Player" << endl;
		cout << "***************************************\n" << endl;

		cin >> type;

		playerCards = rand() % 6 + 1;

		for (int i = 0; i < playerCards; i++)
		{
			players[0]->drawCard(deck);
			players[1]->drawCard(deck);
			players[2]->drawCard(deck);
			players[3]->drawCard(deck);
			//players[4]->drawCard(deck);
		}

		vector<PhaseObserver*> playerPhaseObservers;

		AbstractGameStatistics* gameObserver = new gameStatistics(&players, mapp);
		//apply decorators
		//gameObserver = new PlayerDominationObserverDecorator(gameObserver);
		//gameObserver = new PlayerHandsObserverDecorator(gameObserver);
		//gameObserver = new ContinentControlObserverDecorator(gameObserver);


		do {
			do {

				cout << "Currently, " << endl
					<< decorator[0] << " player dominatoin observer decorator, " << endl
					<< decorator[1] << " player hands observer decorator, " << endl
					<< decorator[2] << " player controlled continent observer decorator, " << endl
					<< "have been applied. ";



				cout << "\n***************************************" << endl;
				cout << "Please select the following option for decorator:" << endl;
				if (decorator[0] == 0)
					cout << "(1) : Add a player dominatoin observer decorator." << endl;
				if (decorator[1] == 0)
					cout << "(2) : Add a player hands observer decorator." << endl;
				if (decorator[2] == 0)
					cout << "(3) : Add a player controlled continent observer decorator." << endl;
				if (decorator[0] > 0 || decorator[1] > 0 || decorator[2] > 0)
				{
					cout << "(4) : Remove a decorator" << endl;
					cout << "(5) : Remove all decorators" << endl;
				}
				cout << "(0) : Do nothing. (Default)" << endl;
				cout << "***************************************\n" << endl;
				decoratorOption = "";
				cin >> decoratorOption;




				if (decoratorOption == "1" && decorator[0] == 0)
				{
					gameObserver = new PlayerDominationObserverDecorator(gameObserver);
					decorator[0] ++;
					lastAddedDecorator.push_back(new int(0));
					continue;
				}

				if (decoratorOption == "2" && decorator[1] == 0)
				{
					gameObserver = new PlayerHandsObserverDecorator(gameObserver);
					decorator[1] ++;
					lastAddedDecorator.push_back(new int(1));
					continue;
				}

				if (decoratorOption == "3" && decorator[2] == 0)
				{
					gameObserver = new ContinentControlObserverDecorator(gameObserver);
					decorator[2] ++;
					lastAddedDecorator.push_back(new int(2));
					continue;
				}

				if (decoratorOption == "4")
				{
					gameObserver = gameObserver->removeCurrentDecorator();
					if (lastAddedDecorator.size() > 0)
					{
						int temp = *lastAddedDecorator[lastAddedDecorator.size()-1];
						lastAddedDecorator.pop_back();
						decorator[temp] = 0;
						
					}
					continue;
				}

				if (decoratorOption == "5")
				{
					for (unsigned int i = 0; i < (decorator[0] + decorator[1] + decorator[2]); i++)
						gameObserver = gameObserver->removeCurrentDecorator();
					decorator[0] = 0;
					decorator[1] = 0;
					decorator[2] = 0;
					continue;
				}
				if (decoratorOption == "0" || decoratorOption == "")
				{
					break;
				}


			} while (true);
			//gameObserver = gameObserver->removeCurrentDecorator();
			//gameObserver = gameObserver->removeCurrentDecorator();
			//gameObserver = gameObserver->removeCurrentDecorator();

			//gameObserver = gameObserver->removeCurrentDecorator();
			//gameObserver = gameObserver->removeCurrentDecorator();




			for (unsigned int i = 0; i < players.size(); i++)
			{
				playerPhaseObservers.push_back(new PhaseObserver(players.at(i), mapp));

			}
			do {

				if (type == "1")
				{
					players[0]->setStrategy(human);
				}
				else if (type == "2")
				{
					players[0]->setStrategy(aggressive);
				}
				else if (type == "3")
				{
					players[0]->setStrategy(benevolent);
				}
				else if (type == "4")
				{
					players[0]->setStrategy(random);

				}
				else if (type == "5")
				{
					players[0]->setStrategy(cheater);
				}
				else
				{
					cout << "Invalid type. Please enter a number between 1, 2 and 3 only." << endl;
					again = true;
				}

				players[0]->play(players[0], mapp, deck);
				players[1]->setStrategy(human);
				players[2]->setStrategy(human);
				players[3]->setStrategy(human);
				//players[0]->setStrategy(human);

				players[1]->play(players[1], mapp, deck);
				players[2]->play(players[2], mapp, deck);
				players[3]->play(players[3], mapp, deck);
				//players[4]->play(players[4], mapp, deck);



				if (again == false)
				{
					cout << "\n***************************************" << endl;
					cout << "Do you want to change your type of player?" << endl;
					cout << "(1) : YES" << endl;
					cout << "(2) : NO" << endl;
					cout << "(3) : END PROGRAM" << endl;

					cout << "***************************************\n" << endl;
					cin >> redo;

					if (redo == "1")
					{
						again = true;
						again_with_same_type = false;
						break;
					}
					else if (redo == "2")
					{
						again_with_same_type = true;
						cout << "Continue with same type of player" << endl;
						break;
					}
					else if(redo == "3")
					{
						cout << "End of program." << endl;
						again = false;
						break;
					}
				}
			} while (true);
		} while (again_with_same_type);

	} while (again);


	return 0;
}