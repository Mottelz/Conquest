#include <iostream>
#include "Dice.h"
using namespace std;

//default ctor
Die::Die() {
	m_Value = 0;
}

//one parameter ctor
Die::Die(int value) {
	m_Value = value;
}

//getters
int Die::getValue(){
	return m_Value;
}

//setters
void Die::setValue(int value) {
	m_Value = value;
}

//members function definition

	//default constructor
	DiceCup::DiceCup(){
		m_NumberOfDice = 0;
		m_DiceCounter = 0;
	}

	//two parameter constructor
	DiceCup::DiceCup(int numberOfDice, int diceCounter) {	
		if (numberOfDice >= 4 || numberOfDice < 0)
		cout << "error, number of dice can only be 1 to 3" << endl;
		else{
			setNumberOfDice(numberOfDice);
			//container[nd];
			m_DiceCounter = diceCounter;
		}
	}
	//getters
	int DiceCup::getNumberOfDice() {
		return m_NumberOfDice;
	}

	int DiceCup::setDiceCounter() {
		return m_DiceCounter;
	}

	//setters
	void DiceCup::setNumberOfDice(int numberOfDice) {
		if(numberOfDice > 3){
			cout << "Attempted to add more than 3 dice. Added 3 instead." << endl;
			m_NumberOfDice = 3;
		} else {
			m_NumberOfDice = numberOfDice;
		}
	}

	void DiceCup::setDiceCounter(int diceCounter) {
		m_DiceCounter = diceCounter;
	}

	//rollDice function to generate a random number for dice
	vector<int> DiceCup::rollDice() {

		for (int i = 0; i < getNumberOfDice(); i++) {

			//generate a random number of 1-6 for dice
			int rollDiceValue = rand() % 6 + 1;
			
			//no value outside of the 1 - 6 range is ever returned
			while ((rollDiceValue < 1 || rollDiceValue > 6))
				rollDiceValue = rand() % 6 + 1;

			//create object and store random dice roll
			Die d(rollDiceValue);

			//store value into container array
			m_Container.push_back(d.getValue());
			cout <<"Die #" <<(i+1) <<" - Player rolled Number: " << m_Container[i] << endl;

			//increment counter for dice each time we roll
			m_DiceCounter++;

			//call function to keep track of dice rolled
			keepTrack(rollDiceValue);
		}
		return m_Container;
	}

	// keep track of how many time player rolled a dice - declare
	void DiceCup::keepTrack(int x){		
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

			double percentNum = (double)m_TrackPercent[i] / m_DiceCounter * 100;

			cout << "the percentage of " << i+1 <<" (#" << m_TrackPercent[i] << ")"<<
				 " is: " << percentNum << "%"<<endl;
		}
	}

	void DiceCup::initializeArray() {
		
		//initialize array of trackPercent with 1's
		for (int i = 0; i < 6; i++) {
			m_TrackPercent[i] = 0;
		}
	}