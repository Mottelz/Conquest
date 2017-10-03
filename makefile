p : 
	gcc -o p

Map.o : Map.cpp Map.h
	g++ -c Map.cpp

Dice.o : Dice.cpp Dice.h
	g++ -c Dice.cpp

Cards.o : Cards.cpp Cards.h
	g++ -c Cards.cpp

Player.o : Player.cpp Player.h
	g++ -c Player.cpp

clean : 
	rm p *.o