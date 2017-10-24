#include "Fortification.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Fortification::Fortification(){}

Fortification::~Fortification() {}

// move number of armies based on user input
void Fortification::moveArmy(string sourceCountry, string targetCountry, Map& map, Player& p) {
	
	int m_moveArmy;
	cout << "please input the number of armies you wish to moves" << endl;
	cin >> m_moveArmy;

	//get number of army in source country 
	int m_numSourceArmy = map.getArmyNumOfTheTerritory(map.seekTerritoryID(sourceCountry));
	
	//do-while to check if user entered the correct input
	do {
		//if user ask to move more army than what the country source have
		if (m_moveArmy > m_numSourceArmy - 1) {
			cout << "It is not possible to move more or equal army than the country have, please try again." << endl;
			cin >> m_moveArmy;
		}
		else if (m_moveArmy <= 0) {
			cout << "It is not possible to move a negative or zero army, please try again." << endl;
			cin >> m_moveArmy;
		}
	} while ((m_moveArmy > m_numSourceArmy - 1) || (m_moveArmy <= 0));

	//move army to neighbor, make sure 1 army left in source country
	//remove the army in the map of source country
		for (int i = 0; i < m_moveArmy; i++)
			map.removeArmies(&p, sourceCountry);

	//assign the new armies into map of target country
	for (int i = 0; i < m_moveArmy; i++)
		map.assignArmies(&p, targetCountry);
}