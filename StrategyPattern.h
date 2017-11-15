#ifndef STRATEGYPATTERN_H
#define STRATEGYPATTERN_H
#include "Player.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Forward declarations
class Player; 
class Map;

static enum PlayerPhase {
	REINFORCEMENT, ATTACK, FORTIFICATION, DEFENSE, DEFAULT
};


/**
* The Strategy class. The parent class for all strategy types.
*/
class Strategy {
public:
	virtual void reinforce(Player* player, Map* map, Deck& deck) = 0;
	virtual bool attack(Player* player, Map* map) = 0;
	virtual bool fortify(Player* player, Map* map) = 0;
	virtual void play(Player* player, Map* map, Deck& deck) = 0;


protected: 	
	int determineExchangedArmies(Player* player, Map* map, Deck& deck);
	void placeArmiesDuringReinforcement(int assign_to, int place_num, Player* player, Map* map);
	void moveArmiesDuringFortification(int move_from, int move_to, int move_num, Player* player, Map* map);

private:
	virtual void engageInBattle(int from, int to, Player* player, Map* map) = 0;
	virtual int territoryToMoveArmyFrom(Player* player, Map* map, int move_to) = 0;

};

/**
* The HumanPlayer class. Inherits from Strategy and implements methods for Human players.
*/
class HumanPlayer : public Strategy {
public:
	void reinforce(Player* player, Map* map, Deck& deck);
	bool attack(Player* player, Map* map);
	bool fortify(Player* player, Map* map);
	void play(Player* player, Map* map, Deck& deck);

private:
	int determineExchangedArmies(Player* player, Map* map, Deck& deck);
	void engageInBattle(int from, int to, Player* player, Map* map);
	vector<int> shakeDiceCup(int armiesOfATerri, PlayerPhase phase, Player* player);
	int territoryToMoveArmyFrom(Player* player, Map* map, int move_to);
};

/**
* The AggressiveAI class. Inherits from Strategy and implements methods for aggressive computer players.
*/
class AggressiveAI : public Strategy {
public:
	void reinforce(Player* player, Map* map, Deck& deck);
	bool attack(Player* player, Map* map);
	bool fortify(Player* player, Map* map);
	void play(Player* player, Map* map, Deck& deck);

private:
	void engageInBattle(int from, int to, Player* player, Map* map);
	int getStrongestTerritory(Player* player, Map* map, PlayerPhase phase);
	int getWeakestEnemyTerritory(int attack_from, Map* map);
	vector<int> shakeDiceCup(int armiesOfATerri, PlayerPhase phase, Player* player);
	int territoryToMoveArmyFrom(Player* player, Map* map, int move_to);
};

/**
* The BenevolentAI class. Inherits from Strategy and implements methods for benevolent computer players.
*/
class BenevolentAI : public Strategy {
public:
	void reinforce(Player* player, Map* map, Deck& deck);
	bool attack(Player* player, Map* map);
	bool fortify(Player* player, Map* map);
	void play(Player* player, Map* map, Deck& deck);

private:
	int getWeakestTerritory(Player* player, Map* map, PlayerPhase phase);
	bool hasValidNeighbour(int territoryID, Map* map);
	void engageInBattle(int from, int to, Player* player, Map* map);
	int territoryToMoveArmyFrom(Player* player, Map* map, int move_to);
};

#endif //STRATEGYPATTERN_H
