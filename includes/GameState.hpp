#ifndef ONELIGHT_GAMESTATE_H
#define ONELIGHT_GAMESTATE_H

#include "State.hpp"

class Player;
class OilLamp;
class LevelManager;

class GameState : public State
{
    public:
        GameState(Game *game);
        virtual ~GameState();

        virtual void initialise();
        virtual void unload();
        virtual void update();
        virtual void handleInput();
        virtual void onResume();

    private:
        std::shared_ptr<Player> player;
        std::shared_ptr<OilLamp> lamp;
        std::shared_ptr<LevelManager> levelManager;

        std::shared_ptr<Flux::SpriteBatch> groundSB;
        std::shared_ptr<Flux::Sprite> ground;

        bool keyA = false;
        bool keyD = false;
        bool keyW = false;
        bool keyS = false;
        Flux::Vector2 tmpVelocity = Flux::Vector2::ZERO;
};

#endif

