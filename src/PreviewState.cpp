#include "PreviewState.hpp"
#include "Game.hpp"

PreviewState::PreviewState(Game *game)
    : State(game)
{ }

PreviewState::~PreviewState()
{ }

void PreviewState::initialise()
{
    auto mat = std::make_shared<Flux::ColourMaterial>();
    maskSB = std::make_shared<Flux::SpriteBatch>(mat);
    mask = std::make_shared<Flux::Sprite>(Flux::Rectangle2D(0.0f, 0.0f, 1024.0f, 1024.0f), Flux::Colour(0.0f, 0.0f, 0.0f, alpha));

    maskSB->addSprite(mask);

    game->getRoot()->addToScene(maskSB);

    timer.reset();
}

void PreviewState::unload()
{ }

void PreviewState::update()
{
    handleInput();
    if(timer.elapsedMilliSeconds() > deltaTime)
    {
        alpha += deltaAlpha;
        if(alpha > 1.0f)
            alpha = 1.0f;

        mask->setColour(Flux::Colour(0.0f, 0.0f, 0.0f, alpha));
        timer.reset();
    }
}

void PreviewState::handleInput()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN :
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE :
                    {
                        game->setAlive(false);
                        break;
                    }
                    default : break;
                }
                break;
            }
            default : break;
        }
    }
}

