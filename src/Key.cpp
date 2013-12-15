#include "Key.hpp"

Key::Key(const Flux::Rectangle2D &rectangle, std::shared_ptr<Flux::SpriteBatch> sb)
{
    auto mat = std::make_shared<Flux::ColourMaterial>();
    this->sb = sb;
    Flux::Colour c = Flux::Colour::PALEGREEN;
    sprite = std::make_shared<Flux::Sprite>(rectangle, c);

    sb->addSprite(sprite);

    sprite->setDepth(-0.5f);

    aabb = rectangle;

}

Key::~Key()
{ }

