#include "Ring.hpp"
#include "Player.hpp"

Ring::Ring(std::shared_ptr<Player> player, Flux::Root *root)
    : player(player), oldPosition(player->getPosition())
{
    auto ringTexture = root->getTextureManager()->loadTexture("assets/ring.png");
    auto ringMat = std::make_shared<Flux::TextureMaterial>(ringTexture);
    sb = std::make_shared<Flux::SpriteBatch>(ringMat);
    sprite = std::make_shared<Flux::Sprite>(Flux::Rectangle2D(-118.0f, -118.0f, 256.0f, 256.0f), Flux::Colour::WHITE, Flux::Rectangle2D(0.0f, 0.0f, 256.0f, 256.0f));
    sb->addSprite(sprite);

    auto blackoutMat = std::make_shared<Flux::ColourMaterial>();
    blackoutSB = std::make_shared<Flux::SpriteBatch>(blackoutMat);

    sides.push_back(std::make_shared<Flux::Sprite>(Flux::Rectangle2D(-1398.0f, -118.0f, 1280.0f, 256.0f), Flux::Colour::BLACK));
    sides.push_back(std::make_shared<Flux::Sprite>(Flux::Rectangle2D(-1398.0f, 128.0f, 2560.0f, 720.0f), Flux::Colour::BLACK));
    sides.push_back(std::make_shared<Flux::Sprite>(Flux::Rectangle2D(136.0f, -118.0f, 1280.0f, 256.0f), Flux::Colour::BLACK));
    sides.push_back(std::make_shared<Flux::Sprite>(Flux::Rectangle2D(-1398.0f, -838.0f, 2560.0f, 720.0f), Flux::Colour::BLACK));

    for(auto &s : sides)
        blackoutSB->addSprite(s);

    root->addToScene(sb);
    root->addToScene(blackoutSB);
}

Ring::~Ring()
{ }

void Ring::update()
{
    Flux::Vector2 delta = player->getPosition() - oldPosition;
    sprite->translate(delta);

    for(auto &s : sides)
        s->translate(delta);

    oldPosition = player->getPosition();
}

