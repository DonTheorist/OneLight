#include "GameState.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "OilLamp.hpp"
#include "LevelManager.hpp"
#include "PreviewState.hpp"

GameState::GameState(Game *game)
    : State(game)
{ }

GameState::~GameState()
{ }

void GameState::initialise()
{
    Flux::Root *root = game->getRoot();

    player = std::make_shared<Player>(root);

    auto texture = root->getTextureManager()->loadTexture("assets/ground.png");
    auto normal = root->getTextureManager()->loadTexture("assets/groundNormal.png");
    auto mat = std::make_shared<Flux::NormalMaterial>(texture, normal);
    groundSB = std::make_shared<Flux::SpriteBatch>(mat);
    groundSB->setLightEnabled(true);

    ground = std::make_shared<Flux::Sprite>(Flux::Rectangle2D(0.0f, 0.0f, 1024.0f, 1024.0f), Flux::Colour::WHITE, Flux::Rectangle2D(0.0f, 0.0f, 1024.0f, 1024.0f), Flux::Rectangle2D(0.0f, 0.0f, 1024.0f, 1024.0f));
    groundSB->addSprite(ground);
    ground->setDepth(-1.0f);
    root->addToScene(groundSB);

    levelManager = std::make_shared<LevelManager>(player, root);
    levelManager->loadLevel(0);

    lamp = std::make_shared<OilLamp>(player, root);
    lamp->setRingVisible(false);
}

void GameState::unload()
{ }

void GameState::update()
{
    if(currentLevel != levelManager->getCurrentLevel())
    {
        currentLevel = levelManager->getCurrentLevel();
        lamp->setRingVisible(false);

        PreviewState *previewState = new PreviewState(game);
        previewState->initialise();
        game->pushState(previewState);
        return;
    }

    handleInput();

    player->setVelocity(Flux::Vector2::normalise(tmpVelocity) * player->getSpeed());
    player->update();

    levelManager->update();
    lamp->update();
}

void GameState::onResume()
{
    lamp->setRingVisible(true);
    lamp->resetRingDiameter();

    keyA = keyD = keyS = keyW = false;
    tmpVelocity = Flux::Vector2::ZERO;
}

void GameState::handleInput()
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
                    case SDLK_a :
                    {
                        tmpVelocity.x = -1.0f;
                        keyA = true;
                        break;
                    }
                    case SDLK_d :
                    {
                        tmpVelocity.x = 1.0f;
                        keyD = true;
                        break;
                    }
                    case SDLK_w :
                    {
                        tmpVelocity.y = 1.0f;
                        keyW = true;
                        break;
                    }
                    case SDLK_s :
                    {
                        tmpVelocity.y = -1.0f;
                        break;
                    }
                    case SDLK_q :
                    {
                        //lightIncreasePercentage = -lightIncreaseRate;
                        lamp->decreaseLightPercentgae();
                        break;
                    }
                    case SDLK_e :
                    {
                        lamp->increaseLightPercentage();
                        //lightIncreasePercentage = lightIncreaseRate;
                        break;
                    }
                    default : break;
                }
                break;
            }
            case SDL_KEYUP :
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_a :
                    {
                        keyA = false;
                        if(!keyD)
                            tmpVelocity.x = 0.0f;
                        else
                            tmpVelocity.x = 1.0f;
                        break;
                    }
                    case SDLK_d :
                    {
                        keyD = false;
                        if(!keyA)
                            tmpVelocity.x = 0.0f;
                        else
                            tmpVelocity.x = -1.0f;
                        break;
                    }
                    case SDLK_w :
                    {
                        keyW = false;
                        if(!keyS)
                            tmpVelocity.y = 0.0f;
                        else
                            tmpVelocity.y = -1.0f;
                        break;
                    }
                    case SDLK_s :
                    {
                        keyS = false;
                        if(!keyW)
                            tmpVelocity.y = 0.0f;
                        else
                            tmpVelocity.y = 1.0f;
                        break;
                    }
                    case SDLK_q : case SDLK_e :
                    {
                        lamp->resetLightPercentage();
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

