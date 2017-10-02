#include <iostream>
#include <stdlib.h>     // srand, rand 
#include <time.h>       // time 
#include "Dice.h"
using namespace std;

int main() {
	int test = 0;

	//dice object that take 2 paramaters 1) number of dice 2) counter for dices
	DiceCup dice1;
	DiceCup dice2;

	//seed to generate random numbers
	srand(time(NULL));
	int userDice1, userDice2;
	cout << "Please enter enter the number of dices for player1 (1-3 max):" << endl;
	cin >> userDice1;
	cout << "Please enter enter the number of dices  for player2 (1-3 max):" << endl;
	cin >> userDice2;
	do {
		//set ctor number of dice 
		dice1.setNumberOfDice(userDice1);
		dice2.setNumberOfDice(userDice2);
		//******************************DICE1*********************************
		cout << "\n********d1 dice rolled...********" << endl;
		cout << "==========================================" << endl;
		
		for (int i = 0; i < dice1.getNumberOfDice(); i++) {
			dice1.storeDiceValue(dice1.rollDice());
			dice1.displayCup();
			dice1.resetContainer();
			cout << "==========================================";
			cout << "\n\tThe percentage of dice1" << endl;
			dice1.showPercentage();
			cout << "==========================================" << endl;
		}
		//******************************DICE2*********************************
		cout << "\n********d2 dice rolled...********" << endl;
		cout << "==========================================" << endl;
		for (int i = 0; i < dice2.getNumberOfDice(); i++) {
			dice2.storeDiceValue(dice2.rollDice());
			dice2.displayCup();
			dice2.resetContainer();
			cout << "==========================================";
			cout << "\n\tThe percentage of dice2" << endl;
			dice2.showPercentage();
			cout << "==========================================" << endl;
		}
		cin >> test;
	} while (test != -1);
	cout << "\n";
	return 0;
}
