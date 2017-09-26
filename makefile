1 : Map.o mapDriver.o
	g++ -o 1 Map.o mapDriver.o

2 : Map.o MapLoader.o MapLoaderDriver.o
	g++ -o 2 Map.o MapLoader.o MapLoaderDriver.o

3 : Dice.o DiceDriver.o
	g++ -o 3 Dice.o DiceDriver.o

5 : Cards.o CardsDriver.o
	g++ -o 5 Cards.o CardsDriver.o

Map.o : Map.cpp Map.h
	g++ -c Map.cpp

mapDriver.o : mapDriver.cpp
	g++ -c mapDriver.cpp

MapLoader.o : MapLoader.h MapLoader.cpp
	g++ -c MapLoader.cpp

MapLoaderDriver.o : MapLoaderDriver.cpp
	g++ -c MapLoaderDriver.cpp

Dice.o : Dice.cpp Dice.h
	g++ -c Dice.cpp

DiceDriver.o : DiceDriver.cpp
	g++ -c DiceDriver.cpp

Cards.o : Cards.cpp Cards.h
	g++ -c Cards.cpp

CardsDriver.o : CardsDriver.cpp
	g++ -c CardsDriver.cpp

clean : 
	rm 5 4 3 2 1 *.o