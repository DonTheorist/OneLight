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

        float lightIncreaseRate = 0.05f;
        float lightIncreasePercentage = 0.0f;
};

#endif

