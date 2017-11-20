/** 
 * \file 
 * The header for the Player.cpp. Includes declaration for Player. 
 **/
#pragma once
#include <string>
#include <vector>
#include "Map.h"
#include "Dice.h"
#include "Cards.h"
#include "StrategyPattern.h"
#include "Subject.h"
using namespace std;


//forward declarations
class Map;
struct Territory;
struct Continent;
class Strategy;

//enum PlayerPhase {
//	REINFORCEMENT, ATTACK, FORTIFICATION, DEFENSE, DEFAULT
//};
enum PlayerPhase;

enum PlayerStatus{
	myDefault, myTerritories, mySpecificTerritory, myEnemyList, myPathList, myPhaseEnded
};


struct PlayerStatusInfo
{
	bool globalView;
	bool phaseView;
	bool cardsView;
	bool contiView;
	PlayerPhase currentPhase;
	PlayerStatus statusType;
	int currentSelectedTerriID;
	PlayerStatusInfo();
	void statusInfoInitialize();
};

/**
 * The Player class. The main class which represents all players in the game.
 * \param m_DiceCup The player's DiceCup to use the dice.
 * \param m_Hand The player's Hand to store and use Cards.
 * \param m_PlayerTerritories The vector of player territories. 
 * \param m_PlayerContinents The vector of player  continents.
 * \param m_Name The player's name.
 */
class Player : public Subject {

public:
	Player(Map * gameMap);
	Player(string name, Map * gameMap);
	int getPlayerID();
	int getNumberOfTerritories();
	int getHandSize();
	string getName();
	vector<string> getPlayerTerritoryNames();
	
	vector<Territory*> * getPlayerTerritoryList();

	vector<Continent*> * getPlayerContinentList();

	void setPlayerID(int ID);

	
	int exchangeCards(Deck &deck);
	int exchangeCardsAI(Deck &deck);
	int assignedAvailableArmies(int exchangedArmies);

	void drawCard(Deck &Deck);
	void displayHand();
	vector<Card>* getCards();
	bool exchangeableHand();
	vector<int> shakeDiceCup(int numberOfDice);

	void assignTerritory(string territoryName, Map& map);
	string deallocateTerritory();
	void displayPlayerTerritories();
	int numberOfArmiesAssigned();
	bool checkOwnedCountry(string territory, Player p);
	void toString();
	int getPlayerContinentBonus(Map& map);
	//void statusDisplay(playerStatus myStatus);
	void myTerriUpdate(Map* map);
	void myContiUpdate(Map* map);
	bool isMyTerritory(Territory * terri);

	void setStrategy(Strategy* strategy);
	void play(Player* player, Map* map, Deck& deck);

	vector<vector<string>>  myPathListOfTerriID(int terriID);

	int valid_assigned_armies;
	PlayerStatusInfo m_StatusInfo; //m_StatusID[0]: phaseType; m_StatusID[1]: notify counting; m_StatusID[2]: error input id
//	int selectedTerritoryID;
	vector<int> myRolledResult, enemyRolledResult;


private:
	DiceCup m_DiceCup;
	Hand m_Hand;
	vector<Territory*> m_PlayerTerritories;
	vector<Continent*> m_PlayerContinents;
	string m_Name;
	Strategy* m_Strategy;
	int m_PlayerID;
	int conti_ctrl_value;
	Map * m_Map;
};