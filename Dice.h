/** 
 * \file 
 * The header for the Dice.cpp. Includes declaration for Die and DiceCup. 
 **/
#pragma once
#include<vector>
using namespace std;
/**
 * The class that represents a die.
 * \param m_Value The value on the die. 
 * \param m_DiceCounter Counts the number of times the dice has been rolled. 
 */
class Die {
public:
	//ctor declaration
	Die();
	Die(int value);

	//function delcaration
	int getValue();
	void setValue(int value);
	int getDiceCounter();
	void setDiceCounter(int dc);
	const int rollDice();

private:
	//instance variables
	int m_Value;
	int m_DiceCounter;
};

/**
 * A class to hold the dice. 
 * \param m_NumberOfDice The number of dice in the cup.
 * \param m_TrackPercent The number of times a number has been returned.
 * \param m_Container Stores all the numbers that have been rolled.
 */
class DiceCup : public Die {

	//declaration of dice
public:
	//ctor declaration
	DiceCup();
	DiceCup(int numberOfDice);

	//getters & setters declaration
	int getNumberOfDice();
	void setNumberOfDice(int numberOfDice);

	//function delcaration
	void keepTrack(int x);//**
	void showPercentage();
	void displayCup();
	void resetContainer();
	void storeDiceValue(int x);//**

	const vector<int> shakeDiceCup(int numOfDice);
	

private:
	//instances variables
	int m_NumberOfDice;
	int m_TrackPercent[6];
	vector<int> m_Container;

	void descendingSort();
};
