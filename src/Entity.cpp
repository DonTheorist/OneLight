#include "Entity.hpp"

Entity::Entity()
{ }

Entity::~Entity()
{ }

Flux::Vector2 Entity::getPosition()
{
    return sprite->getPosition();
}

void Entity::setPosition(const Flux::Vector2 &position)
{
    sprite->setPosition(position);
}

std::shared_ptr<Flux::Sprite> Entity::getSprite()
{
    return sprite;
}

Flux::Vector2 Entity::getVelocity()
{
    return velocity;
}

void Entity::setVelocity(const Flux::Vector2 &velocity)
{
    this->velocity = velocity;
}

float Entity::getSpeed()
{
    return speed;
}

void Entity::setSpeed(const float speed)
{
    this->speed = speed;
}

void Entity::update()
{ }

