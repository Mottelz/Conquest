#include <iostream>
#include "GameInit.h"
using namespace std;

//Just creates the empty objects
GameInit::GameInit(){
    Map m_Map = Map();
    Deck m_Deck = Deck();
    MapLoader m_MapLoader = MapLoader();
    vector<string> m_MapNames;
    m_MapNames.push_back("Canada.map");
    m_MapNames.push_back("Earth.map");
    m_MapNames.push_back("Invalid.map");
    m_MapNames.push_back("Invalid2.map");
    m_MapNames.push_back("World.map");
    m_MapNames.shrink_to_fit();
}

//Destory everything!
GameInit::~GameInit(){
    m_Map.~Map();
    m_Deck.~Deck();
    m_MapLoader.~MapLoader();
    m_MapNames.clear();
    m_Players.clear();
}

int GameInit::askUserForMapSelection(){
    int tempMap = -1;
    do {
        cout << "Use the numbers to select a map" << cout;
        for(int i = 0; i < m_MapNames.size(); i++){
            cout << char(i) << ": " << m_MapNames[i] << endl;
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
    
    for(int i = 0; i <= tempPlayers; i++) {
        m_Players.push_back(Player());
    }
    
    do {
        m_SelectedMap = m_MapNames[askUserForMapSelection()];
        try{
            m_MapLoader.readMapFile(m_SelectedMap, m_Map);
        } catch (string error){
            cerr << "We got an error trying to load the map: " << endl << error << endl;
            break;
        }
        haveMap = true;
    } while (!haveMap);

    m_Deck = Deck(m_Map.getAllTerritoryNames(), m_Map.getTotalNumberOfTerritories());
}