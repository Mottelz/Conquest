/** 
 * \file 
 * The cpp for the Player.h. Includes definitions for Player. 
 **/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Player.h"
using namespace std;

/**
* Constructor that creates the PlayerStatusInfo with the basics.
*/
PlayerStatusInfo::PlayerStatusInfo()
{
	this->currentPhase = DEFAULT;
	this->statusType = myDefault;
	this->globalView = false;
	this->phaseView = false;
	cardsView = false;
	contiView = false;
	this->currentSelectedTerriID = -1;
}

/**
* Initialize the PlayerStatusInfo.
*/
void PlayerStatusInfo::statusInfoInitialize()
{
	this->currentPhase = DEFAULT;
	this->statusType = myDefault;
	globalView = false;
	this->phaseView = false;
	cardsView = false;
	contiView = false;
	this->currentSelectedTerriID = -1;
}


/**
 * Constructor that creates the player with the basics. Names the Player Nameless.
 */
Player::Player(Map * gameMap) {
	m_DiceCup = DiceCup();
	m_Hand = Hand();
	m_Name = "Nameless";
	m_PlayerID = 0;
	m_StatusInfo = PlayerStatusInfo();
	m_Map = gameMap;
}

/**
 * Constructor that creates the player with the basics and the name it's given.
 * \param name The name of the player.
 * \param @ Map the gameMap.
 */
Player::Player(string name, Map * gameMap){
	m_Name = name;
	m_DiceCup = DiceCup();
	m_Hand = Hand();
	m_PlayerID = 0;  // To be set at startup
	m_StatusInfo = PlayerStatusInfo();
	m_Map = gameMap;
};

/**
* Method to set the player's strategy
* \param strategy the Strategy type
*/
void Player::setStrategy(Strategy* strategy)
{
	m_Strategy = strategy;
}

/**
* Method that runs the 3 phases of a player's turn by calling the play() method from Strategy..
* \param player A pointer to the player.
* \param map A pointer to the map.
*/
void Player::play(Player* player, Map* map, Deck& deck)
{
	m_Strategy->play(player, map, deck);
}

/**
* Method that runs the a vector of vector of string
* \type vector<vector<string>>
* \param int terriID
*/
vector<vector<string> >  Player::myPathListOfTerriID(int terriID)
{
	vector<vector<string> > myPathList ;
	for (int i = 0; i < this->getNumberOfTerritories(); i++)
	{
		if (this->m_PlayerTerritories[i]->getTerriID() != terriID)
		{
			vector<string> path;
			if(m_Map->seekPath(this, m_Map->getTerritoryName(terriID), this->m_PlayerTerritories[i]->getTerriName(), path))
				myPathList.push_back(path);
		}
	}
	return myPathList;
}

/**
 * Returns the player's id.
 */
int Player::getPlayerID() {
	return m_PlayerID;
}

/**
 * Returns the number of territories.
 */
int Player::getNumberOfTerritories() {
	return m_PlayerTerritories.size();
}

/**
 * Returns the number of cards in Hand.
 */
int Player::getHandSize()
{
	return m_Hand.getHandSize();
}

/**
 * Returns the player's name.
 */
string Player::getName() {
	return m_Name;
}

/**
 * Returns a string of all the territory names. 
 */
vector<string> Player::getPlayerTerritoryNames() {
	vector<string> toReturn;
	for (int i = 0; i < m_PlayerTerritories.size(); i++) {
		toReturn.push_back(m_PlayerTerritories[i]->m_TerritoryName);
	}
	return toReturn;
}

/**
* Returns a pointer of current player's territory list
*/
vector<Territory*>* Player::getPlayerTerritoryList()
{
	return &m_PlayerTerritories;
}

/**
* Returns a pointer of current player's continent list
*/
vector<Continent*>* Player::getPlayerContinentList()
{
	return &m_PlayerContinents;
}


/**
 * Sets the player's ID. 
 * \param ID The id you want to set.
 */
void Player::setPlayerID(int ID) {
	m_PlayerID = ID;
}


/**
 * Exchanges the cards in the hand with the Deck.
 * \see Hand.exchange
 * \param deck The Deck that is being used in the game.
 */
int Player::exchangeCards(Deck &deck)
{
	return this->m_Hand.exchange(deck);
}

/**
* Exchanges the cards in the hand with the Deck (method for AI).
* \see Hand.exchange
* \param deck The Deck that is being used in the game.
*/
int Player::exchangeCardsAI(Deck &deck)
{
	return this->m_Hand.exchangeAI(deck);
}


/**
* Verify whether the Hand contains exchangeable cards.
* \see Hand.exchangeable
*/
bool Player::exchangeableHand()
{
	return m_Hand.exchangeable();
}


/**
 * Calulates the armies to deploy beyond the number given. The number given is calulated by exchanging cards.
 * \param exchangedArmies Number of armies already set to be deployed.
 */
int Player::assignedAvailableArmies(int exchangedArmies)
{
	int avail_AssignedArmies = this->getNumberOfTerritories()/3;
	if (avail_AssignedArmies < 3)
		avail_AssignedArmies = 3;
	for (int i = 0; i < m_PlayerContinents.size(); i++)
		avail_AssignedArmies += this->m_PlayerContinents[i]->getContiBonus();
	avail_AssignedArmies += exchangedArmies;
	return avail_AssignedArmies;
}

/**
 * Adds a card from the given Deck to player's Hand.
 * \param deck The Deck to draw a card from.
 */
void Player::drawCard(Deck& deck)
{
	m_Hand.addCard(deck);
}

/**
 * Prints out m_Hand 
 * \see Hand.toString
 */
void Player::displayHand()
{
	cout << m_Hand.toString();
}

/**
* Return pointer of cards from m_Hand
* \see Hand.getCards
*/
vector<Card>* Player::getCards()
{
	return m_Hand.getCards();
}

/**
 * Determines number of Dice allowed and rolls them.
 * \param armiesOfATerri The number of armies the player has in the relvant territory.
 * \param atk True if player is attacking, false otherwise.
 */

vector<int> Player::shakeDiceCup(int numberOfDice)
{
	return m_DiceCup.shakeDiceCup(numberOfDice);
}


/**
 * Assigns a given territory on the given map to player.
 * \param territoryName The name of the territory the player is being given.
 * \param map The map we are using in this game.
 */
void Player::assignTerritory(string territoryName, Map& map)
{
	map.setTerritoryOwner(territoryName, this); // Assigns the player directly to the map
	m_PlayerTerritories.push_back(map.getTerriAddress(territoryName)); // Adds the territory to the player's list
}

/**
 * Talkes a territory away from the player. 
 */
void Player::deallocateTerritory(string territory, Map* map)
{
	for (int i = 0; i < m_PlayerTerritories.size(); i++)
	{
		if (m_PlayerTerritories[i]->m_TerritoryName == territory)
		{
			swap(m_PlayerTerritories[i], m_PlayerTerritories[m_PlayerTerritories.size() - 1]);
			m_PlayerTerritories.pop_back();
			return;
		}
	}
}

/**
 * Prints out all the player's territories.
 */
void Player::displayPlayerTerritories()
{
	for (int i = 0; i < m_PlayerTerritories.size(); i++)
	{

		cout << m_PlayerTerritories[i]->m_TerritoryName ;
		cout << ", Armies : " << m_PlayerTerritories[i]->m_Armies << endl;

	}
}

/**
 * Returns the tota number of assigned armies.
 */
int Player::numberOfArmiesAssigned()
{
	int count=0;
	for (int i = 0; i < m_PlayerTerritories.size(); i++)
	{
		count += m_PlayerTerritories[i]->m_Armies;
	}
	
	return count;
}

/**
 * Prints out all the player's stats.
 */
void Player::toString(){
	cout << "Here's what " << m_Name << " has:" << endl;

	cout << "Cards: " << endl;
	displayHand();

	cout << "Territories: " << endl;
	displayPlayerTerritories();
}

/**
 * Calculates army bonus that the player gets for owning a continent.
 * \param map The game's map. 
 */
int Player::getPlayerContinentBonus(Map& map)
{
	int bonus = map.computeTotalBonus(m_PlayerID);
	return bonus;
}

/**
 * Checks if the player owns the the given territory. 
 * \param territory The name of the territory. 
 * \param p The play whose ownership we're checking.
 */
bool Player::checkOwnedCountry(string territory, Player p) {
  for (int i = 0; i < p.getNumberOfTerritories()-1; i++) {

		if (p.m_PlayerTerritories[i]->m_TerritoryName == territory) {
			return true;		
		}
	}
	return false;
}

/**
 * Updates m_PlayerTerritories.
 * \param map The game's map.
 */
void Player::myTerriUpdate(Map* map)
{
	m_PlayerTerritories.clear();
	for (int i = 0; i < map->getTotalNumberOfTerritories(); i++)
	{
		if (map->getOwnerOfTheTerritory(i) == this)
		{
			m_PlayerTerritories.push_back(map->getTerriAddress(i));
		}
	}
}

/**
 * Updates m_PlayerContinents.
 * \param map The game's map.
 */
void Player::myContiUpdate(Map * map)
{
	m_PlayerContinents.clear();
	for (int i = 0; i < map->getTotalNumberOfContinents(); i++)
	{
		if (map->getOwnerOfTheContinent(i) == this)
		{
			m_PlayerContinents.push_back(map->getContiAddress(i));
		}
	}
	//this->m_StatusInfo.phaseView = false;
	//this->m_StatusInfo.currentPhase = REINFORCEMENT;
	this->m_StatusInfo.contiView = true;
	this->notify();
	this->m_StatusInfo.cardsView = false;
	//this->m_StatusInfo.phaseView = true;

}
/**
 * Checks if the player owns a territory.
 * \param territoryToCheck The territory we are checking the owner of. 
 */
bool Player::isMyTerritory(Territory * territoryToCheck)
{
	if (territoryToCheck->getOwnerPointer() == this)
		return true;
	else
	{
		return false;
	}
}

