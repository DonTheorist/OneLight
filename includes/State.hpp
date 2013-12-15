#ifndef ONELIGHT_STATE_H
#define ONELIGHT_STATE_H

#include "FLuxRoot.hpp"

class Game;

class State
{
    public:
        State(Game *game);
        virtual ~State();

        virtual void initialise() = 0;
        virtual void unload() = 0;
        virtual void update() = 0;
        virtual void handleInput() = 0;
        virtual void onResume() = 0;

        bool needToKill();

    protected:
        Game *game;
        SDL_Event event;
        bool kill = false;
};


#endif

