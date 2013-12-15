#include "OilLamp.hpp"

OilLamp::OilLamp(std::shared_ptr<Player> player, Flux::Root *root)
    :player(player), root(root)
{
    ring = std::make_shared<Ring>(player, root);

    light = std::make_shared<Flux::PointLight>(Flux::Vector3(0.0f, 0.0f, -3.0f), Flux::Colour(1.0f, 0.93f, 0.68f), 0.0f, 2.0f, 2.0f);
    this->root->addToScene(light);

    auto mat = std::make_shared<Flux::ColourMaterial>();
    barSB = std::make_shared<Flux::SpriteBatch>(mat);
    barSprite = std::make_shared<Flux::Sprite>(Flux::Rectangle2D(1100.0f, 20.0f, 150.0f, 680.0f), Flux::Colour::AZURE);

    barSB->addSprite(barSprite);
    root->addToScene(barSB);

    oilTimer.reset();
}

OilLamp::~OilLamp()
{ }

void OilLamp::update()
{
    if(lightIncreasePercentage != 0.0f)
    {
        //impose min/max ring size
        float d = ring->getDiameter();
        if((lightIncreasePercentage < 0.0f && d > 0.1f) || (lightIncreasePercentage > 0.0f && d < 1280.0f))
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
        oilDeplete = 0.1f * (ring->getDiameter() / 256.0f);
        oil -= oilDeplete;
        barSprite->setRectangle(Flux::Rectangle2D(barSprite->getPosition(), 150.0f, 680.0f * (oil / 100.0f)));
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
    ring->setDiameter(256.0f);
}

void OilLamp::setRingVisible(const bool visible)
{
    float depth = (visible) ? 0.0f : 100.0f;
    ring->setDepth(depth);
}

