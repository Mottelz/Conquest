#include <iostream>
#include <string>
#include "card.h"

//constructors
//ideal (and only valid constructor)
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