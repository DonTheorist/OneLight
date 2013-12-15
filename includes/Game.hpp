#ifndef ONELIGHT_GAME_H
#define ONELIGHT_GAME_H

#include <iostream>
#include <stack>
#include <vector>
#include <math.h>

#include "FluxRoot.hpp"
#include "FluxNormalMaterial.hpp"

class State;

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

        void setRestart(const bool restart);

        void setEndText(const std::string &endText);

    private:
        Flux::Root *root;
        bool alive = true;
        bool restart = false;

        std::stack<State*> states;

        void setupInitialStates();
        std::string endText = " ";

};

#endif

