#include "Game.hpp"
#include "Player.hpp"
#include "OilLamp.hpp"
#include "Block.hpp"

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



    auto blockMat = std::make_shared<Flux::ColourMaterial>();
    blockSB = std::make_shared<Flux::SpriteBatch>(blockMat);
    root->addToScene(blockSB);

    auto block1 = std::make_shared<Block>(Flux::Rectangle2D(200.0f, 200.f, 200.0f, 200.0f), blockSB);
    auto block2 = std::make_shared<Block>(Flux::Rectangle2D(600.0f, 300.f, 100.0f, 500.0f), blockSB);

    blocks.push_back(block1);
    blocks.push_back(block2);

    lamp = std::make_shared<OilLamp>(player, root);

}

void Game::tick()
{
    handleInput();

    player->setVelocity(Flux::Vector2::normalise(tmpVelocity) * player->getSpeed());
    player->update();
    lamp->update();

    for(auto b : blocks)
    {
        if(b->getAABB().intersect(player->getAABB()))
        {
            player->collideWithBlock(b->getAABB());
            break;
        }
    }

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

