//
// Created by raph on 10/23/15.
//

#include <StateConstellation.h>
#include "Arrow.h"
#include "Core.h"
#include "VecUtils.h"

Arrow::Arrow(const sf::Vector2f &pos, const sf::Vector2f &speed, float timeStamp) : mPos(pos), mSpeed(speed),
                                                                                       mTimeStamp(timeStamp)
{
}

bool Arrow::update(float delta_s)
{
    //TODO find which type cstate must be...
    auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
    mSpeed += cstate->getGravFieldAt(mPos)*delta_s;
    mPos += mSpeed*delta_s;
    return true;
}

void Arrow::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Vector2f normalizedSpeed = normalise(mSpeed) * 15.0f;
    sf::Vertex vertices[] =
            {
              sf::Vertex(mPos),
              sf::Vertex((mPos-normalizedSpeed))
            };
    target.draw(vertices,2,sf::Lines,states);
}


sf::Vector2f Arrow::getPos()
{
    return mPos;
}
