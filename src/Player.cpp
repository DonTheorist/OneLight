#include "Player.hpp"

Player::Player(Flux::Root *root)
{
    auto mat = std::make_shared<Flux::ColourMaterial>();
    sb = std::make_shared<Flux::SpriteBatch>(mat);

    aabb = Flux::Rectangle2D(0.0f, 0.f, 20.0f, 20.0f);
    sprite = std::make_shared<Flux::Sprite>(aabb, Flux::Colour::WHITE);
    sb->addSprite(sprite);

    root->addToScene(sb);

    speed = 4.0f;
}

Player::~Player()
{ }

void Player::update()
{
    sprite->translate(velocity);
    aabb.position += velocity;

    Flux::Vector2 p = sprite->getPosition();
    if(p.x < 0.0f)
    {
        p.x = 0.0f;
        setPosition(p);
    }
    if(p.y < 0.0f)
    {
        p.y = 0.0f;
        setPosition(p);
    }
    if(p.x > 1004.0f)
    {
        p.x = 1004.0f;
        setPosition(p);
    }
    if(p.y > 700.0f)
    {
        p.y = 700.0f;
        setPosition(p);
    }
}

void Player::setPosition(const Flux::Vector2 &position)
{
    sprite->setPosition(position);
    aabb.position = position;
}

void Player::collideWithBlock(const Flux::Rectangle2D &aabb)
{
    float hwA = this->aabb.width / 2.0f;
    float hhA = this->aabb.height / 2.0f;
    float hwB = aabb.width / 2.0f;
    float hhB = aabb.height / 2.0f;

    Flux::Vector2 centreA = this->aabb.position + Flux::Vector2(hwA, hhA);
    Flux::Vector2 centreB = aabb.position + Flux::Vector2(hwB, hhB);

    float dx = centreA.x - centreB.x;
    float dy = centreA.y - centreB.y;

    float x = dx < 0.0f ? aabb.position.x - (this->aabb.position.x + this->aabb.width) : (aabb.position.x + aabb.width) - this->aabb.position.x;
    float y = dy < 0.0f ? aabb.position.y - (this->aabb.position.y + this->aabb.height) : (aabb.position.y + aabb.height) - this->aabb.position.y;

    Flux::Vector2 translate = (fabs(x) < fabs(y)) ? Flux::Vector2(x, 0.0f) : Flux::Vector2(0.0f, y);

    sprite->translate(translate);
    this->aabb.position += translate;
}

