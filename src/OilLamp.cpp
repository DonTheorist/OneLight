#include "OilLamp.hpp"

OilLamp::OilLamp(std::shared_ptr<Player> player, Flux::Root *root)
    :player(player), root(root)
{
    ring = std::make_shared<Ring>(player, root);

    light = std::make_shared<Flux::PointLight>(Flux::Vector3(0.0f, 0.0f, -3.0f), Flux::Colour(1.0f, 0.93f, 0.68f), 0.0f, 2.0f, 2.0f);
    this->root->addToScene(light);
}

OilLamp::~OilLamp()
{ }

void OilLamp::update()
{
    if(lightIncreasePercentage != 0.0f)
    {
        //impose min/max ring size
        if((lightIncreasePercentage < 0.0f && ring->getSprite()->getWidth() > 0.1f) || (lightIncreasePercentage > 0.0f && ring->getSprite()->getWidth() < 1280.0f))
        {
            ring->increaseDiamater(lightIncreasePercentage);
            Flux::Vector3 att = light->getAttenuationAsVector3();
            float q = att.z + lightIncreasePercentage * -2.0f;
            q = (q < 0.0f) ? 0.0f : q;
            light->setQuadraticAttenuation(q);
        }
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

