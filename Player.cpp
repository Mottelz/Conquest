#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"



int numberOfDice;

Player::Player() {
	m_DiceCup = DiceCup();
	m_Hand = Hand();
	m_Name = "Nameless";
	m_PlayerID = 0;
}

Player::Player(std::string name){
	m_Name = name;
	m_DiceCup = DiceCup();
	m_Hand = Hand();
	m_PlayerID = 0;  // To be set at startup
};

int Player::getPlayerID() {
	return m_PlayerID;
}

int Player::getNumberOfTerritories() {
	return m_PlayerTerritories.size();
}

int Player::getMyCard()
{
	return m_Hand.getHandSize();
}

string Player::getName() {
	return m_Name;
}

vector<string> Player::getPlayerTerritoryNames() {
	vector<string> toReturn;
	for (int i = 0; i < m_PlayerTerritories.size(); i++) {
		toReturn.push_back(m_PlayerTerritories[i]->m_TerritoryName);
	}
	return toReturn;
}

void Player::setPlayerID(int ID) {
	m_PlayerID = ID;
}

void Player::reinforce() {
	cout << m_Name << " just got reinforcements!" << endl;
}
void Player::attack() {
	cout << m_Name <<" just attacked!" << endl;
}
void Player::fortify() {
	cout << m_Name << " just fortified their territories!" << endl;
}

void Player::reinforcement(Map * map, Deck &deck)
{
	
	int assign_terri_ID = -1, assign_num = 0;
	this->statusDisplay(myTerri_REIN);

	int my_card;
	int exchangedArmies = 0;

	my_card = this->getMyCard();

	cout << "Currently, you have " << my_card << " cards in your hand. " << endl;
	this->displayHand();
	if (this->reinforcement_cardExchangeable() == true)
	{
		cout << "Your have exchangeable cards. " << endl;
		if (my_card > 5)
		{
			cout << "Since you have more than 5 cards you must exchange. " << endl;
			
			while(exchangedArmies == 0)
				exchangedArmies = this->reinforcement_cardExchange(deck);

		}
		else
		{
			string exchange = NULL;
			do {
				cout << "Do you want to exchange your cards? [Y/N] " << endl;
				cin >> exchange;
				if (exchange == "Y" || exchange == "y")
				{
					exchangedArmies = this->reinforcement_cardExchange(deck);
					if(exchangedArmies!=0)
						break;
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
		
		int valid_assigned_armies = this->reinforcement_availableAssignedArmies(exchangedArmies);

	do {
		cout << "You have " << valid_assigned_armies << " troop(s) left to deploy." << endl;
		//choose territory attack from
		cout << "Please select ID of the territory where you want to assign your armies: " << endl;
		cin >> assign_terri_ID;

		if (assign_terri_ID >= 0)
		{
			if ((map->getOwnerOfTheTerritory(assign_terri_ID)) != this)
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
				this->reinforcement_placeArmies(assign_terri_ID, assign_num, map);
				valid_assigned_armies -= assign_num;
				break;
			}
			else
			{
				cout << "INVALID INPUT " << endl;
			}
		} while (true);
		
		cout << endl;
		this->statusDisplay(myTerri_REIN);

	} while (valid_assigned_armies > 0);
	
	
}

int Player::reinforcement_cardExchange(Deck &deck)
{
	return m_Hand.exchange(deck);
}

int Player::reinforcement_availableAssignedArmies(int exchangedArmies)
{
	int avail_AssignedArmies = this->getNumberOfTerritories()/3;
	if (avail_AssignedArmies < 3)
		avail_AssignedArmies = 3;
	for (int i = 0; i < m_PlayerContinents.size(); i++)
		avail_AssignedArmies += this->m_PlayerContinents[i]->getContiBonus();
	avail_AssignedArmies += exchangedArmies;
	return avail_AssignedArmies;
}

void Player::attack(Map * map)
{
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
		//string input;
		this->statusDisplay(myTerritories);
		do {
			//choose territory attack from
			cout << "Please select the territory ID (integer) that you want to attack from: " << endl;
			cout << "** -1 for ending attack phase" << endl;
			cin >> attack_from;

			if (attack_from == -1)
			{
				cout << "Attack phase is over. " << endl;
				return;
			}else
			if (attack_from >= 0)
			{
				if ((map->getOwnerOfTheTerritory(attack_from)) == this)
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

			
			map->enemyTerriOf(attack_from);
			//choose territory attack to 
			cout << "Please select the adjacent territory ID (integer) that you want to attack to: " << endl;

			cin >> attack_to;
			if (attack_to >= 0)
			{
				if (map->isAdjacent(attack_from, attack_to))
				{
					if ((map->getOwnerOfTheTerritory(attack_to)) != this)
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
					this->attack_attacking(attack_from, attack_to, map);
					if (map->getArmyNumOfTheTerritory(attack_from) > 1 && map->getArmyNumOfTheTerritory(attack_to) > 0)
					{
						bool change_terri;
						do
						{
							cout << "Do you want to continue attack this territory? [Y/N] " << endl;
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
						cout << "You can only assign one army to caputre the territory." << endl;;
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
						map->removeArmies(this, map->getTerritoryName(attack_from));
						map->assignArmies(this, map->getTerritoryName(attack_to));
					}

					cout << "Territory captured. " << endl;
					break;
				}

			}
			else
			{
				cout << "You failed the battle. " << endl;
				break;
			}
		}
		cout << endl;
		this->statusDisplay(myTerritories);
		//recursive loop
		attack(map);
	}
	else
	{
		cout << "Attack phase is over. " << endl;
		//return;
	}
}

void Player::fortification(Map * map)
{
	bool fortify_state;

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
				fortify_state = false;
				break;
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
		this->statusDisplay(myTerri_FORT);
		do
		{
			cout << "Please select the source territory ID (integer) that you want to move your armies from: " << endl;
			cout << "** -1 for ending attack phase" << endl;
			cin >> move_from;
			if (move_from == -1)
			{
				cout << "Fortification phase is over. " << endl;
				return;
			}
			else
				if (move_from >= 0)
				{
					if ((map->getOwnerOfTheTerritory(move_from)) == this)
					{
						if (map->getArmyNumOfTheTerritory(move_from) > 1)
						{
							if (!map->friendNeighbourExists(move_from))
							{
								cout << "INVALID INPUT: you must choose one of your territories having at least one friend neighbour. " << endl;
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


			//choose territory attack to 
			cout << "Please select the target territory ID (integer) that you want to move your armies to: " << endl;

			cin >> move_to;
			if (move_to >= 0)
			{
				fortifyPath.clear();
				if (map->seekPath(this, map->getTerritoryName(move_from), map->getTerritoryName(move_to), fortifyPath))
				{
					do {

						cout << "Please enter the number of armies that you want to fortify (0-"
							<< map->getArmyNumOfTheTerritory(move_from) - 1 << "): " << endl;
						cin >> move_num;
						if (move_num >= 0 && move_num <= map->getArmyNumOfTheTerritory(move_from) - 1)
							break;
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

		this->fortification_moveArmies(move_from, move_to, move_num, map);
		this->fortification(map);
	}
	else
	{
		cout << "Fortification phase is over. " << endl;
		return;
	}

}

//int Player::rollDice(int numToRoll){
//	m_DiceCup.setNumberOfDice(numToRoll);
//	return m_DiceCup.rollDice();
//}

void Player::drawCard(Deck& deck)
{
	m_Hand.addCard(deck);
}


void Player::displayHand()
{
	m_Hand.printHand();
}

vector<int> Player::shakeMyDiceCup(int armiesOfATerri, bool atk/*, int numOfDice*/)
{
	int numOfDice;
	int maxDiceLimit;
	if (atk == true)
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
		return (this->m_DiceCup.shakeDiceCup(numOfDice));
	}
	else
	{
		
		do {

			cout << "Please choose the number of dice that you want to roll (1-" << maxDiceLimit << "):" << endl;
			cin >> numOfDice;
			cout << endl;
			if (numOfDice > 0 && numOfDice <= maxDiceLimit)
			{
				//return (this->m_DiceCup.shakeDiceCup(numOfDice));
				break;
			}
			else
			{
				cout << "INVALID INPUT: invalid dice number. " << endl;
				cout << endl;
			}
		} while (true);
		return (this->m_DiceCup.shakeDiceCup(numOfDice));
	}
}


void Player::assignTerritory(string territoryName, Map& map)
{
	map.setTerritoryOwner(territoryName, this); // Assigns the player directly to the map
	m_PlayerTerritories.push_back(map.getTerriAddress(territoryName)); // Adds the territory to the player's list
}

string Player::deallocateTerritory()
{
	// Delete and return the last element in the vector. For now this is just to facilitate Driver 2.3
	string territory = m_PlayerTerritories[m_PlayerTerritories.size() - 1]->m_TerritoryName;
	m_PlayerTerritories.pop_back();
	return territory;
}

void Player::displayPlayerTerritories()
{
	for (int i = 0; i < m_PlayerTerritories.size(); i++)
	{

		cout << m_PlayerTerritories[i]->m_TerritoryName ;
		cout << ", Armies : " << m_PlayerTerritories[i]->m_Armies << endl;

	}
}

int Player::numberOfArmiesAssigned()
{
	int count=0;
	for (int i = 0; i < m_PlayerTerritories.size(); i++)
	{
		count += m_PlayerTerritories[i]->m_Armies;
	}
	
	return count;
}

void Player::toString(){
	cout << "Here's what " << m_Name << " has:" << endl;

	cout << "Cards: " << endl;
	displayHand();

	cout << "Territories: " << endl;
	displayPlayerTerritories();
}

int Player::getPlayerContinentBonus(Map& map)
{
	int bonus = map.computeTotalBonus(m_PlayerID);
	return bonus;
}
bool Player::checkOwnedCountry(string territory, Player p) {
  for (int i = 0; i < p.getNumberOfTerritories()-1; i++) {

		if (p.m_PlayerTerritories[i]->m_TerritoryName == territory) {
			return true;		
		}
	}
	return false;
}

void Player::statusDisplay(playerStatus myStatus)
{
	switch (myStatus)
	{
	case myTerritories:
	{
		cout << "\nPlayer status: \n";
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "\nPlayer " << this->getPlayerID();
		cout << ": " << this->getName() <<"\n";
		cout << "------------------------------------------------------------------------------" << endl;;
		cout << "Territories Owned: \n";
		for (int i = 0; i < m_PlayerTerritories.size(); i++)
		{
			printf("[%03d] | %18s | Armies: (%2d) | Enemy Adjacent Territories: ", 
				m_PlayerTerritories[i]->getTerriID(), m_PlayerTerritories[i]->getTerriName().c_str(), m_PlayerTerritories[i]->getNumOfArmies());
			for (int j = 0; j < m_PlayerTerritories[i]->m_AdjacentTerritories.size(); j++)
			{
				if (m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getOwnerPointer() != this)
				{
					printf("[%03d]%s(%d), ",
						m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getTerriID(), m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getTerriName().c_str(), m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getNumOfArmies());
				}
			}

			cout << endl;
		}

		
		break;
	}


	case myTerri_REIN:
	{
		cout << "\nPlayer status: \n";
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "\nPlayer " << this->getPlayerID();
		cout << ": " << this->getName() << "\n";
		cout << "------------------------------------------------------------------------------" << endl;;
		cout << "Territories Owned: \n";
		for (int i = 0; i < m_PlayerTerritories.size(); i++)
		{

			printf("[%03d] | %18s | Armies: (%2d) | Enemy Adjacent Territories: ",
				m_PlayerTerritories[i]->getTerriID(), m_PlayerTerritories[i]->getTerriName().c_str(), m_PlayerTerritories[i]->getNumOfArmies());
			for (int j = 0; j < m_PlayerTerritories[i]->m_AdjacentTerritories.size(); j++)
			{
				if (m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getOwnerPointer() != this)
				{
					printf("[%03d]%s(%d), ",
						m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getTerriID(), m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getTerriName().c_str(), m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getNumOfArmies());
				}
			}

			cout << endl;
		}

		if (this->m_PlayerContinents.size() == 0)
			cout << "You do not own any continent. " << endl;
		else
		{
			cout << "You own " << m_PlayerContinents.size() << " continent(s). " << endl;
			for (int i = 0; i < m_PlayerContinents.size(); i++)
			{
				if (i == 0)
					cout << m_PlayerContinents[i]->getContiName();
				else
				{
					cout <<", "<< m_PlayerContinents[i]->getContiName();
				}
			}
		}

		break;
	}

	case myTerri_FORT:
	{
		cout << "\nPlayer status: \n";
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "\nPlayer " << this->getPlayerID();
		cout << ": " << this->getName() << "\n";
		cout << "------------------------------------------------------------------------------" << endl;;
		cout << "Territories Owned: \n";
		for (int i = 0; i < m_PlayerTerritories.size(); i++)
		{
			printf("[%03d] | %18s | Armies: (%2d) | Adjacent Territories: ",
				m_PlayerTerritories[i]->getTerriID(), m_PlayerTerritories[i]->getTerriName().c_str(), m_PlayerTerritories[i]->getNumOfArmies());
			for (int j = 0; j < m_PlayerTerritories[i]->m_AdjacentTerritories.size(); j++)
			{
				if (m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getOwnerPointer() == this)
				{
					printf("[%03d]%s(%d), ",
						m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getTerriID(),
						m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getTerriName().c_str(),
						m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getNumOfArmies());
				}
				else
				{
					
						printf("%s(%d), ",
							m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getTerriName().c_str(), 
							m_PlayerTerritories[i]->m_AdjacentTerritories[j]->getNumOfArmies());
					

				}
			}

			cout << endl;
		}

		break;
	}


	default:
		break;
	}
}

void Player::myTerriUpdate(Map* map)
{
	m_PlayerTerritories.clear();
	for (int i = 0; i < map->getTotalNumberOfTerritories(); i++)
	{
		if (map->getOwnerOfTheTerritory(i) == this)
		{
			m_PlayerTerritories.push_back(map->getTerriAddress(i));
		}
	}
}

void Player::myContiUpdate(Map * map)
{
	m_PlayerContinents.clear();
	for (int i = 0; i < map->getTotalNumberOfContinents(); i++)
	{
		if (map->getOwnerOfTheContinent(i) == this)
		{
			m_PlayerContinents.push_back(map->getContiAddress(i));
		}
	}
}

bool Player::isMyTerritory(Territory * terri)
{
	if (terri->getOwnerPointer() == this)
		return true;
	else
	{
		return false;
	}
}

void Player::reinforcement_placeArmies(int assign_to, int place_num, Map* map)
{
	for (int i = 0; i < place_num; i++)
	{
		map->assignArmies(this, map->getTerritoryName(assign_to));
	}
		
}

bool Player::reinforcement_cardExchangeable()
{
	return m_Hand.exchangeable();
}

void Player::attack_attacking(int from, int to, Map * map)
{
	vector<int> myRolledList, enemyRolledList;

	cout << "The Attaker, Player " << this->getPlayerID() << ": " << this->getName() << " is about to shake the dice cup. " << endl;
	myRolledList = this->shakeMyDiceCup(map->getArmyNumOfTheTerritory(from), true);

	cout << "The Defender, Player " << map->getOwnerOfTheTerritory(to)->getPlayerID() << ": " 
		<< map->getOwnerOfTheTerritory(to)->getName() << " is about to shake the dice cup. " << endl;
	enemyRolledList = map->getOwnerOfTheTerritory(to)->shakeMyDiceCup(map->getArmyNumOfTheTerritory(to), false);

	for (int i = 0; i < myRolledList.size(); i++) {
		if (i == 0)
		{
			cout << "The Attaker, Player " << this->getPlayerID() << ": " << this->getName() << " rolled: " ;
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
			cout << "The Defender, Player " << map->getOwnerOfTheTerritory(to)->getPlayerID() << ": " 
				<< map->getOwnerOfTheTerritory(to)->getName() << " rolled: ";
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
			cout << "Player " << map->getOwnerOfTheTerritory(to)->getPlayerID() << ", "
				<< map->getOwnerOfTheTerritory(to)->getName() << ", lost one army. " << endl;
			map->removeArmies(map->getOwnerOfTheTerritory(to), map->getTerritoryName(to));

		}
		else
		{
			cout << myRolledList[i] << " <= " << enemyRolledList[i] << " --> ";
			cout << "Player " << this->getPlayerID() << ", "
				<< map->getOwnerOfTheTerritory(from)->getName() << ", lost one army. " << endl;
			map->removeArmies(this, map->getTerritoryName(from));


		}
	}

}


void Player::fortification_moveArmies(int move_from, int move_to, int move_num, Map * map)
{
	for (int i = 0; i < move_num; i++)
	{
		map->removeArmies(this,map->getTerritoryName(move_from));
		map->assignArmies(this, map->getTerritoryName(move_to));

	}
}
