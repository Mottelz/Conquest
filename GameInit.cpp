#include <iostream>
#include "GameInit.h"
using namespace std;

//Just creates the empty objects
GameInit::GameInit(){
    m_Map = new Map();
    m_Deck = new Deck();
    m_MapLoader = new MapLoader();
    m_MapNames = vector<string>();
    m_Players = vector<Player>();
    m_MapNames.push_back("Canada.map");
    m_MapNames.push_back("Earth.map");
    m_MapNames.push_back("Invalid.map");
    m_MapNames.push_back("Invalid2.map");
    m_MapNames.push_back("World.map");
    m_MapNames.shrink_to_fit();
}

//Destroy everything!
GameInit::~GameInit(){
    m_MapNames.clear();
    m_Players.clear();
    m_MapLoader->~MapLoader();
    m_Map->~Map();
    m_Deck->~Deck();
}

int GameInit::askUserForMapSelection(){
    int tempMap = -1;
    do {
        cout << "Use the numbers to select a map" << endl;
        for(int i = 0; i < m_MapNames.size(); i++){
            cout << i << ": " << m_MapNames[i] << endl;
        }
        cin >> tempMap;
    } while (tempMap >= m_MapNames.size() || tempMap < 0);

    return tempMap;
}


void GameInit::getUserPrefernces(){
    int tempPlayers = 0;
    bool haveMap = false;
    //get the number of players
    do {
        cout << "Select a number of players between 2 and 6" << endl;
        cin >> tempPlayers;
    } while (tempPlayers < 2 || tempPlayers > 6);
    
    for(int i = 0; i < tempPlayers; i++) {
        m_Players.push_back(Player());
    }
    
    do {
        haveMap = true;
        m_SelectedMap = "maps/" + m_MapNames[askUserForMapSelection()];
        try{
            m_MapLoader->readMapFile(m_SelectedMap, *m_Map);
        } catch (string error){
            delete m_Map;
            m_Map = new Map();
            cerr << "We got an error trying to load the map: " << endl << error << endl;
            haveMap = false;
        }
    } while (!haveMap);

    m_Deck = new Deck(m_Map->getAllTerritoryNames(), m_Map->getTotalNumberOfTerritories());
}

void GameInit::toString(){
    cout << "Here's the map:" << endl;
    m_Map->toString();
    m_Deck->toString();

    for (int i = 0; i < m_Players.size(); ++i) {
        m_Players[i].toString();
    }
}