#include "CrossFadeTransition.h"
#include "Core.h"
#include <cmath>

using namespace std;

CrossFadeTransition::CrossFadeTransition(float duration) : mDuration(duration)
{
    mStart = Core::get().time();
    mScreen.resize(6);
    sf::Vector2u size = Core::get().renderWindow().getSize(); //Create screen size plane
    mScreen.setPrimitiveType(sf::Triangles);
    mScreen[0] = sf::Vertex({0,0},{0,size.y});
    mScreen[1] = sf::Vertex({0,size.y},{0,0});
    mScreen[2] = sf::Vertex({size.x,0},{size.x,size.y});
    mScreen[3] = sf::Vertex({size.x,0},{size.x,size.y});
    mScreen[4] = sf::Vertex({0,size.y},{0,0});
    mScreen[5] = sf::Vertex({size.x,size.y},{size.x,0});
}

void CrossFadeTransition::render(sf::RenderTarget& target, const sf::Texture& first, const sf::Texture& second) const
{
    setScreenColor(sf::Color(255,255,255,mTargetAlpha));
    target.draw(mScreen,sf::RenderStates(&first));
    setScreenColor(sf::Color(255,255,255,255-mTargetAlpha));
    target.draw(mScreen,sf::RenderStates(&second));
}

void CrossFadeTransition::setScreenColor(sf::Color c) const
{
    for(size_t i = 0; i < 6; i++)
        mScreen[i].color = c;
}

Transition::State CrossFadeTransition::update()
{
    float time = Core::get().time();
    if(mStart+mDuration > time) {
        mTargetAlpha = max(0,min(255,int((1-(time-mStart)/mDuration)*255)));
        return SECOND;
    }
    else
        return END;
}
