#include "State.hpp"

State::State(Game *game)
    : game(game)
{ }

State::~State()
{ }

bool State::needToKill()
{
    return kill;
}

