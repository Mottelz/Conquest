a : card.o deck.o hand.o deckDriver.o main.o Map.o mapDriver.o MapLoader.o Die.o DiceCup.o DiceDriver.o MapLoaderDriver.o
	g++ -o a card.o hand.o deck.o deckDriver.o main.o Map.o mapDriver.o MapLoader.o Die.o DiceCup.o DiceDriver.o MapLoaderDriver.o

deckDriver.o : deckDriver.cpp
	g++ -c deckDriver.cpp

card.o : card.h card.cpp
	g++ -c card.cpp

deck.o : deck.h deck.cpp
	g++ -c deck.cpp

hand.o : hand.h hand.cpp
	g++ -c hand.cpp

Map.o : Map.h Map.cpp
	g++ -c Map.cpp

mapDriver.o : mapDriver.cpp
	g++ -c mapDriver.cpp

MapLoader.o : MapLoader.cpp MapLoader.h
	g++ -c MapLoader.cpp

Die.o : Die.cpp Die.h
	g++ -c Die.cpp

DiceCup.o : DiceCup.cpp DiceCup.h
	g++ -c DiceCup.cpp

DiceDriver.o : DiceDriver.cpp
	g++ -c DiceDriver.cpp

MapLoaderDriver.o : MapLoaderDriver.cpp
	g++ -c MapLoaderDriver.cpp

clean :
	rm *.o a