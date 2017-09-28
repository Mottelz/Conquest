#pragma once
#include <string>
#include <vector>
#include "Dice.h"
#include "Cards.h"
#include "Map.h"
#include "MapLoader.h"


class Player {

public:
	Player();
	Player(std::string name);

	void reinforce();
	void attack();
	void fortify();
	std::vector<int> rollDice(int numToRoll);
	void drawCard(Deck &Deck);
	void displayHand();

	void Player::assignTerritory(string territoryName, Map& map);
	void Player::displayPlayerTerritories();

private:
	DiceCup m_DiceCup;
	Hand m_Hand;
	vector<Territory*> m_PlayerTerritories;
	std::string m_Name;
};