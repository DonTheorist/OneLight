#include "Game.hpp"
#include "Block.hpp"
#include "LevelManager.hpp"

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

