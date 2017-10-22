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
	void REINFORCEMENT(Map* map, Deck &deck);
	int REIN_CARD_EXCHANGE(Deck &deck);
	int REIN_AVAILBLE_ASSIGNED_ARMIES(int exchangedArmies);
	void ATTACK(Map* map);
	void FORTIFICATION(Map* map);

	//int rollDice(int numToRoll);
	void drawCard(Deck &Deck);
	
	void displayHand();
	vector<int> shakeMyDiceCup(int armiesOfATerri, bool atk/*, int numOfDice = 0*/);

	void assignTerritory(string territoryName, Map& map);
	string deallocateTerritory();
	void displayPlayerTerritories();
	int numberOfArmiesAssigned();
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
	void REIN_PLACE_ARMIES(int assign_to, int place_num, Map* map);
	bool REIN_CARD_EXCHANGEABLE();
	void ATK_ATTACKING(int from, int to, Map * map);
	void FORT_MOVE_ARMIES(int move_from, int move_to, int move_num, Map* map);
};