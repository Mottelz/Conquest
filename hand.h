#ifndef HAND_H
#define HAND_H


#include <vector>
#include "card.h"
#include "deck.h"

class Hand {
    private:
        std::vector<Card> Cards;
    public:
        Hand();
        ~Hand();
        int Exchange(Deck &deck);
        void addCard(Deck &deck);
        void printHand();
        int getHandSize();
};


#endif //HAND_H
