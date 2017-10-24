#The main parts
1 : GameInitDriver.o Map.o Dice.o Cards.o Player.o GameInit.o
	g++ -o 1 GameInitDriver.o Map.o Dice.o Cards.o Player.o GameInit.o

2 : Map.o Dice.o Cards.o Player.o Startup.o StartupDriver.o
	g++ -o 2 Map.o Dice.o Cards.o Player.o Startup.o StartupDriver.o

3 : Map.o Dice.o Cards.o Player.o GameLoop.o Startup.o GameLoopDriver.o
	g++ -o 3 Map.o Dice.o Cards.o Player.o GameLoop.o Startup.o GameLoopDriver.o

4 : Map.o Dice.o Cards.o Player.o ReinforceDriver.o
	g++ -o 4 Map.o Dice.o Cards.o Player.o ReinforceDriver.o

5 : Map.o Dice.o Cards.o Player.o AttackDriver.o
	g++ -o 5 Map.o Dice.o Cards.o Player.o AttackDriver.o

6 : FortificationDriver.o Map.o Dice.o Cards.o Player.o
	g++ -o 6 Map.o Dice.o Cards.o Player.o FortificationDriver.o

# original elements
Map.o : Map.cpp Map.h
	g++ -c Map.cpp

Dice.o : Dice.cpp Dice.h
	g++ -c Dice.cpp

Cards.o : Cards.cpp Cards.h
	g++ -c Cards.cpp

Player.o : Player.cpp Player.h
	g++ -c Player.cpp

#New elements
GameInit.o : GameInit.cpp GameInit.h
	g++ -c GameInit.cpp

Startup.o : Startup.h Startup.cpp
	g++ -c Startup.cpp

GameLoop.o : GameLoop.h GameLoop.cpp
	g++ -c GameLoop.cpp

#Drivers
GameInitDriver.o : GameInitDriver.cpp
	g++ -c GameInitDriver.cpp

StartupDriver.o : StartupDriver.cpp
	g++ -c StartupDriver.cpp

GameLoopDriver.o : GameLoopDriver.cpp
	g++ -c GameLoopDriver.cpp

ReinforceDriver.o : ReinforceDriver.cpp
	g++ -c ReinforceDriver.cpp

FortificationDriver.o : FortificationDriver.cpp
	g++ -c FortificationDriver.cpp

AttackDriver.o : AttackDriver.cpp
	g++ -c AttackDriver.cpp

#Cleaner
clean : 
	rm 1 2 3 4 5 6 *.o