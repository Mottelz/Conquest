#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>
#include "card.h"

class Deck {
    private:
        std::vector<Card> Cards;
        int NumOfCards;
        int ArmiesForExchange;
    public:
        Deck();
        Deck(std::string countries[], int countriesLeng);
        Card GetCard(int i);
        int GetNumOfCards();
        ~Deck();
        Card Draw();
        int  Exchange(std::vector<Card>& cardsToSwap);
};


#endif //DECK_H
