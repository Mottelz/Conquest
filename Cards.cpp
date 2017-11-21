/** 
 * \file 
 * The cpp for the Cards.h. Includes definitions for Card, Deck, and Hand. 
 **/
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <string>
#include "Cards.h"
using namespace std;

/**
 * Constrctor that makes sure you entered a valid type. 
 * \param type A char to set the m_type. 
 * \param country A string with the name of the country/territory. 
 */
Card::Card(char type, string country) {
    try {switch(type){
        case 'a':
        case 'c':
        case 'i':
            m_Type = type;
            break;
        default:
            throw "Invalid card type!";
    }
    } catch(const char* e){
        cout << e << endl;
    }
    m_Country = country;
};
/**
 * Default Constructor. Creates card of type x. 
 */
Card::Card() {
	m_Type = 'x';
	m_Country = "Unknown";

}

/**
 * Returns the type of the card. 
 */
char Card::getType() {
    return m_Type;
};
/**
 * Returns the name of the territory on the card. 
 */
string Card::getCountry() {
    return m_Country;
};

/**
 * Returns a string that looks like "Type: a Territory: Montreal"
 */
string Card::toString() {
    string toReturn; 
    toReturn += "Type: "; 
    toReturn += getType();
    toReturn += " Territory: " + getCountry();
    return toReturn;
}

/**
 * Default constrcutor. Creates an empty Deck. 
 */
Deck::Deck() {}

/**
 * Constructor that creates and populates the deck.
 * \param countries Vector of all the countries/territories. 
 * \param countriesLeng The total number of countries. 
 */
Deck::Deck(vector<string> countries, int countriesLeng) {

    for (unsigned int i = 0; i < countriesLeng; ++i) {
        //assign type based on mod 3
        if (i % 3 == 0){
			m_Cards.push_back(Card('a', countries[i]));
        }
        else if (i % 3 == 1) {
			m_Cards.push_back(Card('c', countries[i]));
        }
        else if(i % 3 == 2) {
			m_Cards.push_back(Card('i', countries[i]));
        }
    }
    //Shrink to size
	m_Cards.shrink_to_fit();
    //track total number of cards
	m_NumberOfCards = countriesLeng;
    //Start at zero because it increases before returning in exchange()
	m_ArmiesForExchange = 0;
}

/**
 * Destructor. clears out the cards vector. 
 */
Deck::~Deck() {
	m_Cards.clear();
}

/**
 * Returns card at a given index. 
 * \param i Int representing the wanted index. 
 */
Card Deck::getCard(int i) {
    return m_Cards[i];
}

/**
 * Returns the total number of cards in play. Not the current deck size. 
 */
int Deck::getNumberOfCards() {
    return m_NumberOfCards;
}

/**
 * Rerutns a random card from the Deck.
 */
Card Deck::draw() {
    //this is a psuedo random method for shuffling (i think), but it does always return a random one :)
    random_shuffle(m_Cards.begin(), m_Cards.end());
    //temp grab card
    Card cardToReturn = m_Cards[0];
    //remove card and resize deck
    m_Cards.erase((m_Cards.begin()));
    m_Cards.shrink_to_fit();
    //return card
    return cardToReturn;
}

/**
 * Puts the cards back in the deck and returns the number of armies to add as a bonus. 
 * \param cardsToSwap The vector of cards to be added. 
 */
int Deck::exchange(vector<Card> &cardsToSwap) {
    //put the cards back
    for (int i = 0; i < cardsToSwap.size(); ++i) {
        m_Cards.push_back(cardsToSwap[i]);
    }
    //increase and return armies
    m_ArmiesForExchange += 5;
    return m_ArmiesForExchange;
}

/**
 * Returns a string made of all the cards in the deck. 
 * \see Card.toString()
 */
string Deck::toString(){
    string toReturn;
    toReturn += "Here is the deck: \n";
    for(int i = 0; i < m_Cards.size(); i++){
        toReturn += m_Cards[i].toString() +"\n";
    }
    return toReturn;
}

/**
 * The default constructor. Creates an empty hand. 
 */
Hand::Hand() {}

/**
 * Destuctor. Clears out the hand. 
 */
Hand::~Hand() {
	m_Cards.clear();
}

/**
 * Draws a card from the given Deck.
 * \see Deck.draw
 * \param deck The deck that the card will be drawn from. 
 */
void Hand::addCard(Deck &deck){
	m_Cards.push_back(deck.draw());
}

/**
 * Gives the actual number of cards in the Hand. 
 */
int Hand::getHandSize() {
    return m_Cards.size();
}

/**
* Return pointer of cards from Hand
*/
vector<Card>* Hand::getCards()
{
	return &m_Cards;
}

/**
 * Returns a string a which shows all the cards in the hand. 
 */
string Hand::toString() {
    string toReturn;
    for(unsigned int i = 0; i < m_Cards.size(); i++){
		toReturn += "Card #"; 
        toReturn += to_string(i);
        toReturn += ": " + m_Cards[i].toString();
		toReturn += "\n";
    }
    return toReturn;
}

/**
 * Checks for valid set and exchanges it with the fed into the Deck.
 * \param deck The Deck that the cards will be put back in. 
 * \see Deck.exchange
 */
int Hand::exchange(Deck &deck) {
    int card1;
    int card2;
    int card3;

    //show hand and ask for cards
    cout << toString();
    cout << "Please select three cards to exchange by entering their numbers with a line break or space between them. \n"
            "The cards must each all have the same type or be one of each type.\n" << endl;

    //read in cards
    cin >> card1;
    cin >> card2;
    cin >> card3;

	cout << m_Cards[card1].toString();
	cout << m_Cards[card2].toString();
	cout << m_Cards[card3].toString();



    //validate choices
    if((m_Cards[card1].getType() == m_Cards[card2].getType()) && (m_Cards[card2].getType() == m_Cards[card3].getType())){

        vector<Card> cardsToSwap;
        Card cardObj1 = m_Cards[card1];
        Card cardObj2 = m_Cards[card2];
Card cardObj3 = m_Cards[card3];

cardsToSwap.push_back(cardObj1);
cardsToSwap.push_back(cardObj2);
cardsToSwap.push_back(cardObj3);

if (card2 > card1) {
	m_Cards.erase(m_Cards.begin() + (card2 - 1));
	if (card3 > card2) {
		m_Cards.erase(m_Cards.begin() + (card3 - 2));
	}
	else {
		m_Cards.erase(m_Cards.begin() + (card3 - 1));
	}
}
else {
	m_Cards.erase(m_Cards.begin() + card2);
	if (card3 > card2) {
		m_Cards.erase(m_Cards.begin() + (card3 - 1));
	}
	else {
		m_Cards.erase(m_Cards.begin() + card3);
	}
}

return deck.exchange(cardsToSwap);

	}
 else if ((m_Cards[card1].getType() != m_Cards[card2].getType()) && (m_Cards[card2].getType() != m_Cards[card3].getType()) && (m_Cards[card1].getType() != m_Cards[card3].getType())) {

	 vector<Card> cardsToSwap;
	 Card cardObj1 = m_Cards[card1];
	 Card cardObj2 = m_Cards[card2];
	 Card cardObj3 = m_Cards[card3];

	 cardsToSwap.push_back(cardObj1);
	 cardsToSwap.push_back(cardObj2);
	 cardsToSwap.push_back(cardObj3);

	 //delete the cards the if statements are there to make sure that no matter what order the numbers are entered in the results
	 m_Cards.erase(m_Cards.begin() + card1);

	 if (card2 > card1) {
		 m_Cards.erase(m_Cards.begin() + (card2 - 1));
		 if (card3 > card2) {
			 m_Cards.erase(m_Cards.begin() + (card3 - 2));
		 }
		 else {
			 m_Cards.erase(m_Cards.begin() + (card3 - 1));
		 }
	 }
	 else {
		 m_Cards.erase(m_Cards.begin() + card2);
		 if (card3 > card2) {
			 m_Cards.erase(m_Cards.begin() + (card3 - 1));
		 }
		 else {
			 m_Cards.erase(m_Cards.begin() + card3);
		 }
	 }

	 return deck.exchange(cardsToSwap);
 }
 else {
	 cout << "Those cards are not a set!" << endl;
	 return 0;
 }

}

/**
* Automatically exchanges cards for AI.
* \param deck The Deck that the cards will be put back in.
* \see Deck.exchange
*/
int Hand::exchangeAI(Deck &deck) {

	vector<Card> typeA;
	vector<Card> typeC;
	vector<Card> typeI;

	for (int i = 0; i < this->getHandSize(); i++)
	{
		if (this->m_Cards[i].getType() == 'a')
			typeA.push_back(m_Cards[i]);
		if (this->m_Cards[i].getType() == 'c')
			typeC.push_back(m_Cards[i]);
		if (this->m_Cards[i].getType() == 'i')
			typeI.push_back(m_Cards[i]);
	}

	vector<Card> cardsToSwap;

	if (typeA.size() >= 3)
	{
		cardsToSwap.push_back(typeA[0]);
		cardsToSwap.push_back(typeA[1]);
		cardsToSwap.push_back(typeA[2]);

		cout << "\n Exchanging: " << endl;
		cout << cardsToSwap[0].toString() << endl;
		cout << cardsToSwap[1].toString() << endl;
		cout << cardsToSwap[2].toString() << endl;

		return deck.exchange(cardsToSwap);
	}
	else if (typeC.size() >= 3)
	{
		cardsToSwap.push_back(typeC[0]);
		cardsToSwap.push_back(typeC[1]);
		cardsToSwap.push_back(typeC[2]);

		cout << "\n Exchanging: " << endl;
		cout << cardsToSwap[0].toString() << endl;
		cout << cardsToSwap[1].toString() << endl;
		cout << cardsToSwap[2].toString() << endl;

		return deck.exchange(cardsToSwap);
	}
	else if (typeI.size() >= 3)
	{
		cardsToSwap.push_back(typeI[0]);
		cardsToSwap.push_back(typeI[1]);
		cardsToSwap.push_back(typeI[2]);

		cout << "\n Exchanging: " << endl;
		cout << cardsToSwap[0].toString() << endl;
		cout << cardsToSwap[1].toString() << endl;
		cout << cardsToSwap[2].toString() << endl;

		return deck.exchange(cardsToSwap);
	}
	else // since we already verified that there are exchangeable cards, default condition is that player has at least one card of each type.
	{
		cardsToSwap.push_back(typeA[0]);
		cardsToSwap.push_back(typeC[0]);
		cardsToSwap.push_back(typeI[0]);

		cout << "\n Exchanging: " << endl;
		cout << cardsToSwap[0].toString() << endl;
		cout << cardsToSwap[1].toString() << endl;
		cout << cardsToSwap[2].toString() << endl;

		return deck.exchange(cardsToSwap);
	}


	return deck.exchange(cardsToSwap);
}

/**
 * Returns true if the there is a set that can be exchanged, else returns false. 
 */
bool Hand::exchangeable()
{
	if (this->getHandSize()<3)
		return false;
	else
	{
		int typeA = 0, typeC = 0, typeI = 0;
		for (int i = 0; i < this->getHandSize(); i++)
		{
			if (this->m_Cards[i].getType() == 'a')
				typeA++;
			if (this->m_Cards[i].getType() == 'c')
				typeC++;
			if (this->m_Cards[i].getType() == 'i')
				typeI++;

		}
		if (typeA >= 3 || typeC >= 3 || typeI >= 3 || (typeA > 0 && typeC > 0 && typeI > 0))
			return true;
	}
	return false;
}
