/** 
 * \file 
 * The header for the Map.cpp. Includes declaration for Map,  Territory, Continent, and MapLoader. 
 * */
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include "Player.h"
#include "Subject.h"
//#include "GameStatistics.h"
//extern bool globalView;


using namespace std;

// Forward declaration
class Player;
struct Continent;

/**
 * Territory sometimes called country in the docs. It is the smallest area on a map. (Basically, the nodes on the map.)
 * \param m_TerritoryName The name of the m_TerritoryName.
 * \param m_Position X and Y of the territories location. THis is given with all valid map files.
 * \param m_Continent Continent that the territory belongs to 
 * \param m_AdjacentTerritoriesNames Names of connected territories. 
 * \param m_AdjacentTerritories Pointers to connected territories.
 * \param m_TerritoryID Territory's ID.
 * \param m_OwnerID Owner's ID.
 * \param m_Armies Number of occupying armies. 
 * \param m_Owner Pointer to the owning Player.
 */
struct Territory {
	string m_TerritoryName;
	float m_Position[2];
	Continent* m_Continent; 
	vector<string> m_AdjacentTerritoriesNames;
	vector<Territory*> m_AdjacentTerritories; // Node pointer
	int m_TerritoryID;
	int m_OwnerID;
	int m_Armies;
	Player * m_Owner;
	Territory();
	/** Returns m_TerritoryName */
	string getTerriName() { return this->m_TerritoryName; }
	/** Returns m_TerritoryID */
	int getTerriID() { return this->m_TerritoryID; }
	/** Returns m_OwnerID */
	int getOwnerID(){ return this->m_OwnerID; }
	/** Returns m_Armies */
	int getNumOfArmies() { return this->m_Armies; }
	/** Returns m_Owner */
	Player* getOwnerPointer() { return this->m_Owner; }
	bool enemyNeighbourExists();
	void enemyNeighboursDisplay();
	bool friendNeighbourExists();
};

/**
 * Continents are made up of territories. 
 * \param m_ContinentName Name of the continent. 
 * \param m_NumberOfTerritories Number of Territories in the continent. 
 * \param m_ContinentBonus Troop bonus for owning the entire continent. 
 * \param m_ContinentLinks The number of connections to other continents. 
 * \param m_ContinentID ID for the continent. 
 * \param m_OwnerID ID of the owner.
 * \param m_Owner Pointer to the owner as a player.
 * \param m_TerritoryID IDs of all the territories.
 * \param m_ContinentTerritories Pointers for all the territories.
 */
struct Continent {
	string m_ContinentName;
	int m_NumberOfTerritories; 	// Number of all territories in the continent
	int m_ContinentBonus;
	int m_ContinentLinks;
	int m_ContinentID;
	int m_OwnerID;
	Player * m_Owner;
	vector<int> m_TerritoryID;
	vector<Territory*> m_ContinentTerritories;
	Continent();
	/** Returns m_ContinentName */
	string getContiName() { return this->m_ContinentName; }
	/** Returns m_ContinentID */
	int getContiID() { return this->m_ContinentID; }
	/** Returns m_OwnerID */
	int getOwnerID() { return this->m_OwnerID; }
	/** Returns m_Owner */
	Player* getOwnerPointer() { return this->m_Owner; }
	/** Returns m_ContinentBonus */
	int getContiBonus() { return this->m_ContinentBonus; }
	bool contiUpdate(Territory * terri);//return true if the owner info changed, otherwise false
};



/**
 * The map. This is the game's board.
 * \param m_Territories All the territories on the map.
 * \param m_Continents All the Continents on the map.
 * \param m_MapName The name of the map.
 * \param m_ValidMap Starts false. Changes to true if loaded map is valid.
 */
class Map : public Subject{
	private:
		vector<Territory> m_Territories;
		vector<Continent> m_Continents;
		string m_MapName;
		bool m_ValidMap;

	public:
		Map();
		Map(string name);
		string getMapName();
		int getTotalNumberOfTerritories();
		int getTotalNumberOfContinents();
		void setTerritoryOwner(string territory, Player* player);
		void setMapValidate(bool isValid);
		bool isValid();
		bool isAdjacent(int terriID_1, int terriID_2);
		void insertContinent(string name, int continentBonus) throw(string);
		void insertTerritory(string name, float position[2], string continentName, vector<string> adjacentTerritoriesNames) throw(string);
		int seekContinentID(string continentName);
		int seekTerritoryID(string territoryName);
		string getTerritoryName(int terriID);
		int getOwnerIDOfTheTerritory(int terriID);
		Player* getOwnerOfTheTerritory(int terriID);
		int getOwnerIDOfTheContinent(int contiID);
		Player* getOwnerOfTheContinent(int contiID);
		int getArmyNumOfTheTerritory(int terriID);
		void linkAdjacentTerritory(string territory, string adjacentTerritory);
		void linkAdjacentTerritories(string territory, vector<string> adjacentTerritories);
		void linkAdjacentTerritoryID(int territoryID) throw(string);
		void linkAllAdjacentTerritories();
		void linkAllTerritories();
		bool assignArmies(Player *_player, string territory);
		bool removeArmies(Player *_player, string territory);
		bool allTerriAssigned();
		bool isAssigned(int terriID);
		int computeTotalBonus(int playerID);
		Territory* getTerriAddress(string territory);
		Territory* getTerriAddress(int territory);
		Continent* getContiAddress(int contiID);
		vector<Territory*> terriOfPlayer(int _player);
		bool enemyNeighbourExists(int terriID);
		bool friendNeighbourExists(int terriID);
		bool seekPath(Player * _player, string startTerri, string endTerri, vector<string> &path);
		bool isRepeated(vector<string> &list, string obj);
		bool isBadMap() throw(string);
		vector<string> getAllTerritoryNames();
		void displayContinents();
		void displayTerritories();
		void toString();
		void enemyTerriOf(int terriID);
		vector<string> getEnemyAdjacentTerritoryNames(int territoryID);
		vector<string> getFriendlyAdjacentTerritoryNames(int territoryID);
		~Map();

};

/**
 * The object that loads the Mapfile. 
 */
class MapLoader {
	public:
		MapLoader();
		~MapLoader();
		void readMapFile(string &mapFile, Map &mapObject) throw(string);
};


#endif // MAP_H