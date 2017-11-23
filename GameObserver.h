#pragma once
#include "Observer.h"
#include "Player.h"

//using namespace std;

//class gameStatistics : public Observer {};
//class ObserverDecorator : public gameStatistics {};
//class PlayerDominationObserverDecorator : public ObserverDecorator{};
//class PlayerHandsObserverDecorator : public ObserverDecorator
//{};
//class ContinentControlObserverDecorator : public ObserverDecorator
//{};


/**
* The PhaseObserver class, inherited from Observer.
*/
class PhaseObserver : public Observer
{
public:
	PhaseObserver();
	PhaseObserver(Player* m_PS, Map *map);
	~PhaseObserver();
	void update();
	void display(PlayerPhase myPhase, PlayerStatus myStatus);
	//void display(int phaseID, int caseID);
private:
	Player *m_PlayerSubject;
	Map * m_Map;
};

//include all class using notify


/**
* The AbstractGameStatistics class, inherited from Observer.
*/
class AbstractGameStatistics : public Observer {
public:
	AbstractGameStatistics();
	~AbstractGameStatistics();
	virtual void display() = 0;
	virtual bool isGlobalView() = 0;
	virtual bool isCardsView() = 0;
	virtual bool isContiView() = 0;
	virtual Player* getCurrentPlayer() = 0;
	virtual Map* getMap() = 0;
	virtual vector<Player*> getPlayerList() = 0;
	virtual AbstractGameStatistics* removeCurrentDecorator() = 0;

};

/**
* The gameStatistics class, inherited from AbstractGameStatistics.
*/
class gameStatistics : public AbstractGameStatistics {

public:
	gameStatistics();
	gameStatistics(vector<Player*> *playerList, Map * map);
	~gameStatistics();
	void update();
	void display();
	//void displayPlayerControl();
	bool isGlobalView();
	bool isCardsView(); 
	bool isContiView();
	AbstractGameStatistics* removeCurrentDecorator() { return this; }
	Map * getMap();
	Player * getCurrentPlayer();
	vector<Player*> getPlayerList();

	//void display();

private:
	//	Player *m_PlayerSubject;
	Map *m_MapSubject;

	vector<Player*> m_PlayerList;

	int m_TurnNumber;

	Player * m_CurrentPlayer;

	bool isCurrentPlayer();

	string m_display;
};




/**
* The ObserverDecorator class, inherited from AbstractGameStatistics.
*/
class ObserverDecorator : public AbstractGameStatistics {
public:
	ObserverDecorator();
	ObserverDecorator(AbstractGameStatistics * decoratedStatistics);
	~ObserverDecorator();
	//void update();
	void display()=0;
	Map * getMap();
	Player * getCurrentPlayer();
	vector<Player*> getPlayerList();
	//gameStatistics * getObject();
	bool isGlobalView();
	bool isCardsView();
	bool isContiView();

	AbstractGameStatistics * removeCurrentDecorator();
	//void setCurrentPlayer();
	//string getDisplayString();
protected:
	AbstractGameStatistics * m_DecoratedStatistics;

	Map *m_MapSubject;

	vector<Player*> m_PlayerList;

	Player * m_CurrentPlayer;


};


/**
* The PlayerDominationObserverDecorator class, inherited from ObserverDecorator.
*/
class PlayerDominationObserverDecorator : public ObserverDecorator
{
public:
	
	PlayerDominationObserverDecorator(AbstractGameStatistics * decoratedStatistics) : ObserverDecorator(decoratedStatistics) {};
	//~PlayerDominationObserverDecorator();
	void update();
	void display();
	bool isGlobalView();
	Map * getMap();
	Player * getCurrentPlayer();
	vector<Player*> getPlayerList();
	//string getDisplayString();
	//AbstractGameStatistics * m_DecoratedStatistics;

	//Map *m_MapSubject;

	//vector<Player*> m_PlayerList;

	//Player * m_CurrentPlayer;


};

/**
* The PlayerHandsObserverDecorator class, inherited from ObserverDecorator.
*/
class PlayerHandsObserverDecorator : public ObserverDecorator
{
public:
	PlayerHandsObserverDecorator(AbstractGameStatistics * decoratedStatistics) : ObserverDecorator(decoratedStatistics) {};
	//~PlayerHandsObserverDecorator();
	void update();
	void display();
	bool isCardsView();
	Map * getMap();
	Player * getCurrentPlayer();
	vector<Player*> getPlayerList();



};

/**
* The ContinentControlObserverDecorator class, inherited from ObserverDecorator.
*/
class ContinentControlObserverDecorator : public ObserverDecorator
{
public:
	ContinentControlObserverDecorator(AbstractGameStatistics * decoratedStatistics) : ObserverDecorator(decoratedStatistics) {};
	//~ContinentControlObserverDecorator();
	void update();
	void display();
	bool isContinentView();
	Map * getMap();
	Player * getCurrentPlayer();
	vector<Player*> getPlayerList();


};

