//#include "StrategyPattern.h"
//#include "Player.h"
//#include "Startup.h"
//#include <ctime>
//#include "GameObserver.h"
//
//using namespace std;
//
//int main() {
//
//	LOAD THE MAP
//	Map * map;
//	MapLoader maploader;
//	string mapFile = "maps/World.map";
//	map = new Map(mapFile);
//	maploader.readMapFile(mapFile, *map);
//
//	CREATE PLAYERS
//	 Comment or uncomment to test with different number of players
//	vector<Player*> players;
//	players.push_back(new Player("Jon", map));
//	players.push_back(new Player("Daenerys", map));
//	players.push_back(new Player("Cersei", map));
//	players.push_back(new Player("Tyrion", map));
//	players.push_back(new Player("Arya", map));
//	players.push_back(new Player("Sansa", map));
//
//	TEST THE STARTUP CLASS
//	Startup startup(players);
//
//	startup.distributeTerritories(*map);
//	startup.placeArmies(*map);
//
//	vector<string> cards = map->getAllTerritoryNames();
//	Deck deck(cards, cards.size());
//
//	Player* player = players[0];
//	Map* mapp = map;
//	HumanPlayer* human = new HumanPlayer();
//	AggressiveAI* aggressive = new AggressiveAI();
//	BenevolentAI* benevolent = new BenevolentAI();
//	RandomAI* random = new RandomAI();
//	CheaterAI* cheater = new CheaterAI();
//
//	string type, redo;
//	bool again;
//	int playerCards;
//
//	srand((unsigned)time(NULL));
//	vector<PhaseObserver*> playerPhaseObservers;
//
//	AbstractGameStatistics* gameObserver = new gameStatistics(&players, mapp);
//
//
//	do
//	{
//		again = false;
//
//		cout << "\n***************************************" << endl;
//		cout << "Please select your type of player:" << endl;
//		cout << "(1) : Human Player" << endl;
//		cout << "(2) : Aggressive AI Player" << endl;
//		cout << "(3) : Benevolent AI Player" << endl;
//		cout << "(4) : Random Player" << endl;
//		cout << "(5) : Cheater Player" << endl;
//		cout << "***************************************\n" << endl;
//
//		cin >> type;
//
//		apply decorators
//		gameObserver = new PlayerDominationObserverDecorator(gameObserver);
//		gameObserver = new PlayerHandsObserverDecorator(gameObserver);
//		gameObserver = new ContinentControlObserverDecorator(gameObserver);
//
//
//		for (unsigned int i = 0; i < players.size(); i++)
//		{
//			playerPhaseObservers.push_back(new PhaseObserver(players.at(i), mapp));
//
//		}
//		do {
//
//			if (type == "1")
//			{
//				players[0]->setStrategy(human);
//				players[0]->play(players[0], mapp, deck);
//			}
//			else if (type == "2")
//			{
//				players[1]->setStrategy(aggressive);
//				players[1]->play(players[1], mapp, deck);
//			}
//			else if (type == "3")
//			{
//				players[2]->setStrategy(benevolent);
//				players[2]->play(players[2], mapp, deck);
//			}
//			else if (type == "4")
//			{
//				players[3]->setStrategy(random);
//				players[3]->play(players[3], mapp, deck);
//
//			}
//			else if (type == "5")
//			{
//				players[4]->setStrategy(cheater);
//				players[4]->play(players[4], mapp, deck);
//			}
//			else
//			{
//				cout << "Invalid type. Please enter a number between 1, 2 and 3 only." << endl;
//				again = true;
//			}
//
//			if (again == false)
//			{
//				cout << "\n***************************************" << endl;
//				cout << "Do you want to change your type of player?" << endl;
//				cout << "(1) : YES" << endl;
//				cout << "(2) : NO" << endl;
//				cout << "(3) : END PROGRAM" << endl;
//
//				cout << "***************************************\n" << endl;
//				cin >> redo;
//
//				if (redo == "1")
//				{
//					again = true;
//					break;
//				}
//				else if (redo == "2")
//				{
//					cout << "Continue with same type of player" << endl;
//					continue;
//				}
//				else
//				{
//					cout << "End of program." << endl;
//					again = false;
//					break;
//				}
//			}
//		} while (true);
//
//	} while (again);
//
//
//	return 0;
//}