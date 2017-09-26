#include <iostream>
#include "Dice.h"
using namespace std;

//default ctor
Die::Die() {
	value = 0;
}

//one parameter ctor
Die::Die(int v) {
	value = v;
}

//getters
int Die::getValue(){
	return value;
}

//setters
void Die::setValue(int v) {
	value = v;
}

//members function definition

	//default constructor
	DiceCup::DiceCup(){
		numOfDice = 0;
		//container[0];
		diceCounter = 0;
	}

	//one parameter constructor
	DiceCup::DiceCup(int nd, int d) {	
		if (nd >= 4 || nd < 0)
		cout << "error, number of dice can only be 1 to 3" << endl;
		else{
			setNumOfDice(nd);
			//container[nd];
			diceCounter = d;
		}
	}
	//getters
	int DiceCup::getNumOfDice() {
		return numOfDice;
	}

	int DiceCup::setDiceCounter() {
		return diceCounter;
	}

	//setters
	void DiceCup::setNumOfDice(int nd) {
		numOfDice = nd;
	}

	void DiceCup::setDiceCounter(int d) {
		diceCounter = d;
	}

	//rollDice function to generate a random number for dice
	vector<int> DiceCup::rollDice() {

		for (int i = 0; i < getNumOfDice(); i++) {

			//generate a random number of 1-6 for dice
			int rollDiceValue = rand() % 6 + 1;
			
			//no value outside of the 1 - 6 range is ever returned
			while ((rollDiceValue < 1 || rollDiceValue > 6))
				rollDiceValue = rand() % 6 + 1;

			//create object and store random dice roll
			Die d(rollDiceValue);

			//store value into container array
			container[i] = d.getValue();
			cout <<"#" <<(i+1) <<" player rolled Number: " << container[i] << endl;

			//increment counter for dice each time we roll
			diceCounter++;

			//call function to keep track of dice rolled
			keepTrack(rollDiceValue);
		}
		return container;
	}

	// keep track of how many time player rolled a dice - declare
	void DiceCup::keepTrack(int x){		
		switch (x) {		
		case 1:
			trackPercent[0]++;
			break;
		
		case 2:
			trackPercent[1]++;
			break;

		case 3:
			trackPercent[2]++;
			break;

		case 4:
			trackPercent[3]++;
			break;

		case 5:
			trackPercent[4]++;
			break;

		case 6:
			trackPercent[5]++;
			break;
		}
	}

	//display the percentage of dice rolled
	void DiceCup::showPercentage() {

		for (int i = 0; i < 6; i++) {
			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			cout.precision(2);

			double percentNum = (double)trackPercent[i] / diceCounter * 100;

			cout << "the percentage of " << i+1 <<" (#" << trackPercent[i] << ")"<<
				 " is: " << percentNum << "%"<<endl;
		}
	}

	void DiceCup::initializeArray() {
		
		//initialize array of trackPercent with 1's
		for (int i = 0; i < 6; i++) {
			trackPercent[i] = 0;
		}
	}