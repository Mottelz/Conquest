#pragma once
#include <string>
#include <vector>
#include "Dice.h"
#include "Cards.h"
#include "Map.h"


class Player {

public:
	Player();
	Player(std::string name);
	int getPlayerID();
	int getNumberOfTerritories();
	string getName();
	vector<string> getPlayerTerritoryNames();
	void setPlayerID(int ID);

	void reinforce();
	void attack();
	void fortify();
	int rollDice(int numToRoll);
	void drawCard(Deck &Deck);
	void displayHand();

	void assignTerritory(string territoryName, Map& map);
	string deallocateTerritory();
	void displayPlayerTerritories();
	int numberOfArmiesAssigned();
	int getPlayerContinentBonus(Map& map);

private:
	DiceCup m_DiceCup;
	Hand m_Hand;
	vector<Territory*> m_PlayerTerritories;
	std::string m_Name;
	int m_PlayerID;
};