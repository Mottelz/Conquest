#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <string>

class Card{
private:
    //intended to store the card type: infantry (i), calvary (c), or artillery (a)
    char m_Type;
    //the country name
    std::string m_Country;

public:
    //create
    Card();
    Card(char type, std::string);
    //getters
    char getType();
    std::string getCountry();
    void printCard();
};

class Deck {
    private:
        std::vector<Card> m_Cards;
        int m_NumberOfCards;
        int m_ArmiesForExchange;
    public:
        Deck();
        Deck(std::vector<std::string> countries, int countriesLeng);
        Card getCard(int i);
        int getNumberOfCards();
        ~Deck();
        Card draw();
        int exchange(std::vector<Card>& cardsToSwap);
};

class Hand {
private:
    std::vector<Card> m_Cards;
public:
    Hand();
    ~Hand();
    int exchange(Deck &deck);
    void addCard(Deck &deck);
    void printHand();
    int getHandSize();
};

#endif 