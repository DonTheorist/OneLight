#ifndef ONELIGHT_LEVELMANAGER_H
#define ONELIGHT_LEVELMANAGER_H

#include <vector>
#include "FluxRoot.hpp"

class Block;
class Player;

struct Level
{
    std::vector<Flux::Rectangle2D> blocks;
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

        int getCurrentLevel();

    private:
        std::shared_ptr<Player> player;
        std::shared_ptr<Flux::SpriteBatch> blockSB;
        std::vector<std::shared_ptr<Block>> blocks;
        std::vector<Level*> levels;

        int currentLevel = 0;

        void extractValues(std::string str, float *vals);

};

#endif

