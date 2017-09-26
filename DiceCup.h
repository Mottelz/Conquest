#pragma once

class DiceCup {

//declaration of dice
public:
	//ctor declaration
	DiceCup();
	DiceCup( int nd, int d);

	//getters & setters declaration
	int getNumOfDice();
	void setNumOfDice(int nd);

	void setDiceCounter(int d);
	int  setDiceCounter();

	//function delcaration
	int* rollDice();
	void keepTrack(int x);
	void initializeArray();
	void showPercentage();

private:
	//instances variables
	int numOfDice;
	int diceCounter;
	int trackPercent[6];
	int container[];
	
	
};

