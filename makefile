#Game 
p : Map.o Dice.o Cards.o Player.o GameInit.o Startup.o GameLoop.o GameObserver.o GameStatistics.o Observer.o StrategyPattern.o combinedDriver.o
	g++ -o p Map.o Dice.o Cards.o Player.o GameInit.o Startup.o GameLoop.o GameObserver.o GameStatistics.o Observer.o StrategyPattern.o combinedDriver.o
#Docs
dox : Doxyfile
	doxygen

# Game Parts
Map.o : Map.cpp Map.h
	g++ -c Map.cpp

Dice.o : Dice.cpp Dice.h
	g++ -c Dice.cpp

Cards.o : Cards.cpp Cards.h
	g++ -c Cards.cpp

Player.o : Player.cpp Player.h
	g++ -c Player.cpp

# Game Phases

GameInit.o : GameInit.cpp GameInit.h
	g++ -c GameInit.cpp

Startup.o : Startup.h Startup.cpp
	g++ -c Startup.cpp

GameLoop.o : GameLoop.h GameLoop.cpp
	g++ -c GameLoop.cpp

# Supporting Elements
GameObserver.o : GameObserver.cpp GameObserver.h
	g++ -c GameObserver.cpp

GameStatistics.o : GameStatistics.cpp GameStatistics.h
	g++ -c GameStatistics.cpp

Observer.o : Observer.cpp Observer.h
	g++ -c Observer.cpp

StrategyPattern.o : StrategyPattern.cpp StrategyPattern.h
	g++ -c StrategyPattern.cpp

# Drivers
combinedDriver.o : combinedDriver.cpp combinedDriver.h
	g++ -c combinedDriver.cpp

#Cleaner
clean : 
	rm p *.o