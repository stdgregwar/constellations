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
    if(mVisible)
        draw(target);
}

void GameState::setVisible(bool b)
{
    mVisible = b;
}

bool GameState::isVisible()
{
    return mVisible;
}
