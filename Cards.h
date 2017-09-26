#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <string>

class Card{
private:
    //intended to store the card type: infantry (i), calvary (c), or artillery (a)
    char Type;
    //the country name
    std::string Country;

public:
    //create
    Card();
    Card(char type, std::string);
    //getters
    char GetType();
    std::string GetCountry();
    void PrintCard();
};

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

#endif 