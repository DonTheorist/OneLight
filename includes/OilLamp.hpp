#ifndef ONELIGHT_OILLAMP_H
#define ONELIGHT_OILLAMP_H

#include "FluxRoot.hpp"
#include "FluxPointLight.hpp"
#include "Ring.hpp"
#include "Player.hpp"

class OilLamp
{
    public:
        OilLamp(std::shared_ptr<Player> player, Flux::Root *root);
        ~OilLamp();

        void update();
        void increaseLightPercentage();
        void decreaseLightPercentgae();
        void resetLightPercentage();

    private:
        std::shared_ptr<Player> player;
        Flux::Root *root;
        std::shared_ptr<Ring> ring;
        std::shared_ptr<Flux::PointLight> light;

        std::shared_ptr<Flux::SpriteBatch> barSB;
        std::shared_ptr<Flux::Sprite> barSprite;

        float lightIncreaseRate = 0.05f;
        float lightIncreasePercentage = 0.0f;

        Flux::Timer oilTimer;
        float oil = 100.0f;
        float oilDeplete = 0.1f;
        float oilUpdateTime = 50.0f;
};

#endif

