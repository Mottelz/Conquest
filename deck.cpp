#include <random>
#include <iostream>
#include "deck.h"

//constructor
Deck::Deck(std::string countries[], int countriesLeng) {

    for (unsigned int i = 0; i < countriesLeng; ++i) {
        //assign type based on mod 3
        if (i % 3 == 0){
        Cards.push_back(Card('a', countries[i]));
        }
        else if (i % 3 == 1) {
            Cards.push_back(Card('c', countries[i]));
        }
        else if(i % 3 == 2) {
            Cards.push_back(Card('i', countries[i]));
        }
    }
    //Shrink to size
    Cards.shrink_to_fit();
    //track total number of cards
    NumOfCards = countriesLeng;
    //Start at zero because it increases before returning in Exchange()
    ArmiesForExchange = 0;
}

Deck::~Deck() {
    Cards.clear();
}

//card getter
Card Deck::GetCard(int i) {
    return Cards[i];
}

int Deck::GetNumOfCards() {
    return NumOfCards;
}


Card Deck::Draw() {
    //this is a psuedo random method for shuffling (i think), but it does always return a random one :)
    std::random_shuffle(Cards.begin(), Cards.end());
    //temp grab card
    Card cardToReturn = Cards[0];
    //remove card and resize deck
    Cards.erase((Cards.begin()));
    Cards.shrink_to_fit();
    //return card
    return cardToReturn;
}


int Deck::Exchange(std::vector<Card> &cardsToSwap) {
    //put the cards back
    for (int i = 0; i < cardsToSwap.size(); ++i) {
        Cards.push_back(cardsToSwap[i]);
    }
    //increase and return armies
    ArmiesForExchange += 5;
    return ArmiesForExchange;
}