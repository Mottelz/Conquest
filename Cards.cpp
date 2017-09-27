#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "Cards.h"

//constructors
Card::Card(char type, std::string country) {
    //Use switch to make sure it's a valid card type
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
        std::cout << e << std::endl;
    }
    m_Country = country;
};

Card::Card() {
	m_Type = 'x';
	m_Country = "Unknown";

}

//card getters
char Card::getType() {
    return m_Type;
};

std::string Card::getCountry() {
    return m_Country;
};

//card printer
void Card::printCard() {
    std::cout << "Type: " << getType() << " Territory: " << getCountry() << std::endl;
}

//constructors
Deck::Deck() {}

Deck::Deck(std::string countries[], int countriesLeng) {

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

Deck::~Deck() {
	m_Cards.clear();
}

//card getter
Card Deck::getCard(int i) {
    return m_Cards[i];
}

int Deck::getNumberOfCards() {
    return m_NumberOfCards;
}


Card Deck::draw() {
    //this is a psuedo random method for shuffling (i think), but it does always return a random one :)
    std::random_shuffle(m_Cards.begin(), m_Cards.end());
    //temp grab card
    Card cardToReturn = m_Cards[0];
    //remove card and resize deck
    m_Cards.erase((m_Cards.begin()));
    m_Cards.shrink_to_fit();
    //return card
    return cardToReturn;
}


int Deck::exchange(std::vector<Card> &cardsToSwap) {
    //put the cards back
    for (int i = 0; i < cardsToSwap.size(); ++i) {
        m_Cards.push_back(cardsToSwap[i]);
    }
    //increase and return armies
    m_ArmiesForExchange += 5;
    return m_ArmiesForExchange;
}

//Constructor and Destructor
Hand::Hand() {}
Hand::~Hand() {
	m_Cards.clear();
}

//Draw a card from a Deck
void Hand::addCard(Deck &deck){
	m_Cards.push_back(deck.draw());
}

//return size of the hand
int Hand::getHandSize() {
    return m_Cards.size();
}

//Print all the cards in the Hand
void Hand::printHand() {
    for(unsigned int i = 0; i < m_Cards.size(); i++){
        std::cout << "Card #" << i << ": " << m_Cards[i].getType() << " " << m_Cards[i].getCountry() << std::endl;
    }
}

//swap a valid set for the armies
int Hand::exchange(Deck &deck) {
    int card1;
    int card2;
    int card3;

    //show hand and ask for cards
    printHand();
    std::cout << "Please select three cards to exchange by entering their numbers with a line break or space between them. \n"
            "The cards must each all have the same type or be one of each type.\n" << std::endl;

    //read in cards
    std::cin >> card1;
    std::cin >> card2;
    std::cin >> card3;

	m_Cards[card1].printCard();
	m_Cards[card2].printCard();
	m_Cards[card3].printCard();



    //validate choices
    if((m_Cards[card1].getType() == m_Cards[card2].getType()) && (m_Cards[card2].getType() == m_Cards[card3].getType())){

        std::vector<Card> cardsToSwap;
        Card cardObj1 = m_Cards[card1];
        Card cardObj2 = m_Cards[card2];
        Card cardObj3 = m_Cards[card3];

        cardsToSwap.push_back(cardObj1);
        cardsToSwap.push_back(cardObj2);
        cardsToSwap.push_back(cardObj3);

        if (card2 > card1){
			m_Cards.erase(m_Cards.begin()+(card2-1));
            if (card3 > card2) {
				m_Cards.erase(m_Cards.begin()+(card3-2));
            } else {
				m_Cards.erase(m_Cards.begin()+(card3-1));
            }
        } else {
			m_Cards.erase(m_Cards.begin()+card2);
            if (card3 > card2) {
				m_Cards.erase(m_Cards.begin()+(card3-1));
            } else {
				m_Cards.erase(m_Cards.begin()+card3);
            }
        }

        return deck.exchange(cardsToSwap);

    } else if ((m_Cards[card1].getType() != m_Cards[card2].getType()) && (m_Cards[card2].getType() != m_Cards[card3].getType()) && (m_Cards[card1].getType() != m_Cards[card3].getType())) {

        std::vector<Card> cardsToSwap;
        Card cardObj1 = m_Cards[card1];
        Card cardObj2 = m_Cards[card2];
        Card cardObj3 = m_Cards[card3];

        cardsToSwap.push_back(cardObj1);
        cardsToSwap.push_back(cardObj2);
        cardsToSwap.push_back(cardObj3);

        //delete the cards the if statements are there to make sure that no matter what order the numbers are entered in the results
		m_Cards.erase(m_Cards.begin()+card1);

        if (card2 > card1){
			m_Cards.erase(m_Cards.begin()+(card2-1));
            if (card3 > card2) {
				m_Cards.erase(m_Cards.begin()+(card3-2));
            } else {
				m_Cards.erase(m_Cards.begin()+(card3-1));
            }
        } else {
			m_Cards.erase(m_Cards.begin()+card2);
            if (card3 > card2) {
				m_Cards.erase(m_Cards.begin()+(card3-1));
            } else {
				m_Cards.erase(m_Cards.begin()+card3);
            }
        }

        return deck.exchange(cardsToSwap);
    } else {
        std::cout << "Those cards are not a set!" << std::endl;
        return 0;
    }

}