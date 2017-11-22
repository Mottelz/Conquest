/** 
 * \file 
 * The header for the GameInit.cpp. Includes declaration for GameInit. 
 **/
#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
#include "Cards.h"
using namespace std;

/**
 * The class that initializes the game. 
 * \param m_MapNames The complete list of all possible maps to be added.
 * \param m_Players The list of Players.
 * \param m_MapLoader Pointer to the Maploader to be used.
 * \param m_Map Pointer to the Map object used.
 * \param m_Deck Pointer to the Deck used.
 * \param m_SelectedMap The name of the selected map.
 */
class GameInit {
private:
    vector<string> m_MapNames;
    vector<string> m_PlayerNames;
    vector<Player*> m_Players;
    MapLoader *m_MapLoader;
    Map *m_Map;
    Deck *m_Deck;
    string m_SelectedMap;
public:
    GameInit();
    ~GameInit();
    void getUserPrefernces();
    int askUserForMapSelection();
    void toString();
};