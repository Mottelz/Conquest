#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"
#include "Cards.h"
using namespace std;


class GameInit {
private:
    vector<string> m_MapNames;
    vector<Player> m_Players;
    MapLoader *m_MapLoader;
    Map *m_Map;
    Deck *m_Deck;
    string m_SelectedMap;
public:
    GameInit();
    ~GameInit();
    void createMap();
    void createDeck();
    void getUserPrefernces();
    int askUserForMapSelection();
    void toString();
};