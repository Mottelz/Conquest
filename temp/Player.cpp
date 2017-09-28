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
	m_Name = "Nameless";
}

Player::Player(std::string name){
	m_Name = name;
	m_DiceCup = DiceCup();
	m_Hand = Hand();
};

void Player::reinforce() {
	cout << m_Name << " just got reinforcements!" << endl;
}
void Player::attack() {
	cout << m_Name <<" just attacked!" << endl;
}
void Player::fortify() {
	cout << m_Name << " just fortified their territories!" << endl;
}

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


void Player::assignTerritory(string territoryName, Map& map)
{
	m_PlayerTerritories.push_back(map.getTerriAddress(territoryName));
}

void Player::displayPlayerTerritories()
{
	cout << "Player " << this->m_Name << endl;
	cout << "My territories: " << endl;
	for (int i = 0; i < m_PlayerTerritories.size(); i++)
	{

		cout << m_PlayerTerritories[i]->m_TerritoryName ;
		cout << ", Armies " << m_PlayerTerritories[i]->m_Armies << endl;

	}
}