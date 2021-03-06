#ifndef ONELIGHT_ENTITY_H
#define ONELIGHT_ENTITY_H

#include "FluxSprite.hpp"
#include "FluxSpriteBatch.hpp"

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        Flux::Vector2 getPosition();
        virtual void setPosition(const Flux::Vector2 &position);
        std::shared_ptr<Flux::Sprite> getSprite();

        Flux::Vector2 getVelocity();
        void setVelocity(const Flux::Vector2 &velocity);
        float getSpeed();
        void setSpeed(const float speed);

        virtual void update();

        Flux::Rectangle2D getAABB();

    protected:
        std::shared_ptr<Flux::Sprite> sprite;
        std::shared_ptr<Flux::SpriteBatch> sb;
        Flux::Vector2 velocity;
        Flux::Rectangle2D aabb;
        float speed;
};

#endif

