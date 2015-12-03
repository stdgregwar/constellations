#include "CrossFadeTransition.h"
#include "Core.h"
#include <cmath>

using namespace std;

CrossFadeTransition::CrossFadeTransition(float duration) : mDuration(duration), mState(Transition::FIRST)
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

void CrossFadeTransition::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(target.getDefaultView());
    target.draw(mScreen);
}

void CrossFadeTransition::setScreenColor(sf::Color c) const
{
    for(size_t i = 0; i < 6; i++)
        mScreen[i].color = c;
}

Transition::State CrossFadeTransition::update()
{
    float time = Core::get().time();

    switch(mState)
    {
        case FIRST:
        if(mStart+mDuration/2 > time) {
            mTargetAlpha = max(0,min(255,int(((time-mStart)*2/mDuration)*255)));
            setScreenColor(sf::Color(0,0,0,mTargetAlpha));
        }
        else{
            mState = SECOND;
            mStart = time;
        }
        break;
        case SECOND:
        if(mStart+mDuration/2 > time) {
            mTargetAlpha = max(0,min(255,int((1-(time-mStart)*2/mDuration)*255)));
            setScreenColor(sf::Color(0,0,0,mTargetAlpha));
        }
        else
            mState = END;
        break;
        case END:
        break;
    }

    return mState;
}
