part1 : Map.o mapDriver.o
	g++ -o 1 Map.o mapDriver.o

part2 : Map.o MapLoader.o MapLoaderDriver.o
	g++ -o 2 Map.o mapDriver.o MapLoaderDriver.o

part5 : Cards.o CardsDriver.o
	g++ -o 5 Cards.o CardsDriver.o

Map.o : Map.cpp Map.h
	g++ -c Map.cpp

mapDriver.o : mapDriver.cpp
	g++ -c mapDriver.cpp

MapLoader.o : MapLoader.h MapLoader.cpp
	g++ -c MapLoader.cpp

MapLoaderDriver.o : MapLoaderDriver.h MapLoaderDriver.cpp
	g++ -c MapLoaderDriver.cpp

Cards.o : Cards.cpp Cards.h
	g++ -c Cards.cpp

CardsDriver.o : CardsDriver.cpp
	g++ -c CardsDriver.cpp

clean : 
	rm 5 4 3 2 1 *.o