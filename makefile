p : card.o deck.o hand.o deckDriver.o
	g++ -o p card.o hand.o deck.o deckDriver.o

deckDriver.o : deckDriver.cpp
	g++ -c deckDriver.cpp

card.o : card.h card.cpp
	g++ -c card.cpp

deck.o : deck.h deck.cpp
	g++ -c deck.cpp

hand.o : hand.h hand.cpp
	g++ -c hand.cpp

clean :
	rm *.o p