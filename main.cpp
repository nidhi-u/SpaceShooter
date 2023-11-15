// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Game.h"
#include<time.h>

int main()
{
    std::srand(time(0));

    // Init game
    Game game;
    game.runGame();

    // End of application
    return 0;
}

