#include "GameState.h"

GameState::GameState(SharedState parent) : mParent(parent)
{

}

void GameState::setChild(SharedState state)
{
    mChild = state;
}

void GameState::setParent(SharedState state)
{
    mParent = state;
}

SharedState GameState::parent()
{
    return mParent;
}

SharedState GameState::child()
{
    return mChild;
}
