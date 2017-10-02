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
	int getDiceCounter();
	void setDiceCounter(int dc);
	int rollDice();

private:
	//instance variables
	int m_Value;
	int m_DiceCounter;
};

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
	/*std::vector<int> rollDice();*/
	void keepTrack(int x);
	void showPercentage();
	void displayCup();
	void resetContainer();
	void storeDiceValue(int x);

private:
	//instances variables
	int m_NumberOfDice;
	int m_TrackPercent[6];
	std::vector<int> m_Container;
};
