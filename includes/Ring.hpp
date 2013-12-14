#ifndef ONELIGHT_RING_H
#define ONELIGHT_RING_H

#include <vector>
#include <math.h>

#include "Entity.hpp"
#include "FluxRoot.hpp"

class Player;

class Ring : public Entity
{
    public:
        Ring(std::shared_ptr<Player> person, Flux::Root *root);
        virtual ~Ring();

        virtual void update();

        float getDiameter();
        void setDiameter(const float diameter);
        void increaseDiamater(const float percentage);

    private:
        std::shared_ptr<Player> player;
        Flux::Root *root;
        std::shared_ptr<Flux::SpriteBatch> blackoutSB;
        std::vector<std::shared_ptr<Flux::Sprite>> sides;

        Flux::Vector2 oldPosition;
        float diameter;
};

#endif


