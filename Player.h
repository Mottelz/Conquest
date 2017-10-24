#pragma once
#include <string>
#include <vector>
#include "Map.h"
#include "Dice.h"
#include "Cards.h"

using namespace std;

//forward declaration
class Map;
struct Territory;
struct Continent;
enum playerStatus{
	myTerritories, myTerri_REIN, myTerri_FORT
};

class Player {

public:
	Player();
	Player(std::string name);
	int getPlayerID();
	int getNumberOfTerritories();
	int getMyCard();
	string getName();
	vector<string> getPlayerTerritoryNames();
	void setPlayerID(int ID);

	void reinforce();
	void attack();
	void fortify();
	void reinforcement(Map* map, Deck &deck);
	int reinforcement_cardExchange(Deck &deck);
	int reinforcement_availableAssignedArmies(int exchangedArmies);
	void attack(Map* map);
	void fortification(Map* map);

	//int rollDice(int numToRoll);
	void drawCard(Deck &Deck);
	
	void displayHand();
	vector<int> shakeMyDiceCup(int armiesOfATerri, bool atk/*, int numOfDice = 0*/);

	void assignTerritory(string territoryName, Map& map);
	string deallocateTerritory();
	void displayPlayerTerritories();
	int numberOfArmiesAssigned();
	bool checkOwnedCountry(string territory, Player p);
	void toString();
	int getPlayerContinentBonus(Map& map);
	void statusDisplay(playerStatus myStatus);
	void myTerriUpdate(Map* map);
	void myContiUpdate(Map* map);
	bool isMyTerritory(Territory * terri);

private:
	DiceCup m_DiceCup;
	Hand m_Hand;
	vector<Territory*> m_PlayerTerritories;
	vector<Continent*> m_PlayerContinents;
	std::string m_Name;
	int m_PlayerID;
	int conti_ctrl_value;
	void reinforcement_placeArmies(int assign_to, int place_num, Map* map);
	bool reinforcement_cardExchangeable();
	void attack_attacking(int from, int to, Map * map);
	void fortification_moveArmies(int move_from, int move_to, int move_num, Map* map);
};