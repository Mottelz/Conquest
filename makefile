#Game 
3 : Map.o Dice.o Cards.o Player.o GameInit.o Startup.o GameLoop.o GameObserver.o Observer.o StrategyPattern.o TournamentInit.o Part3Driver.o
	g++ -std=c++11 -o p Map.o Dice.o Cards.o Player.o GameInit.o Startup.o GameLoop.o GameObserver.o  Observer.o StrategyPattern.o TournamentInit.o Part3Driver.o

1 : Map.o Dice.o Cards.o Player.o GameInit.o Startup.o GameLoop.o GameObserver.o Observer.o StrategyPattern.o TournamentInit.o combinedDriver.o
	g++ -std=c++11 -o p Map.o Dice.o Cards.o Player.o GameInit.o Startup.o GameLoop.o GameObserver.o Observer.o StrategyPattern.o TournamentInit.o combinedDriver.o

#Docs
dox : Doxyfile
	doxygen

# Game Parts
Map.o : Map.cpp Map.h
	g++ -std=c++11 -c Map.cpp

Dice.o : Dice.cpp Dice.h
	g++ -std=c++11 -c Dice.cpp

Cards.o : Cards.cpp Cards.h
	g++ -std=c++11 -c Cards.cpp

Player.o : Player.cpp Player.h
	g++ -std=c++11 -c Player.cpp

# Game Phases

GameInit.o : GameInit.cpp GameInit.h
	g++ -std=c++11 -c GameInit.cpp

Startup.o : Startup.h Startup.cpp
	g++ -std=c++11 -c Startup.cpp

GameLoop.o : GameLoop.h GameLoop.cpp
	g++ -std=c++11 -c GameLoop.cpp

TournamentInit.o : TournamentInit.cpp TournamentInit.h
	g++ -std=c++11 -c TournamentInit.cpp

# Supporting Elements
GameObserver.o : GameObserver.cpp GameObserver.h
	g++ -std=c++11 -c GameObserver.cpp

Observer.o : Observer.cpp Observer.h
	g++ -std=c++11 -c Observer.cpp

StrategyPattern.o : StrategyPattern.cpp StrategyPattern.h
	g++ -std=c++11 -c StrategyPattern.cpp

# Drivers
combinedDriver.o : combinedDriver.cpp 
	g++ -std=c++11 -c combinedDriver.cpp

Part3Driver.o : Part3Driver.cpp
	g++ -std=c++11 -c Part3Driver.cpp
#Cleaner
clean : 
	rm 1 2 3 *.o