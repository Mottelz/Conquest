#include "GameInit.h"

int main() {
    GameInit theGame = GameInit();

    theGame.getUserPrefernces();
    theGame.toString();
    theGame.~GameInit();
}