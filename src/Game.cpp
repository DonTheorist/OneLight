#include "Game.hpp"
#include "Block.hpp"
#include "LevelManager.hpp"
#include "IntroState.hpp"
#include "GameState.hpp"
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
    setupInitialStates();
}

void Game::tick()
{
    if(restart)
    {
        while(states.size() != 1)
        {
            states.top()->unload();
            delete states.top();
            states.pop();
        }

        dynamic_cast<GameState*>(states.top())->reset();

        setupInitialStates();

        restart = false;
        return;
    }

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

void Game::setRestart(const bool restart)
{
    this->restart = restart;
}

void Game::setupInitialStates()
{
    if(states.size() == 0)
    {
        GameState *gameState = new GameState(this);
        gameState->initialise();
        states.push(gameState);
    }

    IntroState *introState = new IntroState(this, endText);
    introState->initialise();
    states.push(introState);
}

void Game::setEndText(const std::string &endText)
{
    this->endText = endText;
}

