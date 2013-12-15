#ifndef ONELIGHT_PREIVEWSTATE_H
#define ONELIGHT_PREVIEWSTATE_H

#include "State.hpp"

class PreviewState : public State
{
    public:
        PreviewState(Game *game);

        virtual ~PreviewState();

        virtual void initialise();
        virtual void unload();
        virtual void update();
        virtual void handleInput();

    private:
        std::shared_ptr<Flux::SpriteBatch> maskSB;
        std::shared_ptr<Flux::Sprite> mask;
        Flux::Timer timer;

        float deltaTime = 50.0f;
        float alpha = 0.0f;
        float deltaAlpha = 0.01f;
};

#endif

