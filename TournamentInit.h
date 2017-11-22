/**
 * \file
 * The h for the TournamentInit.cpp. Includes definitions for TournamentInit.
 */
#pragma once
#include "GameInit.h"
#include "GameLoop.h"
#include "GameObserver.h"
#include "Player.h"
#include "Startup.h"
#include <vector>

/**
 * The class that inits and runs tournaments.
 * \param m_G Number of games played on a map.
 * \param m_D Number of turns per game.
 * \param m_P Number of players
 * \param m_M number of maps.
 * \param m_Maps Maps the games will be played on.
 * \param m_Winners Winner of each game.
 * \param m_MapNames Names for maps.
 * \param m_PlayerNames Names for players.
 */
class TournamentInit {
public:
    TournamentInit();
    ~TournamentInit();
    void getUserPreferences();
    void loadMaps();
    void runTournament();
    void askUserForMapSelection();
    void askUserForPlayerTypes();
private:
    int m_G;
    int m_D;
    int m_P;
    int m_M;
    vector<Map*> m_Maps;
    vector<Player*> m_Players;
    vector<string> m_Winners;
    vector<string> m_MapNames;
    vector<string> m_PlayerNames;
    vector<string> m_PlayerTypes;
    vector<int> m_SelectedPlayerTypes;
    vector<int> m_SelectedMaps;
};
