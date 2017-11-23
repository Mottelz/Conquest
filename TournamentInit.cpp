/**
 * \file
 * The h for the TournamentInit.cpp. Includes definitions for TournamentInit.
 */
#include "TournamentInit.h"

/**
 * Initializes tournaments.
 */
TournamentInit::TournamentInit() {
    m_MapNames = {"maps/Canada.map", "maps/Earth.map", "maps/Discworld.map", "maps/Metro.map", "World.map"};
    m_PlayerNames = {"Marc Spector", "Steven Grant", "Jake Lockley", "Yitzak Topol", "Mr. Knight", "The Fist of Khonshu"};
    m_PlayerTypes = {"Aggressive", "Benevolent", "Random", "Cheater"};
    m_Players = {};
    m_Maps = {};
}

/**
 * Destroys tournament.
 */
TournamentInit::~TournamentInit() {
    m_Maps.clear();
    m_Winners.clear();
    m_MapNames.clear();
    m_PlayerNames.clear();
}

/**
 * Gets all the user input needed to run a tournament.
 */
void TournamentInit::getUserPreferences() {
    //Get number of maps.
    m_M = 0;
    do {
        cout << "Enter the number of maps you want used. (Max 5. Min 1.)" << endl;
        cin >> m_M;
    } while (m_M > 5 || m_M < 1);

    //Get number of games.
    m_G = 0;
    do {
        cout << "Enter the number of games per map. (Max 5. Min 1.)" << endl;
        cin >> m_G;
    } while (m_G > 5 || m_G < 1);

    //Get number of turns per game.
    m_D = 0;
    do {
        cout << "Enter the number of turns per game. (Max 50. Min 10.)" << endl;
        cin >> m_D;
    } while (m_D > 50 || m_D < 10);


    //Get the number of players.
    m_P = 0;
    do {
        cout << "Enter the number of players in the tournament. (Max 4. Min 2.)" << endl;
        cin >> m_P;
    } while (m_P > 4 || m_P < 2);

    //Get the map prefs
    askUserForMapSelection();

    //Get the player prefs.
    askUserForPlayerTypes();
}

/**
 * Asks the user for their map selections.
 * Stores result in m_SelectedMaps.
 */
void TournamentInit::askUserForMapSelection() {
    m_SelectedMaps = {};
    for(int i = 0; i < m_M; i++) {
        int tempMap = -1;
        do {
            cout << "Use the numbers to select a map" << endl;
            for (int i = 0; i < m_MapNames.size(); i++) {
                cout << i << ": " << m_MapNames[i] << endl;
            }
            cin >> tempMap;
        } while (tempMap >= m_MapNames.size() || tempMap < 0);
        m_SelectedMaps.push_back(tempMap);
    }
}

/**
 * Asks the user for their strategy selections.
 * Stores result in m_SelectedPlayerTypes.
 */
void TournamentInit::askUserForPlayerTypes() {
    m_SelectedPlayerTypes = {};
    for(int i = 0; i < m_P; i++) {
        int tempType = -1;
        do {
            cout << "Use the numbers to select the strategy for player " << i << endl;
            for (int i = 0; i < m_PlayerTypes.size(); i++) {
                cout << i << ": " << m_PlayerTypes[i] << endl;
            }
            cin >> tempType;
        } while (tempType >= m_PlayerTypes.size() || tempType < 0);
        m_SelectedPlayerTypes.push_back(tempType);
    }
}

void TournamentInit::runTournament() {
    getUserPreferences();
    MapLoader mapLoader;
	string selectedMap;
    //Make maps
    for (int i = 0; i < m_SelectedMaps.size(); i++) {
        m_Maps.push_back(new Map(m_MapNames[m_SelectedMaps[i]]));
		//selectedMap = "maps/" + m_SelectedMaps[i];
		
		try 
		{
			mapLoader.readMapFile(m_MapNames[m_SelectedMaps[i]], *m_Maps[i]);
		}
		catch (const string e) {
			cout << "*****************************************" << endl;
			cout << "Failed loading map file: " << m_MapNames[m_SelectedMaps[i]] << endl;
			cout << e << endl;
			cout << "*****************************************" << endl;
			cout << endl;
		}


        //Make players
        for (int j = 0; j < m_P; j++) {
            m_Players.push_back(new Player(m_PlayerNames[j], m_Maps[i]));
            //set strategy
            if(m_SelectedPlayerTypes[j]==1){
                AggressiveAI* aggressiveAI = new AggressiveAI();
                m_Players[j]->setStrategy(aggressiveAI);
            } else if (m_SelectedPlayerTypes[j]==2) {
                BenevolentAI* benevolentAI = new BenevolentAI();
                m_Players[j]->setStrategy(benevolentAI);
            } else if (m_SelectedPlayerTypes[j]==3) {
                RandomAI* randomAI = new RandomAI();
                m_Players[j]->setStrategy(randomAI);
            } else if (m_SelectedPlayerTypes[j]==4) {
                CheaterAI* cheaterAI = new CheaterAI();
                m_Players[j]->setStrategy(cheaterAI);
            }
        }

        //Run games
        for (int k = 0; k < m_G; k++) {
            //start the game
            Startup startup = Startup(m_Players);
            GameLoop game = GameLoop(startup);
            startup.distributeTerritories(*m_Maps[i]);
            startup.placeArmies(*m_Maps[i]);
            vector<string> cards = m_Maps[i]->getAllTerritoryNames();
            Deck* deck = new Deck(cards, cards.size());
            m_Winners.push_back(game.loop(m_Maps[i], *deck, m_D));
        }


    }

    //Print end result.
    for (int l = 0; l < m_Winners.size(); ++l) {
        cout << m_Winners[l] << endl;
    }
}