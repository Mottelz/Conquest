#include "StrategyPattern.h"
#include <ctime>

/**
* Returns the number of armies (as an int) that a player gets after exchanging cards.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
int Strategy::determineExchangedArmies(Player* player, Map* map, Deck& deck)
{
	int my_card;
	int exchangedArmies = 0;

	my_card = player->getHandSize();

	cout << player->getName() << " currently has " << my_card << " cards in their hand. " << endl;
	player->displayHand();
	if (player->exchangeableHand() == true)
	{
		if (my_card > 5)
		{
			cout << endl;
			cout << player->getName() << " has more than 5 cards and must exchange. " << endl;

			exchangedArmies = player->exchangeCardsAI(deck); // Uses the method to exchange cards for AI
		}
	}
	else
	{
		cout << endl;
		cout << player->getName() << " cannot exchange cards at this time. " << endl;
	}

	player->m_StatusInfo.phaseView = false;
	player->m_StatusInfo.currentPhase = REINFORCEMENT;
	player->m_StatusInfo.cardsView = true;
	player->notify();
	player->m_StatusInfo.cardsView = false;
	player->m_StatusInfo.phaseView = true;


	return exchangedArmies;
}

/**
* Places armies to place.
* \param assign_to ID of territory being applied.
* \param place_num Number of territories to place.
* \param map The map.
*/
void Strategy::placeArmiesDuringReinforcement(int assign_to, int place_num, Player* player, Map* map)
{
	for (int i = 0; i < place_num; i++)
	{
		map->assignArmies(player, map->getTerritoryName(assign_to));
	}

}

/**
* Moves armies around.
* \param move_from ID where the troops are moving from.
* \param move_to ID where the troops are moving to.
* \param move_num Number of people moving.
* \param map The map where this is all taking place.
*/
void Strategy::moveArmiesDuringFortification(int move_from, int move_to, int move_num, Player* player, Map * map)
{
	for (int i = 0; i < move_num; i++)
	{
		map->removeArmies(player, map->getTerritoryName(move_from));
		map->assignArmies(player, map->getTerritoryName(move_to));

	}
}

/**
* Method that triggers an automatic dice battle for AI.
* \param from ID of territory we're attacking from.
* \param to ID of territory being attacked.
* \param player Pointer to the player
* \param map The map where the battle is taking place.
*/
void Strategy::engageInBattle(int from, int to, Player* player, Map* map)
{
	vector<int> myRolledList, enemyRolledList;
	Player * enemy = map->getOwnerOfTheTerritory(to);


	cout << "The Attaker, Player " << player->getPlayerID() << ": " << player->getName() << " is about to shake the dice cup. " << endl;
	myRolledList = shakeDiceCup(map->getArmyNumOfTheTerritory(from), ATTACK, player);

	cout << "The Defender, Player " << enemy->getPlayerID() << ": "
		<< enemy->getName() << " is about to shake the dice cup. " << endl;
	enemyRolledList = shakeDiceCup(map->getArmyNumOfTheTerritory(to), DEFENSE, player);

	for (int i = 0; i < myRolledList.size(); i++) {
		if (i == 0)
		{
			cout << "The Attaker, Player " << player->getPlayerID() << ": " << player->getName() << " rolled: ";
			cout << myRolledList[i];
		}
		else
		{
			cout << " | " << myRolledList[i];
		}
	}
	cout << endl;

	for (int i = 0; i < enemyRolledList.size(); i++) {
		if (i == 0)
		{
			cout << "The Defender, Player " << enemy->getPlayerID() << ": "
				<< enemy->getName() << " rolled: ";
			cout << enemyRolledList[i];
		}
		else
		{
			cout << " | " << enemyRolledList[i];
		}
	}
	cout << endl;


	int armiesInBattle = myRolledList.size() < enemyRolledList.size() ? myRolledList.size() : enemyRolledList.size();
	cout << "Rolled Dice Pairs: " << armiesInBattle << endl;

	for (int i = 0; i < armiesInBattle; i++)
	{
		cout << myRolledList[i] << " VS " << enemyRolledList[i] << " : ";
		if (myRolledList[i] > enemyRolledList[i])
		{
			cout << myRolledList[i] << " > " << enemyRolledList[i] << " --> ";
			cout << "Player " << enemy->getPlayerID() << ", "
				<< enemy->getName() << ", lost one army. " << endl;
			map->removeArmies(enemy, map->getTerritoryName(to));

		}
		else
		{
			cout << myRolledList[i] << " <= " << enemyRolledList[i] << " --> ";
			cout << "Player " << player->getPlayerID() << ", "
				<< map->getOwnerOfTheTerritory(from)->getName() << ", lost one army. " << endl;
			map->removeArmies(player, map->getTerritoryName(from));
		}
	}
}


/**
* Automatically rolls the largest possible number of dice for the aggressive AI.
* \param armiesOfATerri Number of armies of the territory passed
* \param phase The phase during which this method is called
* \param player A pointer to the player
*/
vector<int> Strategy::shakeDiceCup(int armiesOfATerri, PlayerPhase phase, Player* player)
{
	int numOfDice;
	if (phase == ATTACK)
	{
		numOfDice = armiesOfATerri - 1;

		if (numOfDice > 3)
		{
			numOfDice = 3;
			return (player->shakeDiceCup(numOfDice));
		}
		else if (numOfDice == 2 || numOfDice == 3)// logic error missing case numOfDice == 3
		{
			return (player->shakeDiceCup(numOfDice));
		}
		else // if numOfDice == 1
		{
			cout << player->getName() << " is only allowed to roll 1 dice for the current battle. " << endl;
			return (player->shakeDiceCup(numOfDice));
		}
	}
	else // if player is defending
	{
		numOfDice = armiesOfATerri;

		if (numOfDice > 2)
		{
			numOfDice = 2;
			return (player->shakeDiceCup(numOfDice));
		}
		else // if numOfDice = 1
		{
			return (player->shakeDiceCup(numOfDice));
		}
	}
}



/**
* The method for the reinforcement phase during the human player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
void HumanPlayer::reinforce(Player* player, Map* map, Deck& deck)
{
	//Reinforce, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = REINFORCEMENT;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->m_StatusInfo.cardsView = true;
	player->m_StatusInfo.contiView = true;
	player->notify();
	player->m_StatusInfo.contiView = false;
	player->m_StatusInfo.cardsView = false;
	player->m_StatusInfo.globalView = false;

	int assign_terri_ID = -1, assign_num = 0;

	int exchangedArmies = determineExchangedArmies(player, map, deck);

	int valid_assigned_armies = player->assignedAvailableArmies(exchangedArmies);

	do {
		cout << "You have " << valid_assigned_armies << " troop(s) left to deploy." << endl;
		//choose territory attack from
		cout << "Please select ID of the territory where you want to assign your armies: " << endl;
		cin >> assign_terri_ID;

		if (assign_terri_ID >= 0)
		{
			if ((map->getOwnerOfTheTerritory(assign_terri_ID)) != player)
			{
				cout << "INVALID INPUT: the territory that you select is not your territory. " << endl;
				continue;
			}
		}
		else
		{
			cout << "INVALID INPUT: invalid territory ID. " << endl;
			continue;
		}

		do {
			cout << "Please enter the number of armies that you want to place on this territory: " << endl;
			cin >> assign_num;

			if (assign_num >= 0 && assign_num <= valid_assigned_armies)
			{
				placeArmiesDuringReinforcement(assign_terri_ID, assign_num, player, map);
				valid_assigned_armies -= assign_num;
				//Reinforce selected terri notify update
				player->m_StatusInfo.currentSelectedTerriID = assign_terri_ID;
				player->m_StatusInfo.statusType = mySpecificTerritory;
				player->notify();
				break;
			}
			else
			{
				cout << "INVALID INPUT " << endl;
			}
		} while (true);

		cout << endl;

	} while (valid_assigned_armies > 0);

	//Reinforce all terri notify 
	player->m_StatusInfo.statusType = myTerritories;
	player->notify();
	//Reinforce, notify counting -1, end of this phase
	player->m_StatusInfo.statusType = myPhaseEnded;
	player->notify();

}

/**
* Returns the number of armies (as an int) that a player gets after exchanging cards.
* Overrides the Strategy method to allow user input.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
int HumanPlayer::determineExchangedArmies(Player* player, Map* map, Deck& deck)
{
	int my_card;
	int exchangedArmies = 0;

	my_card = player->getHandSize();

	//**??Notify cards in hand?
	cout << "Currently, you have " << my_card << " cards in your hand. " << endl;
	player->displayHand();
	if (player->exchangeableHand() == true)
	{
		cout << "Your have exchangeable cards. " << endl;
		if (my_card > 5)
		{
			cout << "Since you have more than 5 cards you must exchange. " << endl;

			while (exchangedArmies == 0)
				exchangedArmies = player->exchangeCards(deck);
			//hand update
			player->m_StatusInfo.phaseView = false;
			player->m_StatusInfo.currentPhase = REINFORCEMENT;
			player->m_StatusInfo.cardsView = true;
			player->notify();
			player->m_StatusInfo.cardsView = false;
			player->m_StatusInfo.phaseView = true;
		}
		else
		{
			string exchange = "";
			do {
				cout << "Do you want to exchange your cards? [Y/N] " << endl;
				cin >> exchange;
				if (exchange == "Y" || exchange == "y")
				{
					exchangedArmies = player->exchangeCards(deck);
					//hand update
					if (exchangedArmies != 0)
					{
						player->m_StatusInfo.phaseView = false;
						player->m_StatusInfo.currentPhase = REINFORCEMENT;
						player->m_StatusInfo.cardsView = true;
						player->notify();
						player->m_StatusInfo.cardsView = false;
						player->m_StatusInfo.phaseView = true;

						break;
					}
				}
				else if (exchange == "N" || exchange == "n")
				{
					exchangedArmies = 0;
					break;
				}
				else
				{
					cout << "INVALID INPUT " << endl;
				}
			} while (true);
		}
	}
	else
	{
		cout << "You cannot exchange cards at this time. " << endl;
	}

	return exchangedArmies;
}

/**
* The method for the attack phase during the human player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
bool HumanPlayer::attack(Player* player, Map* map)
{
	//Attack, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = ATTACK;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->m_StatusInfo.contiView = true;
	player->notify();
	player->m_StatusInfo.contiView = false;
	player->m_StatusInfo.globalView = false;

	bool attack_state;

	string atk = "";

	do {
		
		cout << "Do you want to attack? <Y/N> " << endl;
		cin >> atk;
		if (atk == "Y" || atk == "y")
		{
			attack_state = true;
			break;
		}
		else
		{
			if (atk == "N" || atk == "n")
			{
				attack_state = false;
				break;
			}
			else
			{
				cout << "INVALID INPUT " << endl;
			}
		}
	} while (true);

	if (attack_state == true)
	{

		int attack_from = -1, attack_to = -1;

		do {
			//choose territory attack from
			cout << "Please select the territory ID (integer) that you want to attack from: " << endl;
			cout << "** -1 for ending attack phase" << endl;
			cin >> attack_from;

			if (attack_from == -1)
			{
				//Notify: end of this phase
				player->m_StatusInfo.statusType = myPhaseEnded;
				player->notify();
				return false;
			}
			else
				if (attack_from >= 0)
				{
					if ((map->getOwnerOfTheTerritory(attack_from)) == player)
					{
						if (map->getArmyNumOfTheTerritory(attack_from) > 1)
						{
							if (!map->enemyNeighbourExists(attack_from))
							{
								cout << "INVALID INPUT: you must choose one of your territories having at least one enemy neighbour. " << endl;
								continue;
							}
						}
						else
						{
							cout << "INVALID INPUT: you must choose one of your territories assigned more than one armies. " << endl;
							continue;
						}
					}
					else
					{
						cout << "INVALID INPUT: the territory that you select is not your territory. " << endl;
						continue;
					}
				}
				else
				{
					cout << "INVALID INPUT: invalid territory ID. " << endl;
					continue;
				}

			//Attack, notify enemylist
			player->m_StatusInfo.currentSelectedTerriID = attack_from;
			player->m_StatusInfo.statusType = myEnemyList;
			player->notify();

			//choose territory attack to 
			cout << "Please select the adjacent territory ID (integer) that you want to attack to: " << endl;
			cout << "** -1 for ending attack phase" << endl;
			cin >> attack_to;
			if (attack_to == -1)
			{
				//Attack, notify counting -1, phase ending
				player->m_StatusInfo.statusType = myPhaseEnded;
				player->notify();
				return false;
			}
			else
				if (attack_to >= 0)
				{
					if (map->isAdjacent(attack_from, attack_to))
					{
						if ((map->getOwnerOfTheTerritory(attack_to)) != player)
						{
							break;
						}
						else
						{
							cout << "INVALID INPUT: the territory that you select is your territory. " << endl;
							//continue;
						}
					}
					else
					{
						cout << "INVALID INPUT: you can only attack your neighbour territory. " << endl;
						//continue;
					}
				}
				else
				{
					cout << "INVALID INPUT: invalid territory ID. " << endl;
					//continue;
				}

		} while (true);


		while (true)
		{
			cout << "--------------------------------" << endl;

			if (map->getArmyNumOfTheTerritory(attack_from) > 1)
			{
				if (map->getArmyNumOfTheTerritory(attack_to) > 0)
				{
					engageInBattle(attack_from, attack_to, player, map);
					
					//Attack, notify, selected terri -> attack from
					player->m_StatusInfo.currentSelectedTerriID = attack_from;
					player->m_StatusInfo.statusType = mySpecificTerritory;
					player->notify();
					//Attack, notify, selected terri -> attack to
					player->m_StatusInfo.currentSelectedTerriID = attack_to;
					player->notify();

					if (map->getArmyNumOfTheTerritory(attack_from) > 1 && map->getArmyNumOfTheTerritory(attack_to) > 0)
					{
						bool change_terri;
						do
						{
							cout << "Do you want to keep attacking this territory? [Y/N] " << endl;
							cin >> atk;

							if (atk == "Y" || atk == "y")
							{
								change_terri = false;
								break;
							}
							else
							{
								if (atk == "N" || atk == "n")
								{
									change_terri = true;
									break;
								}
								else
								{
									cout << "INVALID INPUT " << endl;
								}
							}
						} while (true);
						if (change_terri)
							break;
					}
				}
				else
				{
					int assign_num_of_armies;
					cout << "Congradulations! You win the battle." << endl;
					if (map->getArmyNumOfTheTerritory(attack_from) == 2)
					{
						cout << "You can only assign one army to capture the territory." << endl;;
						assign_num_of_armies = 1;
					}
					else
					{

						while (true)
						{
							cout << "Please assign a number of armies to caputre the territory (1-"
								<< map->getArmyNumOfTheTerritory(attack_from) - 1
								<< "): " << endl;
							cin >> assign_num_of_armies;
							if (assign_num_of_armies > 0 && assign_num_of_armies < map->getArmyNumOfTheTerritory(attack_from))
							{
								break;
							}
							else
							{
								cout << "INVALID INPUT: out of range. " << endl;
							}
						}
					}

					for (int i = 0; i < assign_num_of_armies; i++)
					{
						map->removeArmies(player, map->getTerritoryName(attack_from));
						map->assignArmies(player, map->getTerritoryName(attack_to));
					}

					cout << "Territory captured. " << endl;
					//Attack, notify player status
					//player->m_StatusInfo.statusType = myTerritories;
					//player->m_StatusInfo.globalView = true;
					//player->notify();
					//player->m_StatusInfo.globalView = false;
					break;
				}

			}
			else
			{
				cout << "You do not have enough armies in your current territory, " << map->getTerritoryName(attack_from) << ". " << endl;
				cout << "You failed the battle. " << endl;
				////Attack, notify player status
				//player->m_StatusInfo[1] = 0;
				//player->notify();

				break;
			}
		}
		cout << endl;
		//Attack, notify player status
		player->m_StatusInfo.statusType = myTerritories;
		player->m_StatusInfo.globalView = true;
		player->m_StatusInfo.contiView = true;
		player->notify();
		player->m_StatusInfo.contiView = false;
		player->m_StatusInfo.globalView = false;

		return true;
	}
	else
	{
		//Attack, notify counting -1, phase ending
		player->m_StatusInfo.statusType = myPhaseEnded;
		player->notify();
		return false;
	}
	return false;
}

/**
* Method that actually triggers a dice battle.
* \param from ID of territory we're attacking from.
* \param to ID of territory being attacked.
* \param player Pointer to the player // no need since the from ID has already been checked
* \param map The map where the battle is taking place.
*/
void HumanPlayer::engageInBattle(int from, int to, Player* player, Map* map)
{
	vector<int> myRolledList, enemyRolledList;

	Player * enemy = map->getOwnerOfTheTerritory(to);

	cout << "The Attaker, Player " << player->getPlayerID() << ": " << player->getName() << " is about to shake the dice cup. " << endl;
	myRolledList = shakeDiceCup(map->getArmyNumOfTheTerritory(from), ATTACK, player);

	cout << "The Defender, Player " << enemy->getPlayerID() << ": "
		<< enemy->getName() << " is about to shake the dice cup. " << endl;
	enemyRolledList = shakeDiceCup(map->getArmyNumOfTheTerritory(to), DEFENSE, player);//here is the current player or enemy?? & why need player param??

	for (int i = 0; i < myRolledList.size(); i++) {
		if (i == 0)
		{
			cout << "The Attaker, Player " << player->getPlayerID() << ": " << player->getName() << " rolled: ";
			cout << myRolledList[i];
		}
		else
		{
			cout << " | " << myRolledList[i];
		}
	}
	cout << endl;

	for (int i = 0; i < enemyRolledList.size(); i++) {
		if (i == 0)
		{
			cout << "The Defender, Player " << enemy->getPlayerID() << ": "
				<< enemy->getName() << " rolled: ";
			cout << enemyRolledList[i];
		}
		else
		{
			cout << " | " << enemyRolledList[i];
		}
	}
	cout << endl;


	int armiesInBattle = myRolledList.size() < enemyRolledList.size() ? myRolledList.size() : enemyRolledList.size();
	cout << "Rolled Dice Pairs: " << armiesInBattle << endl;

	for (int i = 0; i < armiesInBattle; i++)
	{
		cout << myRolledList[i] << " VS " << enemyRolledList[i] << " : ";
		if (myRolledList[i] > enemyRolledList[i])
		{
			cout << myRolledList[i] << " > " << enemyRolledList[i] << " --> ";
			cout << "Player " << enemy->getPlayerID() << ", "
				<< enemy->getName() << ", lost one army. " << endl;
			map->removeArmies(enemy, map->getTerritoryName(to));
			
		}
		else
		{
			cout << myRolledList[i] << " <= " << enemyRolledList[i] << " --> ";
			cout << "Player " << player->getPlayerID() << ", "
				<< map->getOwnerOfTheTerritory(from)->getName() << ", lost one army. " << endl;
			map->removeArmies(player, map->getTerritoryName(from));
		}
	}
}

/**
* Prompts user to select the number of dice they wish to roll.
* \param armiesOfATerri Number of armies of the territory passed
* \param phase The phase during which this method is called
* \param player A pointer to the player
*/
vector<int> HumanPlayer::shakeDiceCup(int armiesOfATerri, PlayerPhase phase, Player* player)
{
	int numOfDice;
	int maxDiceLimit;
	if (phase == ATTACK)
	{
		maxDiceLimit = armiesOfATerri - 1;
		if (maxDiceLimit > 3)
		{
			maxDiceLimit = 3;
		}
	}
	else
	{
		maxDiceLimit = armiesOfATerri;
		if (maxDiceLimit > 2)
		{
			maxDiceLimit = 2;
		}
	}

	if (maxDiceLimit == 1)
	{
		cout << "You are only allowed to roll 1 dice for the current battle. " << endl;
		cout << endl;
		numOfDice = 1;
		return (player->shakeDiceCup(numOfDice));
	}
	else
	{

		do {

			cout << "Please choose the number of dice that you want to roll (1-" << maxDiceLimit << "):" << endl;
			cin >> numOfDice;
			cout << endl;
			if (numOfDice > 0 && numOfDice <= maxDiceLimit)
			{
				break;
			}
			else
			{
				cout << "INVALID INPUT: invalid dice number. " << endl;
				cout << endl;
			}
		} while (true);
		return (player->shakeDiceCup(numOfDice));
	}
}

/**
* The method for the fortification phase during the human player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
bool HumanPlayer::fortify(Player* player, Map* map)
{
	//Fortify, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = FORTIFICATION;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->notify();
	player->m_StatusInfo.globalView = false;

	bool fortify_state, verified_input = false ;

	string ftf = "";

	do {
		cout << "Do you want to fortify? <Y/N> " << endl;
		cin >> ftf;
		if (ftf == "Y" || ftf == "y")
		{
			fortify_state = true;
			break;
		}
		else
		{
			if (ftf == "N" || ftf == "n")
			{
				return false;
			}
			else
			{
				cout << "INVALID INPUT " << endl;
			}
		}
	} while (true);

	if (fortify_state == true)
	{
		int move_from = -1, move_to = -1, move_num = 0;
		vector<string> fortifyPath;
		do
		{
			cout << "Please select the source territory ID (integer) that you want to move your armies from: " << endl;
			cout << "** -1 for ending fortification phase" << endl;
			cin >> move_from;
			if (move_from == -1)
			{
				//Fortify, notify PLAYER STATUS
				player->m_StatusInfo.statusType = myTerritories;
				player->notify();
				//Fortify, notify end of phase
				player->m_StatusInfo.statusType = myPhaseEnded;
				player->notify();
				return false;
			}
			else
				if (move_from >= 0)
				{
					if ((map->getOwnerOfTheTerritory(move_from)) == player)
					{
						if (map->getArmyNumOfTheTerritory(move_from) > 1)
						{
							if (!map->friendNeighbourExists(move_from))
							{
								cout << "INVALID INPUT: you must choose one of your territories having at least one friend neighbour. " << endl;
								continue;
							}// notify the selected terri? & valid terri list of move to?
							else
							{
								//Fortify, notify the selected terri
								player->m_StatusInfo.currentSelectedTerriID = move_from;
								player->m_StatusInfo.statusType = myPathList;
								player->notify();

							}
						}
						else
						{
							cout << "INVALID INPUT: you must choose one of your territories assigned more than one armies. " << endl;
							continue;
						}
					}
					else
					{
						cout << "INVALID INPUT: the territory that you select is not your territory. " << endl;
						continue;
					}
				}
				else
				{
					cout << "INVALID INPUT: invalid territory ID. " << endl;
					continue;
				}

			do {
				//choose territory move to 
				cout << "Please select the target territory ID (integer) that you want to move your armies to: " << endl;
				cout << "** -1 for ending fortification phase" << endl;
				cout << "** -2 for re-select source territory" << endl;
				cin >> move_to;
				if (move_to == -1 || move_to == -2)
				{
					if (move_to == -1)
					{
						//Fortify, notify PLAYER STATUS
						player->m_StatusInfo.statusType = myTerritories;
						player->notify();
						//Fortify, notify end of phase
						player->m_StatusInfo.statusType = myPhaseEnded;
						player->notify();
						return false;
					}
					if (move_to == -2)
					{
						break;
					}
				}
				else
					if (move_to >= 0)
					{
						fortifyPath.clear();
						if (map->seekPath(player, map->getTerritoryName(move_from), map->getTerritoryName(move_to), fortifyPath))
						{
							do {

								cout << "Please enter the number of armies that you want to fortify (0-"
									<< map->getArmyNumOfTheTerritory(move_from) - 1 << "): " << endl;
								cin >> move_num;
								if (move_num >= 0 && move_num <= map->getArmyNumOfTheTerritory(move_from) - 1)
								{
									verified_input = true;
									break;
								}
								else
								{
									cout << "INVALID INPUT " << endl;
								}

							} while (true);
							break;
						}
						else
						{
							cout << "INVALID INPUT: invalid territory ID. " << endl;
						}
					}
			} while (true);

			if (verified_input == true)
				break;

		} while (true);

		moveArmiesDuringFortification(move_from, move_to, move_num, player, map);
		//Fortify, notify the selected terri : source terri
		player->m_StatusInfo.currentSelectedTerriID = move_from;
		player->m_StatusInfo.statusType = mySpecificTerritory;
		player->notify();
		//Fortify, notify the selected terri : target terri
		player->m_StatusInfo.currentSelectedTerriID = move_to;
		player->notify();

		return true;
	}
	else
	{
		//Fortify, notify PLAYER STATUS
		player->m_StatusInfo.statusType = myTerritories;
		player->notify();
		//Fortify, notify end of phase
		player->m_StatusInfo.statusType = myPhaseEnded;
		player->notify();
		return false;
	}
}

/**
* This method has no current implementation for the human player.
* \param player A pointer to the current player
* \param map A pointer to the map
* \param move_to The territory ID of the territory we move armies to
*/
int HumanPlayer::territoryToMoveArmyFrom(Player* player, Map* map, int move_to)
{
	// No implementation
	return -1;
}

/**
* Calls the methods for the different phases of the human player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
void HumanPlayer::play(Player* player, Map* map, Deck& deck)
{
	reinforce(player, map, deck);
	while(attack(player, map));
	while(fortify(player, map));
}

/**
* The method for the reinforcement phase during the aggressive player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
void AggressiveAI::reinforce(Player* player, Map* map, Deck& deck)
{
	
	//Reinforce, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = REINFORCEMENT;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->m_StatusInfo.cardsView = true;
	player->m_StatusInfo.contiView = true;
	player->notify();
	player->m_StatusInfo.contiView = false;
	player->m_StatusInfo.cardsView = false;
	player->m_StatusInfo.globalView = false;

	int exchangedArmies = determineExchangedArmies(player, map, deck);

	int valid_assigned_armies = player->assignedAvailableArmies(exchangedArmies);

	cout << player->getName() << " (aggressive AI) has " << valid_assigned_armies << " troop(s) left to deploy." << endl;
	cout << player->getName() << " wants to assign their armies to : ";

	int assign_terri_ID = getStrongestTerritory(player, map, REINFORCEMENT);

	cout << map->getTerritoryName(assign_terri_ID) << endl;

	// Aggressive AI will place all its available armies on its strongest country
	cout << player->getName() << " is going to place " << valid_assigned_armies << " armies on " << map->getTerritoryName(assign_terri_ID) << endl;
	placeArmiesDuringReinforcement(assign_terri_ID, valid_assigned_armies, player, map);

	player->m_StatusInfo.phaseView = false;
	player->m_StatusInfo.currentPhase = REINFORCEMENT;
	player->m_StatusInfo.cardsView = true;
	player->notify();
	player->m_StatusInfo.cardsView = false;
	player->m_StatusInfo.phaseView = true;


	cout << endl;
	//Reinforce all terri notify 
	player->m_StatusInfo.statusType = myTerritories;
	player->notify();
	//Reinforce, notify counting -1, end of this phase
	player->m_StatusInfo.statusType = myPhaseEnded;
	player->notify();

}

/**
* Returns the aggressive player's strongest territory (under different conditions according to the phase).
* \param player A pointer to the current player
* \param map A pointer to the map
* \param phase The phase during which this method is called
*/
int AggressiveAI::getStrongestTerritory(Player* player, Map* map, PlayerPhase phase)
{
	vector<string> playerTerritories = player->getPlayerTerritoryNames();
	int biggestArmy = map->getArmyNumOfTheTerritory(map->seekTerritoryID(playerTerritories[0]));
	int thisArmy;
	int assign_terri_ID = map->seekTerritoryID(playerTerritories[0]);

	// Look for the territory with the most armies
	
	if (phase == ATTACK)
	{
		for (int i = 1; i < playerTerritories.size(); i++)
		{
			thisArmy = map->getArmyNumOfTheTerritory(map->seekTerritoryID(playerTerritories[i]));
			if (thisArmy > biggestArmy && map->enemyNeighbourExists(map->seekTerritoryID(playerTerritories[i])))
			{
				biggestArmy = thisArmy;
				assign_terri_ID = map->seekTerritoryID(playerTerritories[i]);
			}
		}

		if (map->enemyNeighbourExists(assign_terri_ID) == false || biggestArmy == 1)
			return -1;
	}
	else if (phase == FORTIFICATION)
	{
		for (int i = 1; i < playerTerritories.size(); i++)
		{
			thisArmy = map->getArmyNumOfTheTerritory(map->seekTerritoryID(playerTerritories[i]));
			if (thisArmy > biggestArmy && map->friendNeighbourExists(map->seekTerritoryID(playerTerritories[i])))
			{
				biggestArmy = thisArmy;
				assign_terri_ID = map->seekTerritoryID(playerTerritories[i]);
			}
		}
		if (map->friendNeighbourExists(assign_terri_ID) == false)
			return -1;
	}
	else // phase == REINFORCEMENT
	{
		for (int i = 1; i < playerTerritories.size(); i++)
		{
			thisArmy = map->getArmyNumOfTheTerritory(map->seekTerritoryID(playerTerritories[i]));
			if (thisArmy > biggestArmy)
			{
				biggestArmy = thisArmy;
				assign_terri_ID = map->seekTerritoryID(playerTerritories[i]);
			}
		}
	}
	
	return assign_terri_ID;
}

/**
* The method for the attack phase during the aggressive player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
bool AggressiveAI::attack(Player* player, Map* map)
{
	//Attack, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = ATTACK;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->m_StatusInfo.contiView = true;
	player->notify();
	player->m_StatusInfo.contiView = false;
	player->m_StatusInfo.globalView = false;

	cout << "\n***************************************" << endl;
	cout << player->getName() << " wants to attack! " << endl;
	cout << "***************************************\n" << endl;


	int attack_from = getStrongestTerritory(player, map, ATTACK);
	if (attack_from == -1) // Not enough armies to attack
	{
		cout << player->getName() << " has too few armies! " << endl;
		//Attack, notify, end of phase
		player->m_StatusInfo.statusType = myPhaseEnded;
		player->m_StatusInfo.globalView = true;
		player->m_StatusInfo.contiView = true;
		player->notify();
		player->m_StatusInfo.contiView = false;
		player->m_StatusInfo.globalView = false;
		return false;
	}

	cout << player->getName() << " is going to attack from: " << map->getTerritoryName(attack_from) << endl;

	///Attack, notify current selected terri
	player->m_StatusInfo.currentSelectedTerriID = attack_from;
	player->m_StatusInfo.statusType = mySpecificTerritory;
	player->notify();

	//Attack, notify enemylist
	player->m_StatusInfo.currentSelectedTerriID = attack_from;
	player->m_StatusInfo.statusType = myEnemyList;
	player->notify();

	int attack_to = getWeakestEnemyTerritory(attack_from, map);
	if (attack_to == -1) // No territory to attack
	{
		cout << player->getName() << " cannot find adjacent enemies! " << endl;

		//Attack, notify, end of phase
		player->m_StatusInfo.statusType = myPhaseEnded;
		player->notify();
		return false;
	}

	cout << player->getName() << " is going to attack to: " << map->getTerritoryName(attack_to) << endl;
	
	bool territoryCaptured = false;
	while (!territoryCaptured)
	{
		cout << "--------------------------------" << endl;

		if (map->getArmyNumOfTheTerritory(attack_from) > 1)
		{
			if (map->getArmyNumOfTheTerritory(attack_to) > 0)
			{
				engageInBattle(attack_from, attack_to, player, map);
				//Attack, notify, selected terri -> attack from
				player->m_StatusInfo.currentSelectedTerriID = attack_from;
				player->m_StatusInfo.statusType = mySpecificTerritory;
				player->notify();
				//Attack, notify, selected terri -> attack to
				player->m_StatusInfo.currentSelectedTerriID = attack_to;
				player->notify();

			}
			else
			{
				cout << player->getName() << " won the battle! " << endl;
				int numberOfArmies = map->getArmyNumOfTheTerritory(attack_from);
				for (int i = 0; i < numberOfArmies-1 ; i++)
				{
					map->removeArmies(player, map->getTerritoryName(attack_from));
					map->assignArmies(player, map->getTerritoryName(attack_to));
				}
				cout << player->getName() << " moved " << numberOfArmies - 1 << " armies to " << map->getTerritoryName(attack_to) << endl;
				territoryCaptured = true;
				//Attack, notify player status
				player->m_StatusInfo.statusType = myTerritories;
				player->m_StatusInfo.globalView = true;
				player->m_StatusInfo.contiView = true;
				player->notify();
				player->m_StatusInfo.contiView = false;
				player->m_StatusInfo.globalView = false;
			}
		}
		else
		{
			cout << player->getName() << " failed the battle. " << endl;
			//Attack, notify player status
			player->m_StatusInfo.statusType = myTerritories;
			player->m_StatusInfo.globalView = true;
			player->m_StatusInfo.contiView = true;
			player->notify();
			player->m_StatusInfo.contiView = false;
			player->m_StatusInfo.globalView = false;
			break;
		}
	}
	return true;
}

/**
* Returns the territory ID of the weakest enemy for the aggressive player to attack.
* \param attack_from The territory ID of the attacking territory
* \param map A pointer to the map
*/
int AggressiveAI::getWeakestEnemyTerritory(int attack_from, Map* map)
{
	vector<string> neighbourTerritories = map->getEnemyAdjacentTerritoryNames(attack_from);

	if (neighbourTerritories.size() == 0)
		return -1;

	int weakestArmy = map->getArmyNumOfTheTerritory(map->seekTerritoryID(neighbourTerritories[0]));
	int thisArmy;
	int targetEnemyID = map->seekTerritoryID(neighbourTerritories[0]);

	// Look for the territory with the most armies
	for (int i = 1; i < neighbourTerritories.size(); i++)
	{
		thisArmy = map->getArmyNumOfTheTerritory(map->seekTerritoryID(neighbourTerritories[i]));
		if (thisArmy < weakestArmy && map->getOwnerOfTheTerritory(map->seekTerritoryID(neighbourTerritories[i])) != map->getOwnerOfTheTerritory(attack_from))
		{
			weakestArmy = thisArmy;
			targetEnemyID = map->seekTerritoryID(neighbourTerritories[i]);
		}
	}

	return targetEnemyID;
}


/**
* The method for the fortification phase during the aggressive player's turn.
* \param attack_from The territory ID of the attacking territory
* \param map A pointer to the map
*/
bool AggressiveAI::fortify(Player* player, Map* map)
{
	//Fortify, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = FORTIFICATION;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->notify();
	player->m_StatusInfo.globalView = false;

	int move_to = getStrongestTerritory(player, map, FORTIFICATION); 
	int move_from = territoryToMoveArmyFrom(player, map, move_to);
	int move_num = 0;
	vector<string> fortifyPath;
		
	if (move_to > -1 && move_from > -1 && map->getArmyNumOfTheTerritory(move_from) > 1)
	{
		if (map->seekPath(player, map->getTerritoryName(move_from), map->getTerritoryName(move_to), fortifyPath))
		{
			
			cout << "\n***************************************" << endl;
			cout << player->getName() << " wants to fortify! " << endl;
			cout << "***************************************\n" << endl;
			
			move_num = map->getArmyNumOfTheTerritory(move_from) - 1; // moves all armies except one
			moveArmiesDuringFortification(move_from, move_to, move_num, player, map);
			cout << endl;
			cout << player->getName() << " Moved " << move_num << " armies from " << map->getTerritoryName(move_from) << " to " << map->getTerritoryName(move_to) << endl;
		}
	}
	else
	{
		cout << endl;
		cout << player->getName() << " cannot fortify at the moment (too few countries). " << endl;
		//Fortify, notify, end of phase
		player->m_StatusInfo.statusType = myPhaseEnded;
		player->notify();
		return false;
	}

	//Fortify, notify, end of phase
	player->m_StatusInfo.statusType = myPhaseEnded;
	player->notify();

	return false;
}

/**
* Determines the territory that will give an army to another friendly territory.
* Returns the ID if there is a valid territory, or -1 if no valid territory is found.
* \param player A pointer to the current player
* \param map A pointer to the map
* \param move_to The territory ID of the territory we move armies to
*/
int AggressiveAI::territoryToMoveArmyFrom(Player* player, Map* map, int move_to)
{
	vector<string> neighbourTerritories = map->getFriendlyAdjacentTerritoryNames(move_to);

	if (neighbourTerritories.size() == 0)
		return -1;

	int thisArmy, thisID;

	for (int i = 0; i < neighbourTerritories.size(); i++)
	{
		thisID = map->seekTerritoryID(neighbourTerritories[i]);
		thisArmy = map->getArmyNumOfTheTerritory(thisID);

		if (thisArmy > 1 && thisID != move_to)
		{
			return thisID;
		}
	}

	return -1;
}

/**
* Calls the methods for the different phases of the aggressive player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
void AggressiveAI::play(Player* player, Map* map, Deck& deck)
{
	reinforce(player, map, deck);
	
	while(attack(player, map));

	while(fortify(player, map));

	cout << "\n***************************************" << endl;
	cout << "End of  " << player->getName() << "'s turn! " << endl;
	cout << "***************************************\n" << endl;
}

/**
* Returns the benevolent player's weakest territory (under different conditions according to the phase).
* \param player A pointer to the current player
* \param map A pointer to the map
* \param phase The phase during which this method is called
*/
int BenevolentAI::getWeakestTerritory(Player* player, Map* map, PlayerPhase phase)
{
	vector<string> playerTerritories = player->getPlayerTerritoryNames();

	int weakestArmy = map->getArmyNumOfTheTerritory(map->seekTerritoryID(playerTerritories[0]));
	int thisArmy, thisID;
	int weakestTerritoryID = map->seekTerritoryID(playerTerritories[0]);

	if (phase == FORTIFICATION)
	{
		for (int i = 1; i < playerTerritories.size(); i++)
		{
			thisID = map->seekTerritoryID(playerTerritories[i]);
			thisArmy = map->getArmyNumOfTheTerritory(map->seekTerritoryID(playerTerritories[i]));
			if (thisArmy < weakestArmy && map->friendNeighbourExists(thisID) && hasValidNeighbour(thisID, map))
			{
				weakestArmy = thisArmy;
				weakestTerritoryID = map->seekTerritoryID(playerTerritories[i]);
			}
		}

		if (map->friendNeighbourExists(weakestTerritoryID) == false || hasValidNeighbour(weakestTerritoryID, map) == false)
			return -1;
	}
	else // phase == REINFORCEMENT
	{
		for (int i = 1; i < playerTerritories.size(); i++)
		{
			thisArmy = map->getArmyNumOfTheTerritory(map->seekTerritoryID(playerTerritories[i]));
			if (thisArmy < weakestArmy)
			{
				weakestArmy = thisArmy;
				weakestTerritoryID = map->seekTerritoryID(playerTerritories[i]);
			}
		}
	}

	return weakestTerritoryID;

}

/**
* Returns true if a territory has valid neighbours (for the fortification phase), false otherwise.
* \param territoryID The ID of the central territory
* \param map A pointer to the map
*/
bool BenevolentAI::hasValidNeighbour(int territoryID, Map* map)
{
	vector<string> neighbourTerritories = map->getFriendlyAdjacentTerritoryNames(territoryID);
	int thisID, thisArmy;
	int originalArmy = map->getArmyNumOfTheTerritory(territoryID);

	for (int i = 0; i < neighbourTerritories.size(); i++)
	{
		thisID = map->seekTerritoryID(neighbourTerritories[i]);
		thisArmy = map->getArmyNumOfTheTerritory(thisID);
		if ((thisArmy - originalArmy) > 1)
			return true;
	}

	return false;
}

/**
* The method for the reinforcement phase during the benevolent player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
void BenevolentAI::reinforce(Player* player, Map* map, Deck& deck)
{
	//Reinforce, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = REINFORCEMENT;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->m_StatusInfo.cardsView = true;
	player->m_StatusInfo.contiView = true;
	player->notify();
	player->m_StatusInfo.contiView = false;
	player->m_StatusInfo.cardsView = false;
	player->m_StatusInfo.globalView = false;

	int exchangedArmies = determineExchangedArmies(player, map, deck);

	int valid_assigned_armies = player->assignedAvailableArmies(exchangedArmies);

	cout << player->getName() << "player->m_StatusInfo. (benevolent AI) has " << valid_assigned_armies << "player->m_StatusInfo. troop(s) left to deploy." << endl;

	int assign_terri_ID = getWeakestTerritory(player, map, REINFORCEMENT);
	
	cout << player->getName() << " wants to assign their armies to : ";
	cout << map->getTerritoryName(assign_terri_ID) << endl;

	// Benevolent AI will place all its available armies on its weakest country
	cout << player->getName() << " is going to place " << valid_assigned_armies << " armies on " << map->getTerritoryName(assign_terri_ID) << endl;
	placeArmiesDuringReinforcement(assign_terri_ID, valid_assigned_armies, player, map);

	player->m_StatusInfo.phaseView = false;
	player->m_StatusInfo.currentPhase = REINFORCEMENT;
	player->m_StatusInfo.cardsView = true;
	player->notify();
	player->m_StatusInfo.cardsView = false;
	player->m_StatusInfo.phaseView = true;


	cout << endl;
	//Reinforce, notify  PLAYER STATUS
	player->notify();
	//Reinforce, notify, end phase
	player->m_StatusInfo.statusType = myPhaseEnded;
	player->notify();
}


/**
* This method has no current implementation for the benevolent player.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
bool BenevolentAI::attack(Player* player, Map* map)
{	
	// No implementation since the benevolent player never attacks.
	//Attack, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = ATTACK;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->m_StatusInfo.contiView = true;
	player->notify();
	player->m_StatusInfo.contiView = false;
	player->m_StatusInfo.globalView = false;

	//***************
	//maybe add some logic??
	//***************


	cout << "\n***************************************" << endl;
	cout << player->getName() << " does not wish to attack. " << endl;
	cout << "***************************************\n" << endl;

	//Attack, notify, end phase
	player->m_StatusInfo.statusType = myPhaseEnded;
	player->notify();

	return false;
}


/**
* The method for the fortification phase during the benevolent player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
bool BenevolentAI::fortify(Player* player, Map* map)
{
	//Fortify, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = FORTIFICATION;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->notify();
	player->m_StatusInfo.globalView = false;

	cout << "\n***************************************" << endl;
	cout << player->getName() << " wants to fortify! " << endl;
	cout << "***************************************\n" << endl;

	
	int move_to = getWeakestTerritory(player, map, FORTIFICATION);
	if (move_to < 0)
	{
		cout << "Nothing to move. " << endl;
		
		//Fortify, notify end of phase
		player->m_StatusInfo.statusType = myPhaseEnded;
		player->notify();
		return false;
	}
	int move_from = territoryToMoveArmyFrom(player, map, move_to);
	
	int move_num = 0;

	//Fortify, notify available target territory list & path?
	//player->statusDisplay(myTerritoryFortify);

	int army_from, army_to;

	army_from = map->getArmyNumOfTheTerritory(move_from);
	army_to = map->getArmyNumOfTheTerritory(move_to);
	move_num =  (army_from - army_to) / 2; 

	moveArmiesDuringFortification(move_from, move_to, move_num, player, map);
	cout << endl;
	cout << player->getName() << " Moved " << move_num << " armies from " << map->getTerritoryName(move_from) << " to " << map->getTerritoryName(move_to) << endl;
	
	//Fortify, notify  PLAYER STATUS
	player->m_StatusInfo.statusType = myTerritories;
	player->notify();
	////Fortify, notify, end of phase
	//player->m_StatusInfo.statusType = myPhaseEnded;
	//player->notify();

	return true;
}

/**
* Determines the territory that will give an army to another friendly territory.
* Returns the ID if there is a valid territory, or -1 if no valid territory is found.
* \param player A pointer to the current player
* \param map A pointer to the map
* \param move_to The territory ID of the territory we move armies to
*/
int BenevolentAI::territoryToMoveArmyFrom(Player* player, Map* map, int move_to)
{
	vector<string> neighbourTerritories = map->getFriendlyAdjacentTerritoryNames(move_to);

	if (neighbourTerritories.size() == 0)
		return -1;

	int thisArmy, thisID;
	int relativeStrongestTerritory = map->seekTerritoryID(neighbourTerritories[0]);
	int relativeStrongestArmy = map->getArmyNumOfTheTerritory(relativeStrongestTerritory);

	for (int i = 0; i < neighbourTerritories.size(); i++)
	{
		thisID = map->seekTerritoryID(neighbourTerritories[i]);
		thisArmy = map->getArmyNumOfTheTerritory(thisID);

		if (thisArmy > relativeStrongestArmy && thisID != move_to)
		{
			relativeStrongestArmy = thisArmy;
			relativeStrongestTerritory = thisID;
		}
	}

	if (relativeStrongestArmy < map->getArmyNumOfTheTerritory(move_to))
		return -1;

	return relativeStrongestTerritory;
}

/**
* Calls the methods for the different phases of the benevolent player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
void BenevolentAI::play(Player* player, Map* map, Deck& deck)
{
	reinforce(player, map, deck);
	
	while(attack(player, map));

	while (fortify(player, map));

	cout << "\n***************************************" << endl;
	cout << "End of  " << player->getName() << "'s turn! " << endl;
	cout << "***************************************\n" << endl;
}

void RandomAI::reinforce(Player* player, Map* map, Deck& deck)
{
	//Reinforce, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = REINFORCEMENT;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->m_StatusInfo.cardsView = true;
	player->m_StatusInfo.contiView = true;
	player->notify();
	player->m_StatusInfo.contiView = false;
	player->m_StatusInfo.cardsView = false;
	player->m_StatusInfo.globalView = false;

	int exchangedArmies = determineExchangedArmies(player, map, deck);

	int valid_assigned_armies = player->assignedAvailableArmies(exchangedArmies);

	cout << player->getName() << " (random AI) has " << valid_assigned_armies << " troop(s) left to deploy." << endl;
	cout << player->getName() << " wants to assign their armies to : ";

	int assign_terri_ID = getRandomPlayerTerritory(player, map, DEFAULT);

	cout << map->getTerritoryName(assign_terri_ID) << endl;

	// Aggressive AI will place all its available armies on its strongest country
	cout << player->getName() << " is going to place " << valid_assigned_armies << " armies on " << map->getTerritoryName(assign_terri_ID) << endl;
	placeArmiesDuringReinforcement(assign_terri_ID, valid_assigned_armies, player, map);

	player->m_StatusInfo.phaseView = false;
	player->m_StatusInfo.currentPhase = REINFORCEMENT;
	player->m_StatusInfo.cardsView = true;
	player->notify();
	player->m_StatusInfo.cardsView = false;
	player->m_StatusInfo.phaseView = true;


	cout << endl;
	//Reinforce all terri notify 
	player->m_StatusInfo.statusType = myTerritories;
	player->notify();
	//Reinforce, notify counting -1, end of this phase
	player->m_StatusInfo.statusType = myPhaseEnded;
	player->notify();
}

/**
* Returns a random territory that belongs to the player.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
int RandomAI::getRandomPlayerTerritory(Player* player, Map* map, PlayerPhase phase)
{
	vector<string> playerTerritories = player->getPlayerTerritoryNames();
	int randomTerritory = rand() % playerTerritories.size();
	int randomID = map->seekTerritoryID(playerTerritories[randomTerritory]);
	int randomArmies = map->getArmyNumOfTheTerritory(randomID);

	if (phase == ATTACK)
	{
		if (map->enemyNeighbourExists(randomID) == false || randomArmies == 1)
			return -1;
	}
	else if (phase == FORTIFICATION)
	{
		if (map->friendNeighbourExists(randomID) == false)
			return -1;
	}
	
	return randomID;
}

/**
* Returns a random adjacent enemy territory.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
int RandomAI::getRandomEnemyTerritory(Player* player, Map* map, int attack_from)
{
	vector<string> neighbourTerritories = map->getEnemyAdjacentTerritoryNames(attack_from);
	int randomTerritory = rand() % neighbourTerritories.size();

	return map->seekTerritoryID(neighbourTerritories[randomTerritory]);
}


/**
* The method for the attack phase during the random player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
bool RandomAI::attack(Player* player, Map* map)
{
	//Attack, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = ATTACK;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->m_StatusInfo.contiView = true;
	player->notify();
	player->m_StatusInfo.contiView = false;
	player->m_StatusInfo.globalView = false;

	cout << "\n***************************************" << endl;
	cout << player->getName() << " wants to attack! " << endl;
	cout << "***************************************\n" << endl;


	int attack_from = getRandomPlayerTerritory(player, map, ATTACK);
	if (attack_from == -1) // Not enough armies to attack from that territory
	{
		cout << player->getName() << " stops attacking!" << endl;
		//Attack, notify, end of phase
		player->m_StatusInfo.statusType = myPhaseEnded;
		player->notify();
		return false;
	}

	cout << player->getName() << " is going to attack from: " << map->getTerritoryName(attack_from) << endl;

	///Attack, notify current selected terri
	player->m_StatusInfo.currentSelectedTerriID = attack_from;
	player->m_StatusInfo.statusType = mySpecificTerritory;
	player->notify();

	//Attack, notify enemylist
	player->m_StatusInfo.currentSelectedTerriID = attack_from;
	player->m_StatusInfo.statusType = myEnemyList;
	player->notify();

	int attack_to = getRandomEnemyTerritory(player, map, attack_from);
	if (attack_to == -1) // No territory to attack
	{
		cout << player->getName() << " cannot find adjacent enemies! " << endl;

		//Attack, notify, end of phase
		player->m_StatusInfo.statusType = myPhaseEnded;
		player->notify();
		return false;
	}

	cout << player->getName() << " is going to attack to: " << map->getTerritoryName(attack_to) << endl;

	bool territoryCaptured = false;
	while (!territoryCaptured)
	{
		cout << "--------------------------------" << endl;

		if (map->getArmyNumOfTheTerritory(attack_from) > 1)
		{
			if (map->getArmyNumOfTheTerritory(attack_to) > 0)
			{
				engageInBattle(attack_from, attack_to, player, map);
				//Attack, notify, selected terri -> attack from
				player->m_StatusInfo.currentSelectedTerriID = attack_from;
				player->m_StatusInfo.statusType = mySpecificTerritory;
				player->notify();
				//Attack, notify, selected terri -> attack to
				player->m_StatusInfo.currentSelectedTerriID = attack_to;
				player->notify();

			}
			else
			{
				cout << player->getName() << " won the battle! " << endl;
				int armiesToMove = rand() % map->getArmyNumOfTheTerritory(attack_from);

				for (int i = 0; i < armiesToMove - 1; i++)
				{
					map->removeArmies(player, map->getTerritoryName(attack_from));
					map->assignArmies(player, map->getTerritoryName(attack_to));
				}
				cout << player->getName() << " moved " << armiesToMove << " armies to " << map->getTerritoryName(attack_to) << endl;
				territoryCaptured = true;
				//Attack, notify player status
				player->m_StatusInfo.statusType = myTerritories;
				player->m_StatusInfo.globalView = true;
				player->m_StatusInfo.contiView = true;
				player->notify();
				player->m_StatusInfo.contiView = false;
				player->m_StatusInfo.globalView = false;
			}
		}
		else
		{
			cout << player->getName() << " failed the battle. " << endl;
			//Attack, notify player status
			player->m_StatusInfo.statusType = myTerritories;
			player->m_StatusInfo.globalView = true;
			player->m_StatusInfo.contiView = true;
			player->notify();
			player->m_StatusInfo.contiView = false;
			player->m_StatusInfo.globalView = false;
			break;
		}
	}
	return true;
}

/**
* The method for the fortification phase during the random player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
bool RandomAI::fortify(Player* player, Map* map)
{
	
	//Fortify, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = FORTIFICATION;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->notify();
	player->m_StatusInfo.globalView = false;

	int move_to = getRandomPlayerTerritory(player, map, FORTIFICATION); // Selects random player territory to fortify
	
	int count = player->getNumberOfTerritories();

	while (move_to < 0 && count > 0)
	{
		move_to = getRandomPlayerTerritory(player, map, FORTIFICATION);
		count--;
	}

	if (move_to < 0)
	{
		cout << endl;
		cout << player->getName() << " cannot fortify at the moment. " << move_to << endl;
		//Fortify, notify, end of phase
		player->m_StatusInfo.statusType = myPhaseEnded;
		player->notify();
		return false;
	}
	
	int move_from = territoryToMoveArmyFrom(player, map, move_to);

	count = map->getFriendlyAdjacentTerritoryNames(move_to).size();
	while (map->getArmyNumOfTheTerritory(move_from) < 2 && count > 0)
	{
		move_from = territoryToMoveArmyFrom(player, map, move_to);
		--count;
	}

	int move_num;
	vector<string> fortifyPath;

	if (move_to > -1 && move_from > -1 && map->getArmyNumOfTheTerritory(move_from) > 1)
	{
		if (map->seekPath(player, map->getTerritoryName(move_from), map->getTerritoryName(move_to), fortifyPath))
		{

			cout << "\n***************************************" << endl;
			cout << player->getName() << " wants to fortify! " << endl;
			cout << "***************************************\n" << endl;

			move_num = rand() % map->getArmyNumOfTheTerritory(move_from); // moves a random number of armies (but always leaves at least one)
			if (move_num == 0)
			{
				move_num = 1;
			}

			moveArmiesDuringFortification(move_from, move_to, move_num, player, map);
			cout << endl;
			cout << player->getName() << " Moved " << move_num << " armies from " << map->getTerritoryName(move_from) << " to " << map->getTerritoryName(move_to) << endl;
		}
	}
	else
	{
		cout << endl;
		cout << player->getName() << " does not want to fortify at the moment. " << endl;
		//Fortify, notify, end of phase
		player->m_StatusInfo.statusType = myPhaseEnded;
		player->notify();
		return false;
	}

	//Fortify, notify, end of phase
	player->m_StatusInfo.statusType = myPhaseEnded;
	player->notify();

	return false;
}


/**
* Returns a random adjacent friend territory to move armies from.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
int RandomAI::territoryToMoveArmyFrom(Player* player, Map* map, int move_to)
{
	vector<string> neighbourTerritories = map->getFriendlyAdjacentTerritoryNames(move_to);
	int randomTerritory = rand() % neighbourTerritories.size();

	return map->seekTerritoryID(neighbourTerritories[randomTerritory]);
}

/**
* Calls the methods for the different phases of the random player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
void RandomAI::play(Player* player, Map* map, Deck& deck)
{
	reinforce(player, map, deck);

	while(attack(player, map));

	while(fortify(player, map));

	cout << "\n***************************************" << endl;
	cout << "End of  " << player->getName() << "'s turn! " << endl;
	cout << "***************************************\n" << endl;
}


/**
 * Doubles the number of armies on all territories.
 * \param player A pointer to the current player
 * \param map A pointer to the map 
 * \param deck A pointer to the deck of cards.
 */
void CheaterAI::reinforce(Player* player, Map* map, Deck& deck) {
	
	//Reinforce, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = REINFORCEMENT;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->m_StatusInfo.cardsView = true;
	player->m_StatusInfo.contiView = true;
	player->notify();
	player->m_StatusInfo.contiView = false;
	player->m_StatusInfo.cardsView = false;
	player->m_StatusInfo.globalView = false;

	vector<string> playersTerritories = player->getPlayerTerritoryNames();

	for(int i=0; i<playersTerritories.size(); i++){
		doubleArmies(map, player, playersTerritories[i]);
	}
	//Fortify, notify, end of phase
	player->m_StatusInfo.statusType = myPhaseEnded;
	player->notify();

};

/**
 * Automatically conquers all neighbouring territories.
 * Always returns true.
 * \param player A pointer to the current player
 * \param map A pointer to the map 
 * \param deck A pointer to the deck of cards.
 * \return true because why not?
 */
bool CheaterAI::attack(Player* player, Map* map) {
	//Attack, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = ATTACK;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->m_StatusInfo.contiView = true;
	player->notify();
	player->m_StatusInfo.contiView = false;
	player->m_StatusInfo.globalView = false;

	vector<string> territoriesWithEnemies = getTerritoriesWithEnemies(player, map);
    for (int i = 0; i < territoriesWithEnemies.size(); ++i) {
        //get the enemies.
        vector<string> enemies = map->getEnemyAdjacentTerritoryNames(map->seekTerritoryID(territoriesWithEnemies[i]));
        //if we haven't already stolen that land steal it now!!!
        if(enemies.size()>0) {
            for (int j = 0; j < enemies.size(); ++j) {
                map->setTerritoryOwner(enemies[j], player);

            }
			player->m_StatusInfo.statusType = myTerritories;
			player->m_StatusInfo.globalView = true;
			player->m_StatusInfo.contiView = true;
			player->notify();
			player->m_StatusInfo.contiView = false;
			player->m_StatusInfo.globalView = false;

        }
    }

	//Fortify, notify, end of phase
	player->m_StatusInfo.statusType = myPhaseEnded;
	player->notify();

    return false;
};

/**
 * Doubles number of armies of any territory with neighbouring enemies. Return type is forced because of loops for other AIs.
 * \param player the player.
 * \param map the map.
 * \param deck the deck.
 * \return talways true.
 */

bool CheaterAI::fortify(Player *player, Map *map) {
	//Fortify, notify  PLAYER STATUS
	player->m_StatusInfo.phaseView = true;
	player->m_StatusInfo.currentPhase = FORTIFICATION;
	player->m_StatusInfo.statusType = myTerritories;
	player->m_StatusInfo.globalView = true;
	player->notify();
	player->m_StatusInfo.globalView = false;

	vector<string> territoriesWithEnemies = getTerritoriesWithEnemies(player, map);
    for (int i = 0; i < territoriesWithEnemies.size(); ++i) {
        doubleArmies(map, player, territoriesWithEnemies[i]);
    }
	
	//Fortify, notify, end of phase
	player->m_StatusInfo.statusType = myPhaseEnded;
	player->notify();

	return false;
}

/**
 * Doubles the number of armies in the given territory.
 * \param map the map
 * \param player the player
 * \param territoryName the territory where we want to double the armies.
 */
void CheaterAI::doubleArmies (Map *map, Player *player, string territoryName){
		int territoryID = map->seekTerritoryID(territoryName);
		int newArmySize = (map->getArmyNumOfTheTerritory(territoryID)*2);
		placeArmiesDuringReinforcement(territoryID, newArmySize, player, map);
};

/**
 * Returns all of the player's territories that have neighbouring enemies.
 * @param player the player.
 * @param map the map.
 * @return a vector of strings with the names of player territories that have neighbouring enemies.
 */
vector<string> CheaterAI::getTerritoriesWithEnemies (Player *player, Map *map){
	vector<string> myTerritories = player->getPlayerTerritoryNames();
	vector<string> toReturn = {};
	for(int i=0; i<myTerritories.size(); i++){
		vector<string> enemies = map->getEnemyAdjacentTerritoryNames(map->seekTerritoryID(myTerritories[i]));
		if(enemies.size() > 0){
			toReturn.push_back(myTerritories[i]);
		}
	}
	return toReturn;
}

/**
* Virtual method from Strategy, implementation is not relevant for CheaterAI.
*/
int CheaterAI::territoryToMoveArmyFrom(Player* player, Map* map, int move_to)
{
	return 0;
}


/**
* Calls the methods for the different phases of the cheater player's turn.
* \param player A pointer to the current player
* \param map A pointer to the map
*/
void CheaterAI::play(Player *player, Map *map, Deck &deck) {
    reinforce(player, map, deck);
    while(attack(player, map));
    while(fortify(player, map));

    cout << "\n***************************************" << endl;
    cout << "End of  " << player->getName() << "'s turn! " << endl;
    cout << "***************************************\n" << endl;
}

