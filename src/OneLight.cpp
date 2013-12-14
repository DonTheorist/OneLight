#include <iostream>

#include "Game.hpp"
#include "emscripten.h"

Game *game;

void tick();

void tick()
{
    game->tick();
}

int main(int argc, char **argv)
{
    game = new Game();
    game->initialise();

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(tick, 0, true);
#else
    while(game->isAlive())
        tick();
#endif

    delete game;

    return 0;
}

