#ifndef ONELIGHT_KEY_H
#define ONELIGHT_KEY_H

#include "Entity.hpp"

class Key : public Entity
{
    public:
        Key(const Flux::Rectangle2D &rectangle, std::shared_ptr<Flux::SpriteBatch> sb);
        virtual ~Key();
};

#endif

