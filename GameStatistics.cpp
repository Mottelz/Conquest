////concrete Observer
//#include <iostream>
//#include <vector>
//#include "GameStatistics.h"
//
//using namespace std;
//
////declare the static vector variable
////vector<Player*> gameStatistics::listPlayers;
//
//gameStatistics::gameStatistics() {
//}
//
//gameStatistics::gameStatistics(vector<Player*> *playerList, Map* map) {
//	//m_PlayerSubject = p;
//	m_MapSubject = map;
//	m_MapSubject->attach(this);
//	m_PlayerList = playerList;
//	for (unsigned int i = 0; i < m_PlayerList->size(); i++)
//	{
//		m_PlayerList->at(i)->attach(this);
//	}
//}
//
//gameStatistics::~gameStatistics() {
//	m_MapSubject->detach(this);
//	for (unsigned int i = 0; i < m_PlayerList->size(); i++)
//	{
//		m_PlayerList->at(i)->detach(this);
//	}
//}
//void gameStatistics::update() {
//	if(globalView == true)
//	display();
//}
//
//void gameStatistics::display() {
//
//	cout << "=================Game Statistics==================" << endl;
//	
//	displayPlayerControl();
//
//	cout << "==================================================" << endl;
//}
//
//void gameStatistics::displayPlayerControl() {
//
//	int m_TotalTerritory = m_MapSubject->getTotalNumberOfTerritories();
//	
//
//	//to properly print out after 2 decimal
//	cout.setf(ios::fixed);
//	cout.setf(ios::showpoint);
//	cout.precision(2);
//	cout << "Total territory in game: " << m_MapSubject->getTotalNumberOfTerritories() << endl;
//	for (int i = 0; i < m_PlayerList->size(); i++) {
//
//		//calculate the percentage of players owned country
//		double percentage = ((double)m_PlayerList->at(i)->getNumberOfTerritories() / m_TotalTerritory) * 100;
//
//		//print the percentage of owned country
//		cout << m_PlayerList->at(i)->getName() << ": (" << percentage << "%) \t";
//		
//		//output percentage in form of stars
//		for (int j = 0; j < m_PlayerList->at(i)->getNumberOfTerritories(); j++) {
//			if (j % 5 == 0)
//				cout << " ";
//			cout << "*";
//		}
//		cout << endl;
//	}
//}