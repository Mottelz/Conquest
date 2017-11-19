#include "GameObserver.h"

PhaseObserver::PhaseObserver()
{
}

/**
* Constructor of PhaseObserver
* \param myStatus The player's PlayerPhase.
* \param myStatus The player's PlayerStatus.
*/
PhaseObserver::PhaseObserver(Player* m_PS, Map* map)
{
	m_PlayerSubject = m_PS;
	m_Map = map;
	m_PlayerSubject->attach(this);
}


PhaseObserver::~PhaseObserver()
{
	m_PlayerSubject->detach(this);
}


void PhaseObserver::update()
{
	if (m_PlayerSubject->m_StatusInfo.phaseView == true)
	{
		display(m_PlayerSubject->m_StatusInfo.currentPhase, m_PlayerSubject->m_StatusInfo.statusType);
	}
}

/**
* Print out a certain type of player status based on the PlayerPhase &  PlayerStatus enum.
* \param myStatus The player's PlayerPhase.
* \param myStatus The player's PlayerStatus.
*/
void PhaseObserver::display(PlayerPhase myPhase, PlayerStatus myStatus)
{

	switch (myPhase)
	{
	case DEFAULT:
	{
		switch (myStatus)
		{
		case myDefault:
		{
			cout << "\nPlayer status: \n";
			cout << "------------------------------------------------------------------------------";
			cout << "\nPlayer " << m_PlayerSubject->getPlayerID();
			cout << ": " << m_PlayerSubject->getName() << "\n";
			cout << "------------------------------------------------------------------------------";
			cout << "\nTerritories Owned: \n";
			vector<Territory*> * tempTerritoryList = m_PlayerSubject->getPlayerTerritoryList();
			for (unsigned int i = 0; i < m_PlayerSubject->getNumberOfTerritories(); i++)
			{
				printf("[%03d] | %18s | Armies: (%2d) | Adjacent Territories: ",
					tempTerritoryList->at(i)->getTerriID(), tempTerritoryList->at(i)->getTerriName().c_str(), tempTerritoryList->at(i)->getNumOfArmies());

				for (unsigned int j = 0; j < tempTerritoryList->at(i)->m_AdjacentTerritories.size(); j++)
				{
					if (j == 0)
					{
						if (tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getOwnerPointer() == m_PlayerSubject)
						{
							printf("[Mine]%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
						}
						else
						{

							printf("[Enemy]%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
						}

					}
					else
					{
						if (tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getOwnerPointer() == m_PlayerSubject)
						{
							printf(", [Mine]%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
						}
						else
						{

							printf(", [Enemy]%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());


						}
					}
				}
				cout << endl;
			}
			break;
		}
		}


		break;
	}


	case REINFORCEMENT:
	{
		switch (myStatus)
		{
		
		case myDefault:
		{
			cout << "<Reinforcement> +" << m_PlayerSubject->getName() << "+ <Reinforcement>" << endl;

			break;
		}
			
			
			//displayer all territories of this player for REINFORCEMENT
		case myTerritories:
		{

			cout << "\nPlayer status: Reinforcement Phase\n";
			cout << "------------------------------------------------------------------------------";
			cout << "\nPlayer " << m_PlayerSubject->getPlayerID();
			cout << ": " << m_PlayerSubject->getName() << "\n";
			cout << "------------------------------------------------------------------------------";
			cout << "\nTerritories Owned: \n";
			vector<Territory*> * tempTerritoryList = m_PlayerSubject->getPlayerTerritoryList();
			for (unsigned int i = 0; i < m_PlayerSubject->getNumberOfTerritories(); i++)
			{

				printf("[%03d] | %18s | Armies: (%2d) | Adjacent Territories: ",
					tempTerritoryList->at(i)->getTerriID(), tempTerritoryList->at(i)->getTerriName().c_str(), tempTerritoryList->at(i)->getNumOfArmies());

				for (unsigned int j = 0; j < tempTerritoryList->at(i)->m_AdjacentTerritories.size(); j++)
				{
					if (j == 0)
					{
						if (tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getOwnerPointer() == m_PlayerSubject)
						{
							printf("[%03d]%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriID(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
						}
						else
						{

							printf("%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
						}

					}
					else
					{
						if (tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getOwnerPointer() == m_PlayerSubject)
						{
							printf(", [%03d]%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriID(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
						}
						else
						{

							printf(", %s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());


						}
					}
				}
				cout << endl;
			}

			vector<Continent*> * tempContinentList = m_PlayerSubject->getPlayerContinentList();
			if (tempContinentList->size() == 0)
				cout << "You do not own any continent. " << endl;
			else
			{
				cout << "You own " << tempContinentList->size() << " continent(s). " << endl;
				for (unsigned int i = 0; i < tempContinentList->size(); i++)
				{
					if (i == 0)
						cout << tempContinentList->at(i)->getContiName();
					else
					{
						cout << ", " << tempContinentList->at(i)->getContiName();
					}
				}
				cout << endl;
			}
			break;
		}


		case mySpecificTerritory:
		{
			int temp_terriID = m_PlayerSubject->m_StatusInfo.currentSelectedTerriID;
			printf("[%03d] | ", temp_terriID);
			printf("%18s | ", m_Map->getTerritoryName(temp_terriID).c_str());
			printf("Armies: (%2d) ", m_Map->getArmyNumOfTheTerritory(temp_terriID));
			cout << endl;
			break;
		}

		case myPhaseEnded:
		{
			cout << "Reinforcement phase is over. " << endl;
			m_PlayerSubject->m_StatusInfo.statusInfoInitialize();
			break;
		}

		default:
			break;

		}
		break;
	}

	case ATTACK:
	{
		
		switch (myStatus)
		{

		case myDefault:
		{
			cout << "<Attack> x" << m_PlayerSubject->getName() << "x <Attack>" << endl;

			break;
		}


		//displayer all territories of this player for ATTACK
		case myTerritories:
		{

			cout << "\nPlayer status: Attack Phase\n";
			cout << "------------------------------------------------------------------------------";
			cout << "\nPlayer " << m_PlayerSubject->getPlayerID();
			cout << ": " << m_PlayerSubject->getName() << "\n";
			cout << "------------------------------------------------------------------------------";
			cout << "\nTerritories Owned: \n";
			vector<Territory*> * tempTerritoryList = m_PlayerSubject->getPlayerTerritoryList();

			for (unsigned int i = 0; i < m_PlayerSubject->getNumberOfTerritories(); i++)
			{
				printf("[%03d] | %18s | Armies: (%2d) | Enemy Adjacent Territories: ",
					tempTerritoryList->at(i)->getTerriID(), tempTerritoryList->at(i)->getTerriName().c_str(), tempTerritoryList->at(i)->getNumOfArmies());
				bool first = true;
				for (unsigned int j = 0; j < tempTerritoryList->at(i)->m_AdjacentTerritories.size(); j++)
				{
					if (first == true)
					{
						if (tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getOwnerPointer() != m_PlayerSubject)
						{
							printf("[%03d]%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriID(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
							first = false;
						}

					}
					else
					{
						if (tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getOwnerPointer() != m_PlayerSubject)
						{
							printf(", [%03d]%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriID(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
						}
					}
				}
				cout << endl;
			}
			break;
		}


		case mySpecificTerritory:
		{
			int temp_terriID = m_PlayerSubject->m_StatusInfo.currentSelectedTerriID;
			if (m_Map->getOwnerOfTheTerritory(temp_terriID) == m_PlayerSubject)
			{
				//current player's terri
				printf("[%03d] | ", temp_terriID);
				printf("%18s | ", m_Map->getTerritoryName(temp_terriID).c_str());
				printf("Armies: (%2d) ", m_Map->getArmyNumOfTheTerritory(temp_terriID));
				cout << endl;
			}
			else
			{
				//enemy terri
				printf("<%03d> | ", temp_terriID);
				printf("%18s | ", m_Map->getTerritoryName(temp_terriID).c_str());
				printf("Armies: (%2d) ", m_Map->getArmyNumOfTheTerritory(temp_terriID));
				cout << endl;
			}
			break;
		}


		case myEnemyList:
		{
			int temp_terriID = m_PlayerSubject->m_StatusInfo.currentSelectedTerriID;
			m_Map->enemyTerriOf(temp_terriID);
			break;
		}


		case myPhaseEnded:
		{
			cout << "Attack phase is over. " << endl;
			m_PlayerSubject->m_StatusInfo.statusInfoInitialize();
			break;
		}

		default:
			break;

		}

		break;
	}


	case FORTIFICATION:
	{
		switch (myStatus)
		{

		case myDefault:
		{
			cout << "<Fortification> |" << m_PlayerSubject->getName() << "| <Fortification>" << endl;

			break;
		}


		//displayer all territories of this player for FORTIFICATION
		case myTerritories:
		{
			cout << "\nPlayer status: Fortification Phase\n";
			cout << "------------------------------------------------------------------------------";
			cout << "\nPlayer " << m_PlayerSubject->getPlayerID();
			cout << ": " << m_PlayerSubject->getName() << "\n";
			cout << "------------------------------------------------------------------------------";
			cout << "\nTerritories Owned: \n";
			vector<Territory*> * tempTerritoryList = m_PlayerSubject->getPlayerTerritoryList();
			for (unsigned int i = 0; i < m_PlayerSubject->getNumberOfTerritories(); i++)
			{
				printf("[%03d] | %18s | Armies: (%2d) | Adjacent Territories: ",
					tempTerritoryList->at(i)->getTerriID(), tempTerritoryList->at(i)->getTerriName().c_str(), tempTerritoryList->at(i)->getNumOfArmies());
				for (unsigned int j = 0; j < tempTerritoryList->at(i)->m_AdjacentTerritories.size(); j++)
				{
					if (j == 0)
					{
						if (tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getOwnerPointer() == m_PlayerSubject)
						{
							printf("[%03d]%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriID(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
						}
						else
						{

							printf("%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
						}

					}
					else
					{
						if (tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getOwnerPointer() == m_PlayerSubject)
						{
							printf(", [%03d]%s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriID(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());
						}
						else
						{

							printf(", %s(%d)",
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getTerriName().c_str(),
								tempTerritoryList->at(i)->m_AdjacentTerritories[j]->getNumOfArmies());


						}
					}
				}

				cout << endl;
			}
			break;
		}

		case mySpecificTerritory:
		{
			int temp_terriID = m_PlayerSubject->m_StatusInfo.currentSelectedTerriID;
			printf("[%03d] | ", temp_terriID);
			printf("%18s | ", m_Map->getTerritoryName(temp_terriID).c_str());
			printf("Armies: (%2d) ", m_Map->getArmyNumOfTheTerritory(temp_terriID));
			cout << endl;
			break;
		}
		
		case myPathList:
		{
			int temp_terriID = m_PlayerSubject->m_StatusInfo.currentSelectedTerriID;
			vector<vector<string>> myValidPath;
			myValidPath = (m_PlayerSubject->myPathListOfTerriID(temp_terriID));
			cout << "Vaid Path List: " << endl;
			for (unsigned int i = 0; i < myValidPath.size(); i++)
			{
				for (unsigned int j = 0; j < myValidPath.at(i).size(); j++)
				{
					int temp_ID = m_Map->getTerriAddress(myValidPath[i][myValidPath[i].size() - 1])->getTerriID();
					if (j != 0)
						cout << " -> ";
					else {
						printf("Valid Target Territory: [%03d] %18s | Path: ", temp_ID, m_Map->getTerritoryName(temp_ID).c_str());
						
					}
					cout << myValidPath.at(i).at(j);
				}
				cout << endl;
			}
			cout << "--------------------------------------------------------" << endl;
			printf("[%03d] | ", temp_terriID);
			printf("%18s | ", m_Map->getTerritoryName(temp_terriID).c_str());
			printf("Armies: (%2d) | Valid Target Territory: \n", m_Map->getArmyNumOfTheTerritory(temp_terriID));
			cout << "--------------------------------------------------------" << endl;

			for (unsigned int i = 0; i < myValidPath.size(); i++)
			{
				int temp_ID = m_Map->getTerriAddress(myValidPath[i][myValidPath[i].size() - 1])->getTerriID();

				//if (i != 0)
				//	cout << ", ";
				printf("-> [%03d] ", temp_ID);
				cout << myValidPath.at(i).at(myValidPath.at(i).size() - 1);
				cout << " (" << m_Map->getArmyNumOfTheTerritory(temp_ID) << ") ";
				cout << endl;;
			}
			cout << endl;
			break;
		}


		case myPhaseEnded:
		{
			cout << "Fortification phase is over. " << endl;
			m_PlayerSubject->m_StatusInfo.statusInfoInitialize();
			break;
		}

		default:
			break;


		}
		break;
	}


	default:
		break;
	}

	//cout << phaseString << endl;
}



////concrete Observer
//#include <iostream>
//#include <vector>
//
//using namespace std;

//declare the static vector variable
//vector<Player*> gameStatistics::listPlayers;

gameStatistics::gameStatistics() {
}

gameStatistics::gameStatistics(vector<Player*> *playerList, Map* map) {
	//m_PlayerSubject = p;
	m_MapSubject = map;
	m_MapSubject->attach(this);
	m_PlayerList = playerList;
	for (unsigned int i = 0; i < m_PlayerList->size(); i++)
	{
		m_PlayerList->at(i)->attach(this);
	}
}

gameStatistics::~gameStatistics() {
	m_MapSubject->detach(this);
	for (unsigned int i = 0; i < m_PlayerList->size(); i++)
	{
		m_PlayerList->at(i)->detach(this);
	}
}
void gameStatistics::update() {
	if (isGlobalView())
		display();
}

void gameStatistics::display() {

	cout << "=================Game Statistics==================" << endl;

	displayPlayerControl();

	cout << "==================================================" << endl;
}

void gameStatistics::displayPlayerControl() {

	int m_TotalTerritory = m_MapSubject->getTotalNumberOfTerritories();


	//to properly print out after 2 decimal
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout << "Total territory in game: " << m_MapSubject->getTotalNumberOfTerritories() << endl;
	for (int i = 0; i < m_PlayerList->size(); i++) {

		//calculate the percentage of players owned country
		double percentage = ((double)m_PlayerList->at(i)->getNumberOfTerritories() / m_TotalTerritory) * 100;

		//print the percentage of owned country
		cout << m_PlayerList->at(i)->getName() << ": (" << percentage << "%) \t";

		//output percentage in form of stars
		for (int j = 0; j < m_PlayerList->at(i)->getNumberOfTerritories(); j++) {
			if (j % 5 == 0)
				cout << " ";
			cout << "*";
		}
		cout << endl;
	}
}

bool gameStatistics::isGlobalView()
{
	for (unsigned int i = 0; i < m_PlayerList->size(); i++)
	{
		if (m_PlayerList->at(i)->m_StatusInfo.globalView)
			return true;
	}
	return false;
}