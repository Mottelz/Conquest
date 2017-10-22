#include <iostream>
#include "Dice.h"
using namespace std;

//default ctor
Die::Die() {
	m_Value = 0;
	m_DiceCounter = 0;
}

//one parameter ctor
Die::Die(int value) {
	m_Value = value;
	m_DiceCounter = 0;
}

//getters
int Die::getValue() {
	return m_Value;
}
int Die::getDiceCounter() {
	return m_DiceCounter;
}

//setters
void Die::setValue(int value) {
	m_Value = value;
}

void Die::setDiceCounter(int dc) {
	m_DiceCounter = dc;
}

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
//members function definition

//default constructor
DiceCup::DiceCup() {
	m_NumberOfDice = 0;
}

//two parameter constructor
DiceCup::DiceCup(int numberOfDice) {
	if (numberOfDice >= 4 || numberOfDice < 0)
		cout << "error, number of dice can only be 1 to 3" << endl;
	else {
		setNumberOfDice(numberOfDice);
	}
}
//getters
int DiceCup::getNumberOfDice() {
	return m_NumberOfDice;
}

//setters
void DiceCup::setNumberOfDice(int numberOfDice) {
	if (numberOfDice > 3) {
		cout << "Attempted to add more than 3 dice. Added 3 instead." << endl;
		m_NumberOfDice = 3;
	}
	else {
		m_NumberOfDice = numberOfDice;
	}
}

void DiceCup::storeDiceValue(int x) {
		//call rollDice() to get value of a dice
		int valueOfDice = x;

		//store value into container array
				m_Container.push_back(valueOfDice);

		//call function to keep track of dice rolled
				keepTrack(valueOfDice);
}

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

	//displayCup();

	return  m_Container;
	
}

//sort container descendingly
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

// keep track of how many time player rolled a dice - declare
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

//display the percentage of dice rolled
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

void DiceCup::resetContainer() {
	for (unsigned int i = 0; i < m_Container.size(); i++) {
		m_Container.clear();
	}
}

void DiceCup::displayCup() {
	cout << "Player rolled Number: " << m_Container[0];
	
	if (m_Container.size() >= 2)
	{
		for (unsigned int i = 1; i < m_Container.size(); i++)
			cout << " | " << m_Container[0];
	}
	cout << endl;
}
