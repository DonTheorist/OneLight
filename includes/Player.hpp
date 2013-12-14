#ifndef ONELIGHT_PLAYER_H
#define ONELIGHT_PLAYER_H

#include "Entity.hpp"
#include "FluxRoot.hpp"
#include "FluxColourMaterial.hpp"

class Player : public Entity
{
    public:
        Player(Flux::Root *root);
        ~Player();

        virtual void update();
};

#endif

