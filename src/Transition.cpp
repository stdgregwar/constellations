#include "../include/Transition.h"

Transition::Transition()
{

}
void Transition::setTexture(sf::Texture* tex)
{
    mTexture = tex;
}

const sf::Texture* Transition::tRender() const
{
    return mTexture;
}

