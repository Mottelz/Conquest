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
	myTerritories, myTerritoryReinforce, myTerritoryFortify
};

/**
 * The Player class. The main class which represents all players in the game.
 * \param m_DiceCup The player's DiceCup to use the dice.
 * \param m_Hand The player's Hand to store and use Cards.
 * \param m_PlayerTerritories The vector of player territories. 
 * \param m_PlayerContinents The vector of player  continents.
 * \param m_Name The player's name.
 */
class Player {

public:
	Player();
	Player(string name);
	int getPlayerID();
	int getNumberOfTerritories();
	int getHandSize();
	string getName();
	vector<string> getPlayerTerritoryNames();
	void setPlayerID(int ID);

	
	void reinforce(Map* map, Deck &deck);
	int exchangeCards(Deck &deck);
	int assignedAvailableArmies(int exchangedArmies);
	void attack(Map* map);
	void fortify(Map* map);

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
	string m_Name;
	int m_PlayerID;
	int conti_ctrl_value;
	void placeArmiesDuringReinforcement(int assign_to, int place_num, Map* map);
	void engageInBattle(int from, int to, Map * map);
	void moveArmiesDuringFortification(int move_from, int move_to, int move_num, Map* map);
};