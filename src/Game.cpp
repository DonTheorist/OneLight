#include "Game.hpp"
#include "Block.hpp"
#include "LevelManager.hpp"
#include "PreviewState.hpp"

Game::Game()
    : root(new Flux::Root())
{ }

Game::~Game()
{
    while(!states.empty())
    {
        delete states.top();
        states.pop();
    }

    delete root;
}

void Game::initialise()
{
    root->initialise();

    GameState *gameState = new GameState(this);
    gameState->initialise();
    states.push(gameState);
}

void Game::tick()
{
    if(states.top()->needToKill())
    {
        if(states.size() == 1)
        {
            alive = false;
            return;
        }
        states.top()->unload();
        delete states.top();
        states.pop();

        states.top()->onResume();
    }
    states.top()->update();

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

void Game::setAlive(const bool alive)
{
    this->alive = alive;
}

State* Game::getCurrentState()
{
    return states.top();
}

void Game::pushState(State *state)
{
    states.push(state);
}

