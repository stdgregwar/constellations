//
// Created by raph on 10/23/15.
//

#include <StateConstellation.h>
#include "Arrow.h"
#include "Core.h"
#include "VecUtils.h"

#include <iostream>
using namespace std;

Arrow::Arrow(const sf::Vector2f &pos, const sf::Vector2f &speed, const PlayerID& ownerID)
    : mPos(pos), mSpeed(speed), mTimeStamp(Core::get().time()), mOwnerID(ownerID), mPut(false)
{
    mTexture.loadFromFile("data/arrow.png");
    mSprite.setTexture(mTexture);
    mSprite.setOrigin(mTexture.getSize().x-6,mTexture.getSize().y/2);
}

bool Arrow::update(float delta_s)
{
    //TODO Arrow follow planet in which putted
    if(mPlanet)
    {
        mPos = mPlanet->getPosOn(mPhi);
    }
    else
    {
        //TODO find which type cstate must be...
        auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
        SharedCharacter c = cstate->collideWithCharacter(mPos);
        if(c && c->id() != mOwnerID)
            c->hit(50);
        mPlanet = cstate->collideWithPlanet(mPos);
        if(mPlanet) {
            mSprite.setTextureRect({0,0,10,5});
            mPhi = angle(mPos-mPlanet->getPosition());
            mPut = true;
        }
        mSpeed += cstate->getGravFieldAt(mPos)*delta_s*1.f;
        mPos += mSpeed*delta_s;
        mSprite.setRotation(angle(mSpeed)*TO_DEGREES);

    }
    mSprite.setPosition(mPos);
    return true;
}

void Arrow::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite);
}


const sf::Vector2f& Arrow::getPos()
{
    return mPos;
}

bool Arrow::hasTimeOut() const
{
    return Core::get().time() - mTimeStamp > 15.f;
}

bool Arrow::isPut() const
{
    return mPut;
}

bool Arrow::isLastDead(PlayerID id,std::function<void()> callback)
{
    if((hasTimeOut() || isPut())&& id == mOwnerID)
    {
        callback();
        return true;
    }
    return false;
}