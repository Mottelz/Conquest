#pragma once
#include<vector>

class Die {

public:
	//ctor declaration
	Die();
	Die(int value);

	//function delcaration
	int getValue();
	void setValue(int value);

private:
	//instance variables
	int m_Value;
};

class DiceCup {

//declaration of dice
public:
	//ctor declaration
	DiceCup();
	DiceCup(int numberOfDice, int diceCounter);

	//getters & setters declaration
	int getNumberOfDice();
	void setNumberOfDice(int numberOfDice);

	void setDiceCounter(int diceCounter);
	int  setDiceCounter();

	//function delcaration
	std::vector<int> rollDice();
	void keepTrack(int x);
	void initializeArray();
	void showPercentage();

private:
	//instances variables
	int m_NumberOfDice;
	int m_DiceCounter;
	int m_TrackPercent[6];
	std::vector<int> m_Container;
	
	
};

