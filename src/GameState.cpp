#include "GameState.h"

GameState::GameState() : mVisible(true)
{

}

void GameState::setChild(SharedState state)
{
    mChild = state;
}

SharedState GameState::child()
{
    return mChild;
}

void GameState::drawAll(sf::RenderTarget &target)
{
    if(mChild)
        mChild->drawAll(target);
    draw(target);
}
