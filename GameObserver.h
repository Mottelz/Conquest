#pragma once
#include "Observer.h"
#include "Player.h"


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

class gameStatistics : public Observer {

public:
	gameStatistics();
	gameStatistics(vector<Player*> *playerList, Map * map);
	~gameStatistics();
	void update();
	void display();
	void displayPlayerControl();
	bool isGlobalView();

private:
	//	Player *m_PlayerSubject;
	Map *m_MapSubject;

	vector<Player*>* m_PlayerList;
};