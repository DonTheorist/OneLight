#include "Ring.hpp"
#include "Player.hpp"

Ring::Ring(std::shared_ptr<Player> player, Flux::Root *root)
    : player(player), root(root), oldPosition(player->getPosition())
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

    diameter = 256.0f;

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

    float fluctuate = sin(root->getElapsedSeconds() * 12.0f) * 0.6f;
    setDiameter(fluctuate + diameter);
}

void Ring::setDiameter(const float diameter)
{
    //assume diameter is length of image (not actual circle diameter)
    float w = sprite->getWidth();
    float d = (w - diameter) / 2.0f;

    sprite->setRectangle(Flux::Rectangle2D(sprite->getPosition() + Flux::Vector2(d, d), diameter, diameter));

    Flux::Vector2 p = sprite->getPosition();

    sides[0]->setRectangle(Flux::Rectangle2D(p.x - 1280.0f, p.y, 1280.0f, diameter));
    sides[1]->setRectangle(Flux::Rectangle2D(p.x - 1280.0f, p.y + diameter, 4560.0f, 720.0f));
    sides[2]->setRectangle(Flux::Rectangle2D(p.x + diameter, p.y, 1280.0f, diameter));
    sides[3]->setRectangle(Flux::Rectangle2D(p.x - 1280.0f, p.y - 720.0f, 4560.0f, 720.0f));

    this->diameter = diameter;
}

void Ring::increaseDiamater(const float percentage)
{
    float scale = (percentage < 0.0f) ? 1.0f - fabs(percentage) : 1.0f + percentage;
    float w = sprite->getWidth();

    setDiameter(w * scale);
}

