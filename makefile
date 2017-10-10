p : a2.1.o Map.o Dice.o Cards.o Player.o GameInit.o
	g++ -o p a2.1.o Map.o Dice.o Cards.o Player.o GameInit.o

Map.o : Map.cpp Map.h
	g++ -c Map.cpp

Dice.o : Dice.cpp Dice.h
	g++ -c Dice.cpp

Cards.o : Cards.cpp Cards.h
	g++ -c Cards.cpp

Player.o : Player.cpp Player.h
	g++ -c Player.cpp

GameInit.o : GameInit.cpp GameInit.h
	g++ -c GameInit.cpp

clean : 
	rm p *.o