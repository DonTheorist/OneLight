#ifndef ONELIGHT_BLOCK_H
#define ONELIGHT_BLOCK_H

#include "Entity.hpp"

class Block : public Entity
{
    public:
        Block(const Flux::Rectangle2D &rectangle, std::shared_ptr<Flux::SpriteBatch> sb);
        virtual ~Block();

};

#endif

