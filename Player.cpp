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

int Player::rollDice(int numToRoll){
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

string Player::deallocateTerritory()
{
	// Delete and return the last element in the vector
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

int Player::getPlayerContinentBonus(Map& map)
{
	int bonus = map.computeTotalBonus(m_PlayerID);
	return bonus;
}