//
// Created by raph on 10/23/15.
//

#include "Arrow.h"
#include "Core.h"

Arrow::Arrow(const sf::Vector2f &pos, const sf::Vector2f &speed, float timeStamp) : mPos(pos), mSpeed(speed),
                                                                                       mTimeStamp(timeStamp)
{

}

bool Arrow::update(float delta_s)
{
    //mSpeed += Core::get().currentState()->;
    mPos += mSpeed*delta_s;
    return true;
}

void Arrow::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}
