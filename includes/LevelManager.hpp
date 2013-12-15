#ifndef ONELIGHT_LEVELMANAGER_H
#define ONELIGHT_LEVELMANAGER_H

#include <vector>
#include "FluxRoot.hpp"

class Block;
class Player;
class Key;
class OilLamp;

struct Level
{
    std::vector<Flux::Rectangle2D> blocks;
    std::vector<Flux::Vector2> keys;
    Flux::Rectangle2D exit;
    Flux::Vector2 start;
};

class LevelManager
{
    public:
        LevelManager(std::shared_ptr<Player> player, Flux::Root *root);
        ~LevelManager();

        void update();
        void unloadLevel();
        void loadLevel(const int level);
        void reset();

        int getCurrentLevel();
        bool isCompleted();
        bool isExitUnlocked();

        void setOilLamp(std::shared_ptr<OilLamp> lamp);

    private:
        std::shared_ptr<Player> player;
        std::shared_ptr<OilLamp> lamp;
        std::shared_ptr<Flux::SpriteBatch> blockSB;
        std::vector<std::shared_ptr<Block>> blocks;
        std::shared_ptr<Flux::SpriteBatch> keySB;
        std::vector<std::shared_ptr<Key>> keys;
        std::vector<Level*> levels;
        std::shared_ptr<Flux::Sprite> exit;

        int currentLevel = 0;
        bool completed = false;

        void extractValues(std::string str, float *vals);

};

#endif

