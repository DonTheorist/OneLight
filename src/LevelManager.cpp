#include "LevelManager.hpp"

#include "Block.hpp"
#include "Player.hpp"

LevelManager::LevelManager(std::shared_ptr<Player> player, Flux::Root *root)
    : player(player)
{
    auto blockMat = std::make_shared<Flux::ColourMaterial>();
    blockSB = std::make_shared<Flux::SpriteBatch>(blockMat);
    root->addToScene(blockSB);

    std::ifstream f;
    f.open("assets/levels.xml");
    std::stringstream strm;

    if(f.is_open())
    {
        while(!f.eof())
        {
            std::string tmp;
            std::getline(f, tmp);
            strm << tmp;
        }
    }

    rapidxml::xml_document<> doc;
    doc.parse<0>((char*)strm.str().c_str());

    rapidxml::xml_node<> *node = doc.first_node("levels");
    rapidxml::xml_node<> *child;

    for(child = node->first_node("level"); child; child = child->next_sibling())
    {
        Level *level = new Level();
        rapidxml::xml_node<> *blockChild;

        for(blockChild = child->first_node("block"); blockChild; blockChild = blockChild->next_sibling("block"))
        {
            float blockVals[4] = { 0.0f };
            std::string blockRect = blockChild->value();

            extractValues(blockRect, blockVals);
            level->blocks.push_back(Flux::Rectangle2D(blockVals[0], blockVals[1], blockVals[2], blockVals[3]));
        }

        std::string exitRect = child->first_node("exit")->value();
        std::string startVec = child->first_node("start")->value();
        float exitVals[4] = { 0.0f };
        float startVals[2] = { 0.0f };

        extractValues(exitRect, exitVals);
        level->exit = Flux::Rectangle2D(exitVals[0], exitVals[1], exitVals[2], exitVals[3]);

        extractValues(startVec, startVals);
        level->start = Flux::Vector2(startVals[0], startVals[1]);

        levels.push_back(level);
    }
}

LevelManager::~LevelManager()
{
   for(auto l : levels)
      delete l; 
}

void LevelManager::reset()
{
    currentLevel = 0;
    completed = false;
}

void LevelManager::extractValues(std::string str, float *vals)
{
    int index = 0;
    std::stringstream strm;

    for(int i = 0; i <= (int)str.length(); i++)
    {
        char c = str[i];

        if(c != ' ' && i != (int)str.length())
            strm << c;
        else
        {
            vals[index++] = atof(strm.str().c_str());
            strm = std::stringstream();
        }
    }
}

void LevelManager::update()
{
    for(auto b : blocks)
    {
        if(b->getAABB().intersect(player->getAABB()))
        {
            player->collideWithBlock(b->getAABB());
            break;
        }
    }

    if(currentLevel != (int)levels.size() - 1 && player->getAABB().intersect(levels[currentLevel]->exit))
        loadLevel(++currentLevel);
}

void LevelManager::unloadLevel()
{
    blockSB->clear();
    blocks.clear();
}

void LevelManager::loadLevel(const int level)
{
    unloadLevel();

    for(auto b : levels[level]->blocks)
    {
        auto block1 = std::make_shared<Block>(b, blockSB);
        blocks.push_back(block1);
    }

    auto exit = std::make_shared<Flux::Sprite>(levels[level]->exit, Flux::Colour::BLUE);
    blockSB->addSprite(exit);

    player->setPosition(levels[level]->start);

    currentLevel = level;
}

int LevelManager::getCurrentLevel()
{
    return currentLevel;
}

bool LevelManager::isCompleted()
{
    return completed;
}


