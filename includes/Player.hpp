#ifndef ONELIGHT_PLAYER_H
#define ONELIGHT_PLAYER_H

#include "Entity.hpp"
#include "FluxRoot.hpp"
#include "FluxColourMaterial.hpp"

class Player : public Entity
{
    public:
        Player(Flux::Root *root);
        virtual ~Player();

        virtual void update();
        virtual void setPosition(const Flux::Vector2 &position);

        void collideWithBlock(const Flux::Rectangle2D &aabb);

};

#endif

