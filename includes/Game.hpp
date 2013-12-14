#ifndef ONELIGHT_GAME_H
#define ONELIGHT_GAME_H

#include <iostream>

#include "FluxRoot.hpp"

class Game
{
    public:
        Game();
        ~Game();

        Flux::Root* getRoot();

        void initialise();
        void tick();
        bool isAlive();
        void handleInput();

    private:
        Flux::Root *root;
        bool alive = true;
        SDL_Event event;
};

#endif

