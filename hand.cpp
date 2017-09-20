#include <iostream>
#include <vector>
#include "hand.h"

//Constructor and Destructor
Hand::Hand() {}
Hand::~Hand() {
    Cards.clear();
}

//Draw a card from a Deck
void Hand::addCard(Deck &deck){
    Cards.push_back(deck.Draw());
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

//        Cards.erase(std::remove(Cards.begin(), Cards.end(), &Cards[card1]), Cards.end());
//        Cards.erase(std::remove(Cards.begin(), Cards.end(), &Cards[card2]), Cards.end());
//        Cards.erase(std::remove(Cards.begin(), Cards.end(), &Cards[card3]), Cards.end());

        return deck.Exchange(cardsToSwap);

    } else if ((Cards[card1].GetType() != Cards[card2].GetType()) && (Cards[card2].GetType() != Cards[card3].GetType()) && (Cards[card1].GetType() != Cards[card3].GetType())) {

        std::vector<Card> cardsToSwap;
        Card cardObj1 = Cards[card1];
        Card cardObj2 = Cards[card2];
        Card cardObj3 = Cards[card3];

        cardsToSwap.push_back(cardObj1);
        cardsToSwap.push_back(cardObj2);
        cardsToSwap.push_back(cardObj3);

//        Cards.erase(std::remove(Cards.begin(), Cards.end(), &Cards[card1]), Cards.end());
//        Cards.erase(std::remove(Cards.begin(), Cards.end(), &Cards[card2]), Cards.end());
//        Cards.erase(std::remove(Cards.begin(), Cards.end(), &Cards[card3]), Cards.end());

        return deck.Exchange(cardsToSwap);
    } else {
        std::cout << "Those cards are not a set!" << std::endl;
        return 0;
    }

}