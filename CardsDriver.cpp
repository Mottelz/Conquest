#include <iostream>
#include "Cards.h"

int main() {

    std::string cities[] = {"Montreal", "New York", "Ottawa", "Boston", "Tel Aviv", "London", "Hell", "Hogwarts", "Blooper Land"};

    //create decks
    Deck testDeck1 = Deck(cities, 9);
    Deck testDeck2 = Deck(cities, 9);

    //type counters
    int numOfInf = 0;
    int numOfCav = 0;
    int numOfArt = 0;

    for (int j = 0; j < testDeck1.GetNumOfCards(); ++j) {
        //temp card
        Card tempCard = testDeck1.Draw();
        if (tempCard.GetType() == 'a') {
            numOfArt++;
        } else if (tempCard.GetType() == 'c') {
            numOfCav++;
        } else if (tempCard.GetType() == 'i') {
            numOfInf++;
        }
    }

    //display totals
    std::cout << "Total Infantry: " << numOfInf << std::endl;
    std::cout << "Total Cavalry: " << numOfCav << std::endl;
    std::cout << "Total Artillery: " << numOfArt << std::endl;

    //create hand
    Hand Mottel = Hand();

    //draw a full hand
    for (int i = 0; i < 5; ++i) {
        Mottel.addCard(testDeck2);
    }

    int armies;

    do {
        //exchange armies and print result
        armies = Mottel.Exchange(testDeck2);
        std::cout << "Number of armies returned " << armies << std::endl;

        //refill hand
        for (int i = Mottel.getHandSize(); i < 5; ++i) {
            Mottel.addCard(testDeck2);
        }
    } while (armies < 15);

    return 0;
}