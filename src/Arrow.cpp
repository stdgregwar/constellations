#include <StateConstellation.h>
#include "Arrow.h"
#include "Core.h"
#include "VecUtils.h"
#include "IntegrationUtils.h"
#include "MathUtils.h"
#include "VecUtils.h"

#include <iostream>
using namespace std;
bool Arrow::mSelfhit = false;

Arrow::Arrow(const sf::Vector2f &pos, const sf::Vector2f &speed, const PlayerID& ownerID)
    : mPos(pos), mSpeed(speed), mTimeStamp(Core::get().time()), mOwnerID(ownerID),
      mPut(false), mCallback(nullptr), mCounter(sf::Color::Red,50), mTimeOut(false), mTrail(1.2,2,128)
{
    //Setup sounds
    mPutSound.setBuffer(*Core::get().soundBufferCache().get("data/arrowput.wav"));
    mSwiftSound.setBuffer(*Core::get().soundBufferCache().get("data/arrowswift2.wav"));
    mWarnSound.setBuffer(*Core::get().soundBufferCache().get("data/arrowwarn.wav"));
    mTouchSound.setBuffer(*Core::get().soundBufferCache().get("data/explodehigh.wav"));
    mThrowSound.setBuffer(*Core::get().soundBufferCache().get("data/arrowthrow.wav"));
    mDeathSound.setBuffer(*Core::get().soundBufferCache().get("data/arrowdeath.wav"));

    //Setup textures
    sf::Texture* sTex = Core::get().textureCache().get("data/arrow.png");
    mSprite.setTexture(*sTex);
    mSprite.setOrigin(sTex->getSize().x-6,sTex->getSize().y/2);
    sf::Texture* cTex = Core::get().textureCache().get("data/cursor.png");
    mCursor.setTexture(*cTex);
    mCursor.setOrigin(cTex->getSize().x/2,cTex->getSize().y/2);
    auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
    float s = cstate->zoomFactor();
    mCounter.setScale(s,s);

    //Launch swift sound
    mSwiftSound.setLoop(true);
    mSwiftSound.play();
    mThrowSound.play();
    mSelfhit = Core::get().globalDict()["selfHit"].toBool();
}

bool Arrow::update(float delta_s)
{
    delta_s*=1.5f;
    //TODO Arrow follow planet in which putted
    if(mPlanet)
    {
        mPos = mPlanet->getPosOn(mPhi);
    }
    else
    {
        if(hasTimeOut())
        {
            mSprite.setScale(0,0);
        }
        else
        {
            //TODO find which type cstate must be...
            auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
            SharedCharacter c = cstate->collideWithCharacter(mPos);
            if(c && (c->id() != mOwnerID || mSelfhit)) {
                c->hit(50);
                mTouchSound.play();
                if(c->isDead())
                    Core::get().timeStretch(0.125f,2.f);
            }
            mPlanet = cstate->collideWithPlanet(mPos);
            if(mPlanet) {
                mSprite.setTextureRect({0,0,10,5});
                mPhi = angle(mPos-mPlanet->getPosition());
                mPut = true;
                onPut();
            }
            using namespace std::placeholders;
            integrateEC(mPos, mSpeed, delta_s, std::bind(&StateConstellation::getGravFieldAt, cstate.get(), _1));
            mSwiftSound.setVolume(lenght(mSpeed)/30.f);
            mSprite.setRotation(angle(mSpeed)*TO_DEGREES);

            //Trail


            //Warning sound
            if(lastMoments() && mWarnSound.getStatus() == sf::Sound::Status::Stopped)
                mWarnSound.play();
        }
    }
    mTrail.addPoint(getPos());
    mSprite.setPosition(mPos);

    if(Core::get().isStretchin()) {
        float tf = Core::get().timeFactor();
        mSwiftSound.setVolume(60);
        mSwiftSound.setPitch(tf);
        mTouchSound.setPitch(tf);
        mDeathSound.setPitch(tf);
    }
    return true;
}

void Arrow::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());

    if(!mTimeOut)
        drawCursor(target,cstate);


    if(!(lastMoments() && !mPut && (int(ceilf(Core::get().time()*6.f))%2==0)))
    {
        target.draw(mSprite);
        target.draw(mTrail);
    }
    if(lastMoments() && !mPut && !mTimeOut)
        drawCounter(target,cstate);
}

void Arrow::drawCursor(sf::RenderTarget& target, SConst& cstate) const
{
    mCursor.setRotation(angle(mPos)*TO_DEGREES-90);
    mCursor.setPosition(mPos);

    sf::FloatRect cursorBounds = {mCursor.getLocalBounds().left+mPos.x,
                                  mCursor.getLocalBounds().top+mPos.y,
                                  mCursor.getLocalBounds().width,
                                  mCursor.getLocalBounds().height};
    sf::Vector2f newCursorPos = mCursor.getOrigin() + cstate->clampRect(cursorBounds);

    if(newCursorPos != sf::Vector2f{cursorBounds.left+mCursor.getOrigin().x,cursorBounds.top+mCursor.getOrigin().y})
    {
        mCursor.setPosition(newCursorPos);
        target.draw(mCursor);
    }
}

void Arrow::drawCounter(sf::RenderTarget& target, SConst& cstate) const
{
    mCounter.setValue(lifetime-Core::get().time()+mTimeStamp);
    sf::FloatRect bounds = mCounter.bounds();
    mCounter.setPosition(sf::Vector2f{7,-14} + cstate->clampRect({mPos.x+bounds.left,mPos.y-bounds.top,bounds.width,bounds.height}));
    target.draw(mCounter);
}

bool Arrow::dead()
{
    return hasTimeOut() && mDeathSound.getStatus() == sf::Sound::Stopped; //Wait for end of sound to destroy arrow
}

const sf::Vector2f& Arrow::getPos()
{
    return mPos;
}

bool Arrow::lastMoments() const
{
    return Core::get().time() - mTimeStamp > lifetime-2;
}

bool Arrow::hasTimeOut()
{
    if(Core::get().time() - mTimeStamp > lifetime && !mPut)
    {
        if(!mTimeOut)
        {
            mTimeOut = true;
            onTimeOut();
        }
        return true;
    }
    return false;
}

void Arrow::onPut()
{
    mPutSound.play();
    mSwiftSound.stop();
    if(mCallback) mCallback();
}

void Arrow::onTimeOut()
{
    mDeathSound.play();
    if(mCallback) mCallback();
}

void Arrow::setCallback(std::function<void()> callback)
{
    mCallback = callback;
}
