part5 : Cards.o CardsDriver.o
	g++ -o 5 Cards.o CardsDriver.o

Cards.o : Cards.cpp Cards.h
	g++ -c Cards.cpp

CardsDriver.o : CardsDriver.cpp
	g++ -c CardsDriver.cpp

clean : 
	rm 5 4 3 2 1 *.o