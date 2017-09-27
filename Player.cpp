#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"


using namespace std;

int numberOfDice;

Player::Player() {
	m_DiceCup = DiceCup();
	m_Hand = Hand();
}

void Player::reinforce() {}
void Player::attack() {}
void Player::fortify() {}

std::vector<int> Player::rollDice(int numToRoll){
	m_DiceCup.setNumberOfDice(numToRoll);
	return m_DiceCup.rollDice();
}

void Player::drawCard(Deck& deck)
{
	m_Hand.addCard(deck);
}

void Player::displayHand()
{
	m_Hand.printHand();
}

//void Player::assignTerritories(int number, Map& map) 
//{
//	srand((int)time(0));
//	int random;
//	int totalNumberOfTerritories = map.getTotalNumberOfTerritories();
//	for (int i = 0; i < number; i++)
//	{
//		random = (rand() % totalNumberOfTerritories);
//		
//	}
//
//}