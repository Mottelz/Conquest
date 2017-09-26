#pragma once
#include <string>
#include "Dice.h"
#include "Cards.h"


class Player {

public:
	Player();

	void reinforce();
	void attack();
	void fortify();
	std::vector<int> RollDice(int numToRoll);
	void DrawCard(Deck &Deck);
	void DisplayHand();

private:
	DiceCup m_DiceCup;
	Hand m_Hand;
};