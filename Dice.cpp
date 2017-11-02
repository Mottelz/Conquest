/** 
 * \file 
 * The cpp for the Dice.h. Includes definitions for Die and DiceCup. 
 **/
#include <iostream>
#include "Dice.h"
using namespace std;

/**
 * Default constructor. 
 */
Die::Die() {
	m_Value = 0;
	m_DiceCounter = 0;
}

/**
 * Constructor that allows to set the value. 
 */
Die::Die(int value) {
	m_Value = value;
	m_DiceCounter = 0;
}

/**
 * Returns current value of the die. 
 */
int Die::getValue() {
	return m_Value;
}
/**
 * Returns the number of times the this Die has been rolled. 
 */
int Die::getDiceCounter() {
	return m_DiceCounter;
}

/**
 * Manulally set the value of the Die. 
 * \param value This is the value to set.
 */
void Die::setValue(int value) {
	m_Value = value;
}

/**
 * Set the number of times this die has been rolled.
 * \param dc The number you wish to set m_DiceCounter to.
 */
void Die::setDiceCounter(int dc) {
	m_DiceCounter = dc;
}

/**
 * Randomly set the value of the die and increase counter.
 */
const int Die::rollDice() {
		//generate a random number of 1-6 for dice
		int rollDiceValue = rand() % 6 + 1;

		//no value outside of the 1 - 6 range is ever returned
		while ((rollDiceValue < 1 || rollDiceValue > 6))
			rollDiceValue = rand() % 6 + 1;

		//increment counter for number of dice each time function get called
		m_DiceCounter++;
	
		return (const int)rollDiceValue;
}


/**
 * Default constructor. Sets dice to zero.
 */
DiceCup::DiceCup() {
	m_NumberOfDice = 0;
}

/**
 * Constructor that sets number of dice. 
 * \param numberOfDice Desired number of dice. Must be between 1 and 3 (inclusive).
 */ 
DiceCup::DiceCup(int numberOfDice) {
	if (numberOfDice >= 4 || numberOfDice < 0)
		cout << "error, number of dice can only be 1 to 3" << endl;
	else {
		setNumberOfDice(numberOfDice);
	}
}

/**
 * Returns the number of dice.
 */
int DiceCup::getNumberOfDice() {
	return m_NumberOfDice;
}

/**
 * Sets number of dice. Sets to 3 if number is greater than 3. Sets to 1 if less than 1. 
 * \param numberOfDice The number of dice to set.
 */
void DiceCup::setNumberOfDice(int numberOfDice) {
	if (numberOfDice > 3) {
		cout << "Attempted to add more than 3 dice. Added 3 instead." << endl;
		m_NumberOfDice = 3;
	} else if (numberOfDice < 1) {
		cout << "Attempted to use less than 1 die. Set to 1 instead." << endl;
		m_NumberOfDice = 1;
	}
	else {
		m_NumberOfDice = numberOfDice;
	}
}

/**
 * Stores the given value as a Die value and updates the stats.
 * \see DiceCup.keepTrack
 * \param x The die value.
 */
void DiceCup::storeDiceValue(int x) {
		//call rollDice() to get value of a dice
		int valueOfDice = x;

		//store value into container array
		m_Container.push_back(valueOfDice);

		//call function to keep track of dice rolled
		keepTrack(valueOfDice);
}

/**
 * Sets the number of and rolls the dice in the cup.
 * \param numOfDice The number of Dice we want to use. 
 */
const vector<int> DiceCup::shakeDiceCup(int numOfDice)
{
	
	//clear up first incase of some unexpected cases
	this->m_Container.clear();

	for (int i = 0; i < numOfDice; i++)
	{
		m_Container.push_back(rollDice());
	}
	//sort container descendingly
	descendingSort();

	return  m_Container;
	
}

/**
 * Sorts the die values in descending order. Used because we need to compare values. 
 */
void DiceCup::descendingSort()
{
	int temp = m_Container[0];
	if (m_Container.size() > 1)
	{
		for (int j = 1; j < m_Container.size(); j++)
		{
			for (int i = 0; i < m_Container.size() - j; i++)
			{
				if (m_Container[i] < m_Container[i + 1])
				{
					temp = m_Container[i];
					m_Container[i] = m_Container[i + 1];
					m_Container[i + 1] = temp;
				}
			}
		}
	}
}

/**
 * Updates the number of times a specific number has come up.
 */
void DiceCup::keepTrack(int x) {
	switch (x) {
	case 1:
		m_TrackPercent[0]++;
		break;

	case 2:
		m_TrackPercent[1]++;
		break;

	case 3:
		m_TrackPercent[2]++;
		break;

	case 4:
		m_TrackPercent[3]++;
		break;

	case 5:
		m_TrackPercent[4]++;
		break;

	case 6:
		m_TrackPercent[5]++;
		break;
	}
}

/**
 * Prints out the percentages that each number has been rolled.
 */
void DiceCup::showPercentage() {
	for (int i = 0; i < 6; i++) {
		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);
		cout.precision(2);

		double percentNum = (double)m_TrackPercent[i] / getDiceCounter() * 100;

		cout << "the percentage of " << i + 1 << " (#" << m_TrackPercent[i] << ")" <<
			" is: " << percentNum << "%" << endl;
	}
}

/**
 * Removes everything from the container. 
 */
void DiceCup::resetContainer() {
	for (unsigned int i = 0; i < m_Container.size(); i++) {
		m_Container.clear();
	}
}

/**
 * Prints out the value of every die. 
 */
void DiceCup::displayCup() {
	cout << "Player rolled Number: " << m_Container[0];
	
	if (m_Container.size() >= 2)
	{
		for (unsigned int i = 1; i < m_Container.size(); i++)
			cout << " | " << m_Container[0];
	}
	cout << endl;
}
