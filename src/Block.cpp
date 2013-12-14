#include "Block.hpp"

Block::Block(const Flux::Rectangle2D &rectangle, std::shared_ptr<Flux::SpriteBatch> sb)
{
    auto mat = std::make_shared<Flux::ColourMaterial>();
    this->sb = sb;
    sprite = std::make_shared<Flux::Sprite>(rectangle, Flux::Colour::CRIMSON);
    sb->addSprite(sprite);

    sprite->setDepth(-0.5f);

    aabb = rectangle;
}

Block::~Block()
{ }

