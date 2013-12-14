#include "Game.hpp"
#include "Player.hpp"
#include "Ring.hpp"

Game::Game()
    : root(new Flux::Root())
{ }

Game::~Game()
{
    delete root;
}

void Game::initialise()
{
    root->initialise();

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

    light = std::make_shared<Flux::PointLight>(Flux::Vector3(0.0f, 0.0f, -3.0f), Flux::Colour(1.0f, 0.93f, 0.68f), 0.0f, 2.0f, 2.0f);
    root->addToScene(light);

    ring = std::make_shared<Ring>(player, root);
    //ring->setDiameter(512.0f);
}

void Game::tick()
{
    handleInput();

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
    player->setVelocity(Flux::Vector2::normalise(tmpVelocity) * player->getSpeed());
    player->update();
    ring->update();
    root->renderFrame();
}

Flux::Root* Game::getRoot()
{
    return root;
}

bool Game::isAlive()
{
    return alive;
}

void Game::handleInput()
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
                        alive = false;
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
                        lightIncreasePercentage = -lightIncreaseRate;
                        break;
                    }
                    case SDLK_e :
                    {
                        lightIncreasePercentage = lightIncreaseRate;
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
                        lightIncreasePercentage = 0.0f;
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

