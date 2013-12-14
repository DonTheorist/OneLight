#include "Player.hpp"

Player::Player(Flux::Root *root)
{
    auto mat = std::make_shared<Flux::ColourMaterial>();
    sb = std::make_shared<Flux::SpriteBatch>(mat);

    sprite = std::make_shared<Flux::Sprite>(Flux::Rectangle2D(0.0f, 0.0f, 20.0f, 20.0f), Flux::Colour::WHITE);
    sb->addSprite(sprite);

    root->addToScene(sb);

    speed = 5.0f;
}

Player::~Player()
{ }

void Player::update()
{
    sprite->translate(velocity);
}

