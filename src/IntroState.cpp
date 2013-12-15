#include "IntroState.hpp"
#include "Game.hpp"

IntroState::IntroState(Game *game, const std::string customText)
    : State(game), customText(customText)
{ }

IntroState::~IntroState()
{ }

void IntroState::initialise()
{
    auto texture = game->getRoot()->getTextureManager()->loadTexture("assets/ground.png");
    auto normal = game->getRoot()->getTextureManager()->loadTexture("assets/groundNormal.png");
    auto mat = std::make_shared<Flux::NormalMaterial>(texture, normal);
    backgroundSB = std::make_shared<Flux::SpriteBatch>(mat);

    source = Flux::Rectangle2D(0.0f, 0.0f, 2048.0f, 2048.0f);
    background = std::make_shared<Flux::Sprite>(Flux::Rectangle2D(0.0f, 0.0f, 2048.0f, 2048.0f), Flux::Colour::WHITE, source, source);

    backgroundSB->addSprite(background);
    backgroundSB->setLightEnabled(true);
    background->setDepth(4.0f);

    light = std::make_shared<Flux::PointLight>(Flux::Vector3(40.0f, 661.0f, 3.0f), Flux::Colour(1.0f, 0.93f, 0.68f), 0.0f, 2.0f, 2.0f);
    game->getRoot()->addToScene(light);

    game->getRoot()->addToScene(backgroundSB);

    auto fontTex = game->getRoot()->getTextureManager()->loadTexture("assets/font.png");
    startTextDrawer = std::make_shared<Flux::TextDrawer>(Flux::Vector2(520.0f, 360.0f), fontTex, "assets/font.xml");
    startTextDrawer->setString("Press (space) to start.");
    startTextDrawer->centreText(1280.0f);
    startTextDrawer->setDepth(4.5f);

    customTextDrawer = std::make_shared<Flux::TextDrawer>(Flux::Vector2(520.0f, 390.0f), fontTex, "assets/font.xml");
    customTextDrawer->setString(customText);
    customTextDrawer->centreText(1280.0f);
    customTextDrawer->setDepth(4.5f);

    instructionsTextDrawer = std::make_shared<Flux::TextDrawer>(Flux::Vector2(520.0f, 330.0f), fontTex, "assets/font.xml");
    instructionsTextDrawer->setString("Press (i) for instructions");
    instructionsTextDrawer->centreText(1280.0f);
    instructionsTextDrawer->setDepth(4.5f);

    auto insText = game->getRoot()->getTextureManager()->loadTexture("assets/instructions.png");
    auto insMat = std::make_shared<Flux::TextureMaterial>(insText);
    instructionsSB = std::make_shared<Flux::SpriteBatch>(insMat);
    instructions = std::make_shared<Flux::Sprite>(Flux::Rectangle2D(384.0f, 104.0f, 512.0f, 512.0f), Flux::Colour::WHITE, Flux::Rectangle2D(0.0f, 0.0f, 512.0f, 512.0f));
    instructionsSB->addSprite(instructions);
    instructions->setDepth(100.0f);

    game->getRoot()->addToScene(startTextDrawer);
    game->getRoot()->addToScene(customTextDrawer);
    game->getRoot()->addToScene(instructionsTextDrawer);
    game->getRoot()->addToScene(instructionsSB);
}

void IntroState::unload()
{ 
    game->getRoot()->removeFromScene(backgroundSB);
    game->getRoot()->removeFromScene(light);
    game->getRoot()->removeFromScene(startTextDrawer);
    game->getRoot()->removeFromScene(customTextDrawer);
    game->getRoot()->removeFromScene(instructionsTextDrawer);
    game->getRoot()->removeFromScene(instructionsSB);
}

void IntroState::update()
{
    handleInput();

    Flux::Vector3 centre(640.0f, 360.0f, 0.0f);
    Flux::Vector3 p = light->getPosition();
    p -= centre;
    p = Flux::Matrix4::makeRotateZ(-0.02f) * p;
    p += centre;

    light->setPosition(p);

    source.position.x += 1.0f;
    background->setTextureSource(source);
    background->setNormalSource(source);
}

void IntroState::onResume()
{ }

void IntroState::handleInput()
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
            case SDL_KEYUP :
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_SPACE :
                    {
                        kill = true;
                        break;
                    }
                    case SDLK_i :
                    {
                        instructionsVisible = !instructionsVisible;
                        if(instructionsVisible)
                        {
                            instructions->setDepth(4.0f);
                            startTextDrawer->setDepth(100.0f);
                            instructionsTextDrawer->setDepth(100.0f);
                            customTextDrawer->setDepth(100.0f);
                        }
                        else
                        {
                            std::cout << "Here" << std::endl;
                            instructions->setDepth(100.0f);
                            startTextDrawer->setDepth(4.5f);
                            instructionsTextDrawer->setDepth(4.5f);
                            customTextDrawer->setDepth(4.5f);
                        }
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

