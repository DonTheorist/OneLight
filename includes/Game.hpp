#ifndef ONELIGHT_GAME_H
#define ONELIGHT_GAME_H

#include <iostream>
#include <math.h>

#include "FluxRoot.hpp"
#include "FluxNormalMaterial.hpp"

class Player;
class OilLamp;

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

        std::shared_ptr<Player> player;
        std::shared_ptr<OilLamp> lamp;
        std::shared_ptr<Flux::SpriteBatch> groundSB;
        std::shared_ptr<Flux::Sprite> ground;

        bool keyA = false;
        bool keyD = false;
        bool keyW = false;
        bool keyS = false;
        Flux::Vector2 tmpVelocity = Flux::Vector2::ZERO;

        std::shared_ptr<Flux::PointLight> light;
};

#endif

