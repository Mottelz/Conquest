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


/**
* Destructor of PhaseObserver
*/
PhaseObserver::~PhaseObserver()
{
	m_PlayerSubject->detach(this);
	delete m_PlayerSubject;
	delete m_Map;
	m_PlayerSubject = nullptr;
	m_Map = nullptr;

}


/**
* update method of PhaseObserver, call display(...) if phaseView == true 
*/
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





/**
* default Constructor of gameStatistics
*/
gameStatistics::gameStatistics() {
}

/**
* Constructor of gameStatistics
*/
gameStatistics::gameStatistics(vector<Player*> *playerList, Map* map) {
	//m_PlayerSubject = p;
	m_MapSubject = map;
	m_MapSubject->attach(this);
	m_PlayerList = *playerList;
	for (unsigned int i = 0; i < m_PlayerList.size(); i++)
	{
		m_PlayerList.at(i)->attach(this);
	}
	m_TurnNumber = -1;
	m_CurrentPlayer = NULL;
}

/**
* Destructor of gameStatistics
*/
gameStatistics::~gameStatistics() {
	m_MapSubject->detach(this);
	for (unsigned int i = 0; i < m_PlayerList.size(); i++)
	{
		m_PlayerList.at(i)->detach(this);
	}
}

/**
* update method of gameStatistics, call display()
*/
void gameStatistics::update() {

	display();
		

}

/**
* bool function of gameStatistics, return true if globalView is true
*/
bool gameStatistics::isGlobalView()
{
	for (unsigned int i = 0; i < gameStatistics::m_PlayerList.size(); i++)
	{
		if (m_PlayerList.at(i)->m_StatusInfo.globalView)
			return true;
	}
	return false;
}

/**
* bool function of gameStatistics, return true if cardsView is true
*/
bool gameStatistics::isCardsView()
{
	if (m_CurrentPlayer->m_StatusInfo.cardsView == true)
		return true;
	else
	{
		return false;
	}
}

/**
* bool function of gameStatistics, return true if contiView is true
*/
bool gameStatistics::isContiView()
{
	if (m_CurrentPlayer->m_StatusInfo.contiView == true)
		return true;
	else
	{
		return false;
	}
}

/**
* A getter for the pointer of m_MapSubject
*/
Map * gameStatistics::getMap()
{
	return m_MapSubject;
}

/**
* A getter for the pointer of m_CurrentPlayer
*/
Player * gameStatistics::getCurrentPlayer()
{
	return m_CurrentPlayer;
}

/**
* A getter for the pointer of m_PlayerList
*/
vector<Player*>  gameStatistics::getPlayerList()
{
	
	return m_PlayerList;
}

/**
* void function of gameStatistics, print turn number of game statistics at every turn
*/
void gameStatistics::display()
{
	//m_display = "";
	//m_display += 
	if (!isCurrentPlayer())
	{
	//this->isCurrentPlayer();
		cout << "=================Game Statistics==================\n";
		cout << "Game round ---- Turn " << std::to_string(m_TurnNumber / (getPlayerList().size()) + 1) << endl;
		cout << "==================================================\n";
	}
	//return m_display;
	//cout << "######## current player --- " << getCurrentPlayer()->getName() << "\n";
}

/**
* bool function of gameStatistics, increament turnNumber & return true if a different player starts to play; otherwise, false
*/
bool gameStatistics::isCurrentPlayer()
{
	Player * currentPlayer = NULL;

	for (unsigned int i = 0; i < getPlayerList().size(); i++)
	{
		//if (m_PlayerList.at(i)->m_StatusInfo.currentPhase != DEFAULT && m_PlayerList.at(i)->m_StatusInfo.currentPhase != DEFENSE)
		if (getPlayerList().at(i)->m_StatusInfo.currentPhase == REINFORCEMENT)
		{
			currentPlayer = getPlayerList().at(i);
			if (m_CurrentPlayer != currentPlayer)
			{
				m_TurnNumber++;
				m_CurrentPlayer = currentPlayer;
				return false;
			}
		}
	}

	return true;
}




/**
*The Following are the functions of GameStatistics Decorator
*/

/**
* Default constructor
*/
ObserverDecorator::ObserverDecorator()
{
};

/**
* A constructor takes a pointer of gameStatistics
* \param AbstractGameStatistics * 
*/
ObserverDecorator::ObserverDecorator(AbstractGameStatistics * decoratedStatistics)
{
	this->m_DecoratedStatistics = decoratedStatistics;
	//setCurrentPlayer();
	this->m_MapSubject = getMap();
	this->m_CurrentPlayer = getCurrentPlayer();
	this->m_PlayerList = getPlayerList();
	m_MapSubject->attach(this);

	for (unsigned int i = 0; i < m_PlayerList.size(); i++)
	{
		m_PlayerList.at(i)->attach(this);
	}

}

/**
* Default destructor
*/
ObserverDecorator::~ObserverDecorator()
{
	getMap()->detach(this);
	for (unsigned int i = 0; i <getPlayerList().size(); i++)
	{
		getPlayerList().at(i)->detach(this);
	}
	//delete m_DecoratedStatistics;
}

/**
* bool function of ObserverDecorator, return true if globalView is true
*/
bool ObserverDecorator::isGlobalView()
{
	for (unsigned int i = 0; i < getPlayerList().size(); i++)
	{
		if (getPlayerList().at(i)->m_StatusInfo.globalView)
			return true;
	}
	return false;
}

/**
* bool function of ObserverDecorator, return true if cardsView is true
*/
bool ObserverDecorator::isCardsView()
{
	for (unsigned int i = 0; i < getPlayerList().size(); i++)
	{
		if (getPlayerList().at(i)->m_StatusInfo.cardsView)
			return true;
	}
	return false;
}

/**
* bool function of ObserverDecorator, return true if contiView is true
*/
bool ObserverDecorator::isContiView()
{
	for (unsigned int i = 0; i < getPlayerList().size(); i++)
	{
		if (getPlayerList().at(i)->m_StatusInfo.contiView)
			return true;
	}
	return false;
}

/**
* undecorator function of ObserverDecorator, return a pointer of its component -- AbstractGameStatistics*
*/
AbstractGameStatistics * ObserverDecorator::removeCurrentDecorator()
{
	this->~ObserverDecorator();
	return m_DecoratedStatistics;
}


/**
*  function of ObserverDecorator, call component's display
*/
void ObserverDecorator::display()
{
	m_DecoratedStatistics->display();
}

/**
* function of ObserverDecorator, return pointer of Map
*/
Map * ObserverDecorator::getMap()
{
	return (m_DecoratedStatistics->getMap());
}

/**
* function of ObserverDecorator, return pointer of Player
*/
Player * ObserverDecorator::getCurrentPlayer()
{
	return m_DecoratedStatistics->getCurrentPlayer();
}

/**
* function of ObserverDecorator, return vector<Player*>
*/
vector<Player*> ObserverDecorator::getPlayerList()
{
	return m_DecoratedStatistics->getPlayerList();
}


/**
* function of PlayerDominationObserverDecorator, call display()
*/
void PlayerDominationObserverDecorator::update()
{
	
	display();
	
}

/**
* function of ObserverDecorator, display all players' territory percentages
*/
void PlayerDominationObserverDecorator::display()
{
	if (ObserverDecorator::isGlobalView())
	{
		cout << "Call from PlayerDominationObserverDecorator" << endl;

		int m_TotalTerritory = ObserverDecorator::getMap()->getTotalNumberOfTerritories();


		//to properly print out after 2 decimal
		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);
		cout.precision(2);
		cout << "Total territory in game: " << ObserverDecorator::getMap()->getTotalNumberOfTerritories() << endl;
		for (unsigned int i = 0; i <ObserverDecorator::getPlayerList().size(); i++) {

			//calculate the percentage of players owned country
			double percentage = ((double)ObserverDecorator::getPlayerList().at(i)->getNumberOfTerritories() / m_TotalTerritory) * 100;

			//print the percentage of owned country
			cout << ObserverDecorator::getPlayerList().at(i)->getName() << ": (" << percentage << "%) \t";

			//output percentage in form of stars
			for (int j = 0; j <ObserverDecorator::getPlayerList().at(i)->getNumberOfTerritories(); j++) {
				if (j % 5 == 0)
					cout << " ";
				cout << "*";
			}
			cout << endl;
		}
		cout << "==================================================" << endl;
		getCurrentPlayer()->m_StatusInfo.globalView = false;

	}

}

/**
* bool function of PlayerDominationObserverDecorator, call isGlobalView() from parent
*/
bool PlayerDominationObserverDecorator::isGlobalView()
{
	return ObserverDecorator::isGlobalView();
}

/**
* function of PlayerDominationObserverDecorator, return pointer of Map
*/
Map * PlayerDominationObserverDecorator::getMap()
{
	return ObserverDecorator::getMap();
}

/**
* function of PlayerDominationObserverDecorator, return pointer of Player
*/
Player * PlayerDominationObserverDecorator::getCurrentPlayer()
{
	return ObserverDecorator::getCurrentPlayer();
}

/**
* function of PlayerDominationObserverDecorator, return vector<Player*>
*/
vector<Player*> PlayerDominationObserverDecorator::getPlayerList()
{
	return ObserverDecorator::getPlayerList();
}



/**
* function of PlayerHandsObserverDecorator, call display()
*/
void PlayerHandsObserverDecorator::update()
{
	display();

}

/**
* function of PlayerHandsObserverDecorator, display all players' cards
*/
void PlayerHandsObserverDecorator::display()
{
	if (ObserverDecorator::isCardsView())
	{
		cout << "Call from PlayerHandsObserverDecorator" << endl;
		for (unsigned int i = 0; i < ObserverDecorator::getPlayerList().size(); i++)
		{
			vector<Card>* temp_cards = ObserverDecorator::getPlayerList().at(i)->getCards();
			
			cout << "Player " << i << ", " << ObserverDecorator::getPlayerList().at(i)->getName() << ", has " <<temp_cards->size() << " card(s) in hand. " << endl;

			for (unsigned int j = 0; j < temp_cards->size(); j++)
			{
				cout << "Card # " << j << " | " << temp_cards->at(j).toString() << endl;
			}
			cout << "--------------------------------" << endl;
		}
		getCurrentPlayer()->m_StatusInfo.cardsView = false;

	}
}

/**
* bool function of PlayerHandsObserverDecorator, call isCardsView() from parent
*/
bool PlayerHandsObserverDecorator::isCardsView()
{
	return ObserverDecorator::isCardsView();
}

/**
* function of PlayerHandsObserverDecorator, return pointer of Map
*/
Map * PlayerHandsObserverDecorator::getMap()
{
	return ObserverDecorator::getMap();
}

/**
* function of PlayerHandsObserverDecorator, return pointer of Player
*/
Player * PlayerHandsObserverDecorator::getCurrentPlayer()
{
	return ObserverDecorator::getCurrentPlayer();
}

/**
* function of PlayerHandsObserverDecorator, return vector<Player*>
*/
vector<Player*> PlayerHandsObserverDecorator::getPlayerList()
{
	return ObserverDecorator::getPlayerList();
}


/**
* function of ContinentControlObserverDecorator, call display()
*/
void ContinentControlObserverDecorator::update()
{
	//m_DecoratedStatistics->display();
	ContinentControlObserverDecorator::display();
}

/**
* function of ContinentControlObserverDecorator, display all players' continents
*/
void ContinentControlObserverDecorator::display()
{
	if (ContinentControlObserverDecorator::isContinentView())
	{
		//string my_str = ObserverDecorator::getDisplayString();
		
		cout << "Call from ContinentControlObserverDecorator\n";

		for (unsigned int i = 0; i < ObserverDecorator::getPlayerList().size(); i++)
		{
			vector<Continent*>* temp_conti = ObserverDecorator::getPlayerList().at(i)->getPlayerContinentList();

			cout << "Player " << i << ObserverDecorator::getPlayerList().at(i)->getName() << ", owns " << temp_conti->size() << " continent(s). " << endl;

			for (unsigned int j = 0; j < temp_conti->size(); j++)
			{
				if (j != 0)
					cout << ", ";
				cout << temp_conti->at(j)->getContiName();
			}
			cout << endl;
			cout << "--------------------------------" << endl;
		}
		getCurrentPlayer()->m_StatusInfo.contiView = false;
	}
}

/**
* bool function of ContinentControlObserverDecorator, call isContinentView() from parent
*/
bool ContinentControlObserverDecorator::isContinentView()
{
	return ObserverDecorator::isContiView();
}

/**
* function of ObserverDecorator, return pointer of Map
*/
Map * ContinentControlObserverDecorator::getMap()
{
	return ObserverDecorator::getMap();
}

/**
* function of ContinentControlObserverDecorator, return pointer of Player
*/
Player * ContinentControlObserverDecorator::getCurrentPlayer()
{
	return ObserverDecorator::getCurrentPlayer();
}

/**
* function of ContinentControlObserverDecorator, return vector<Player*>
*/
vector<Player*> ContinentControlObserverDecorator::getPlayerList()
{
	return ObserverDecorator::getPlayerList();
}

AbstractGameStatistics::AbstractGameStatistics()
{
}

AbstractGameStatistics::~AbstractGameStatistics()
{
}
