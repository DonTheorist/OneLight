#ifndef ONELIGHT_INTROSTATE_H
#define ONELIGHT_INTOSTATE_H

#include "State.hpp"

class IntroState : public State
{
    public:
        IntroState(Game *game, const std::string customText = "");
        virtual ~IntroState();

        virtual void initialise();
        virtual void unload();
        virtual void update();
        virtual void handleInput();
        virtual void onResume();

    private:
        std::shared_ptr<Flux::SpriteBatch> backgroundSB;
        std::shared_ptr<Flux::Sprite> background;
        std::shared_ptr<Flux::SpriteBatch> instructionsSB;
        std::shared_ptr<Flux::Sprite> instructions;
        std::shared_ptr<Flux::PointLight> light;
        std::shared_ptr<Flux::TextDrawer> startTextDrawer;
        std::shared_ptr<Flux::TextDrawer> instructionsTextDrawer;
        std::shared_ptr<Flux::TextDrawer> customTextDrawer;

        Flux::Rectangle2D source;
        std::string customText;

        bool instructionsVisible = false;
};

#endif

