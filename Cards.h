/** 
 * \file 
 * The header for the Cards.cpp. Includes declaration for Card, Deck, and Hand. 
 **/
#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <string>
using namespace std;

/**
 * A Card class. 
 * Used to make the cards that can either be held in Deck or Hand.
 * \param m_Type A char that represents the card type infantry (i), calvary (c), or artillery (a).
 * \param m_Country The name of the country. 
 */
class Card{
private:
    char m_Type;
    string m_Country;

public:
    Card();
    Card(char type, string);
    //getters
    char getType();
    string getCountry();
    string toString();
};


/**
 * The Deck class. 
 * This is the class that stores the deck, which are all the cards that are not in a player's hand. 
 * \param m_Cards A vector of Cards. 
 * \param m_NumberOfCards The total number of cards in the Deck. 
 * \param m_ArmiesForExchange This is current number of armies that will be returned for a valid exchange of sets. 
 */
class Deck {
    private:
        std::vector<Card> m_Cards;
        int m_NumberOfCards;
        int m_ArmiesForExchange;
    public:
        Deck();
        Deck(vector<string> countries, int countriesLeng);
        Card getCard(int i);
        int getNumberOfCards();
        ~Deck();
        Card draw();
        int exchange(vector<Card>& cardsToSwap);
        string toString();
};


/**
 * Class to represent a player's hand. 
 * This is the for Cards not in the Deck. 
 * \param m_Cards A vector of Cards. 
 */
class Hand {
private:
    std::vector<Card> m_Cards;
public:
    Hand();
    ~Hand();
    int exchange(Deck &deck);
	int exchangeAI(Deck &deck);
	bool exchangeable();
    void addCard(Deck &deck);
    string toString();
    int getHandSize();
	vector<Card> * getCards();
};

#endif 