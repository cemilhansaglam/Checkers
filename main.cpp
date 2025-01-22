// main.cpp
#include "Game.hpp"

int main()
{
    Game* game = new Game();

    // Call run() method
    game->run();

    // Free allocated memory
    delete game;

    return 0;
}
