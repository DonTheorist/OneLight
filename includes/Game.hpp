#ifndef ONELIGHT_GAME_H
#define ONELIGHT_GAME_H

#include <iostream>
#include <stack>
#include <vector>
#include <math.h>

#include "FluxRoot.hpp"
#include "FluxNormalMaterial.hpp"

#include "GameState.hpp"

class Game
{
    public:
        Game();
        ~Game();

        Flux::Root* getRoot();

        void initialise();
        void tick();
        bool isAlive();
        void setAlive(const bool alive);

        State* getCurrentState();
        void pushState(State *state);

    private:
        Flux::Root *root;
        bool alive = true;

        std::stack<State*> states;

};

#endif

