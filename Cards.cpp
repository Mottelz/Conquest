#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "Cards.h"

//constructors
Card::Card(char type, std::string country) {
    //use switch to make sure it's a valid card type
    try {switch(type){
        case 'a':
        case 'c':
        case 'i':
            Card::Type = type;
            break;
        default:
            throw "Invalid card type!";
    }
    } catch(const char* e){
        std::cout << e << std::endl;
    }
    Card::Country = country;
};
Card::Card() {
    Type = 'x';
    Country = "Unknown";

}

//card getters
char Card::GetType() {
    return Type;
};

std::string Card::GetCountry() {
    return Country;
};

//card printer
void Card::PrintCard() {
    std::cout << "Type: " << GetType() << " Territory: " << GetCountry() << std::endl;
}

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

//Constructor and Destructor
Hand::Hand() {}
Hand::~Hand() {
    Cards.clear();
}

//Draw a card from a Deck
void Hand::addCard(Deck &deck){
    Cards.push_back(deck.Draw());
}

//return size of the hand
int Hand::getHandSize() {
    return Cards.size();
}

//Print all the cards in the Hand
void Hand::printHand() {
    for(unsigned int i = 0; i < Cards.size(); i++){
        std::cout << "Card #" << i << ": " << Cards[i].GetType() << " " << Cards[i].GetCountry() << std::endl;
    }
}

//swap a valid set for the armies
int Hand::Exchange(Deck &deck) {
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

    Cards[card1].PrintCard();
    Cards[card2].PrintCard();
    Cards[card3].PrintCard();



    //validate choices
    if((Cards[card1].GetType() == Cards[card2].GetType()) && (Cards[card2].GetType() == Cards[card3].GetType())){

        std::vector<Card> cardsToSwap;
        Card cardObj1 = Cards[card1];
        Card cardObj2 = Cards[card2];
        Card cardObj3 = Cards[card3];

        cardsToSwap.push_back(cardObj1);
        cardsToSwap.push_back(cardObj2);
        cardsToSwap.push_back(cardObj3);

        if (card2 > card1){
            Cards.erase(Cards.begin()+card2-1);
            if (card3 > card2) {
                Cards.erase(Cards.begin()+card3-2);
            } else {
                Cards.erase(Cards.begin()+card3-1);
            }
        } else {
            Cards.erase(Cards.begin()+card2);
            if (card3 > card2) {
                Cards.erase(Cards.begin()+card3-1);
            } else {
                Cards.erase(Cards.begin()+card3);
            }
        }

        return deck.Exchange(cardsToSwap);

    } else if ((Cards[card1].GetType() != Cards[card2].GetType()) && (Cards[card2].GetType() != Cards[card3].GetType()) && (Cards[card1].GetType() != Cards[card3].GetType())) {

        std::vector<Card> cardsToSwap;
        Card cardObj1 = Cards[card1];
        Card cardObj2 = Cards[card2];
        Card cardObj3 = Cards[card3];

        cardsToSwap.push_back(cardObj1);
        cardsToSwap.push_back(cardObj2);
        cardsToSwap.push_back(cardObj3);

        //delete the cards the if statements are there to make sure that no matter what order the numbers are entered in the results
        Cards.erase(Cards.begin()+card1);

        if (card2 > card1){
            Cards.erase(Cards.begin()+card2-1);
            if (card3 > card2) {
                Cards.erase(Cards.begin()+card3-2);
            } else {
                Cards.erase(Cards.begin()+card3-1);
            }
        } else {
            Cards.erase(Cards.begin()+card2);
            if (card3 > card2) {
                Cards.erase(Cards.begin()+card3-1);
            } else {
                Cards.erase(Cards.begin()+card3);
            }
        }

        return deck.Exchange(cardsToSwap);
    } else {
        std::cout << "Those cards are not a set!" << std::endl;
        return 0;
    }

}