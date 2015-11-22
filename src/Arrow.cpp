#include <StateConstellation.h>
#include "Arrow.h"
#include "Core.h"
#include "VecUtils.h"
#include "IntegrationUtils.h"
#include "MathUtils.h"

#include <iostream>
using namespace std;

Arrow::Arrow(const sf::Vector2f &pos, const sf::Vector2f &speed, const PlayerID& ownerID)
    : mPos(pos), mSpeed(speed), mTimeStamp(Core::get().time()), mOwnerID(ownerID),
      mPut(false), mCallback(nullptr), mCounter(sf::Color::Red,50)
{
    mTexture.loadFromFile("data/arrow.png");
    mSprite.setTexture(mTexture);
    mSprite.setOrigin(mTexture.getSize().x-6,mTexture.getSize().y/2);
    auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
    float s = cstate->zoomFactor();
    mCounter.setScale(s,s);
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
            onPut();
        }
        using namespace std::placeholders;
        integrateEC(mPos, mSpeed, delta_s, std::bind(&StateConstellation::getGravFieldAt, cstate.get(), _1));
        mSprite.setRotation(angle(mSpeed)*TO_DEGREES);

    }
    mSprite.setPosition(mPos);
    return true;
}

void Arrow::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
    mCounter.setValue(lifetime-Core::get().time()+mTimeStamp);
    sf::FloatRect bounds = mCounter.bounds();
    mCounter.setPosition(cstate->clampRect({mPos.x+bounds.left,mPos.y-bounds.top,bounds.width,bounds.height}));
    if(!(lastMoments() && !mPut && (int(ceilf(Core::get().time()*6.f))%2==0)))
    {
        target.draw(mSprite);
        if(lastMoments() && !mPut)
            target.draw(mCounter);
    }
}


const sf::Vector2f& Arrow::getPos()
{
    return mPos;
}

bool Arrow::lastMoments() const
{
    return Core::get().time() - mTimeStamp > lifetime-2;
}

bool Arrow::hasTimeOut() const
{
    if(Core::get().time() - mTimeStamp > lifetime && !mPut)
    {
        onTimeOut();
        return true;
    }
    return false;
}

void Arrow::onPut() const
{
    if(mCallback) mCallback();
}

void Arrow::onTimeOut() const
{
    if(mCallback) mCallback();
}

void Arrow::setCallback(std::function<void()> callback)
{
    mCallback = callback;
}
