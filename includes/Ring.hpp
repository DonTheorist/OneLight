#ifndef ONELIGHT_RING_H
#define ONELIGHT_RING_H

#include <vector>

#include "Entity.hpp"
#include "FluxRoot.hpp"

class Player;

class Ring : public Entity
{
    public:
        Ring(std::shared_ptr<Player> person, Flux::Root *root);
        virtual ~Ring();

        virtual void update();

    private:
        std::shared_ptr<Player> player;
        std::shared_ptr<Flux::SpriteBatch> blackoutSB;
        std::vector<std::shared_ptr<Flux::Sprite>> sides;

        Flux::Vector2 oldPosition;
};

#endif

