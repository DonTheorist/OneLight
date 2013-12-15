#include "OilLamp.hpp"

#define DEFAULT_RING_SIZE 128.0f

OilLamp::OilLamp(std::shared_ptr<Player> player, Flux::Root *root)
    :player(player), root(root)
{
    ring = std::make_shared<Ring>(player, root);

    light = std::make_shared<Flux::PointLight>(Flux::Vector3(0.0f, 0.0f, -3.0f), Flux::Colour(1.0f, 0.93f, 0.68f), 0.0f, 2.0f, 2.0f);
    this->root->addToScene(light);

    auto tex = root->getTextureManager()->loadTexture("assets/lamp.png");
    auto texMat = std::make_shared<Flux::TextureMaterial>(tex);
    auto lampSB = std::make_shared<Flux::SpriteBatch>(texMat);
    auto lampSprite = std::make_shared<Flux::Sprite>(Flux::Rectangle2D(1024.0f, 0.0f, 256.0f, 720.0f), Flux::Colour::WHITE, Flux::Rectangle2D(0.0f, 0.0f, 459.0f, 1024.0f));

    lampSB->addSprite(lampSprite);
    lampSprite->setDepth(1.0f);
    root->addToScene(lampSB);

    auto mat = std::make_shared<Flux::ColourMaterial>();
    barSB = std::make_shared<Flux::SpriteBatch>(mat);

    Flux::Colour c = Flux::Colour::AZURE;
    c.a = 0.5f;

    barSprite = std::make_shared<Flux::Sprite>(Flux::Rectangle2D(1102.0f, 99.0f, 101.0f, 425.0f), c);

    barSB->addSprite(barSprite);
    barSprite->setDepth(2.0f);
    root->addToScene(barSB);

    oilTimer.reset();
}

OilLamp::~OilLamp()
{ }

void OilLamp::reset()
{
    oil = 100.0f;
    oilTimer.reset();
    barSprite->setRectangle(Flux::Rectangle2D(barSprite->getPosition(), 101.0f, 425.0f * (oil / 100.0f)));
    oilDeplete = 0.1f;
}

void OilLamp::update()
{
    if(lightIncreasePercentage != 0.0f)
    {
        //impose min/max ring size
        float d = ring->getDiameter();
        if((lightIncreasePercentage < 0.0f && d > 20.0f) || (lightIncreasePercentage > 0.0f && d < 1280.0f))
        {
            ring->increaseDiamater(lightIncreasePercentage);
            Flux::Vector3 att = light->getAttenuationAsVector3();
            float q = att.z + lightIncreasePercentage * -2.0f;
            q = (q < 0.0f) ? 0.0f : q;
            light->setQuadraticAttenuation(q);
        }
    }

    if(oilTimer.elapsedMilliSeconds() >= oilUpdateTime)
    {
        oilDeplete = 0.05f * (ring->getDiameter() / DEFAULT_RING_SIZE);
        oil -= oilDeplete;
        barSprite->setRectangle(Flux::Rectangle2D(barSprite->getPosition(), 101.0f, 425.0f * (oil / 100.0f)));
        oilTimer.reset();
    }

    float z = light->getPosition().z;
    light->setPosition(Flux::Vector3(player->getPosition(), z));

    ring->update(); 
}

void OilLamp::increaseLightPercentage()
{
    lightIncreasePercentage = lightIncreaseRate;
}

void OilLamp::decreaseLightPercentgae()
{
    lightIncreasePercentage = -lightIncreaseRate;
}

void OilLamp::resetLightPercentage()
{
    lightIncreasePercentage = 0.0f;
}

void OilLamp::resetRingDiameter()
{
    ring->setDiameter(DEFAULT_RING_SIZE);
}

void OilLamp::setRingVisible(const bool visible)
{
    float depth = (visible) ? 0.0f : 100.0f;
    ring->setDepth(depth);
}

bool OilLamp::isOilEmpty()
{
    return (oil <= 0.0f);
}

float OilLamp::getOil()
{
    return oil;
}

void OilLamp::removeOil(const float amount)
{
    oil -= amount;
}

void OilLamp::setLightColour(const Flux::Colour &colour)
{
    light->setColour(colour);
}

