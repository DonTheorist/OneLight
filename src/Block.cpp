#include "Block.hpp"

Block::Block(const Flux::Rectangle2D &rectangle, std::shared_ptr<Flux::SpriteBatch> sb)
{
    auto mat = std::make_shared<Flux::ColourMaterial>();
    this->sb = sb;
    Flux::Colour c(0.37f, 0.24f, 0.09f, 1.0f);
    sprite = std::make_shared<Flux::Sprite>(rectangle, c);
    sb->addSprite(sprite);

    sprite->setDepth(-0.5f);

    aabb = rectangle;
}

Block::~Block()
{ }

