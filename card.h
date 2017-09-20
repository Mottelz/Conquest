#ifndef CARD_H
#define CARD_H
//since card is just data using struct
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

#endif //CARD_H