#include "Character.h"
#include "VecUtils.h"
#include "ColorUtils.h"
#include "Path.h"
#include <cmath>
#include <iostream>
#include <Core.h>
#include <StateConstellation.h>
#include "MathUtils.h"

using namespace std;
Path Character::mPath;

Character::Character(SharedPlanet planet, const PlayerID &id, sf::Color c, float phi)
    : mPlanet(planet), mFrame(0), mWalking(true), mAiming(false), mColor(c),
      mPV(Core::get().globalDict()["player_pv"].toInt()*50), mID(id), mLastHitTime(0),
      mSkin(Core::get().textureCache().get("data/skin.png"),Animations::basic)
{
    setPhi(phi);
    //mSkin.setTexture(*Core::get().textureCache().get("data/chara_w_6.png"));
    //mSkin.setOrigin(9,28);
    //mSkin.setTextureRect({0,0,18,30});
    mSkin.setColor(mColor);
    mCursor.setTexture(*Core::get().textureCache().get("data/cursor.png"));
    mCursor.setOrigin(8,mSkin.height()+20);
    mCursor.setColor(saturate(mColor,.7));
    mSkin.setAnimation("idle");
}


Character::Character(const Character& other)
    : mSkin(other.mSkin), mPlanet(other.mPlanet), mFrame(0), mWalking(other.mWalking), mAiming(other.mAiming), mArrowStartingPoint{0,0}, mPV(other.mPV)
{
    setPhi(other.mPhi);
}

Character::Character(const Character&& other)
    :  mSkin(other.mSkin), mPlanet(other.mPlanet), mFrame(0), mWalking(other.mWalking), mPV(other.mPV)
{
    setPhi(other.mPhi);
}

void Character::rot(float dphi)
{
    mPhi += dphi;
    updatePos();
}

void Character::updatePos()
{
    if(mPlanet) {
        mSkin.setPosition(mPlanet->getPosOn(mPhi));
        mSkin.setRotation(mPhi*TO_DEGREES+90);
        if(mActionSpeed.x)
        {
            mSkin.setScale(mActionSpeed.x/abs(mActionSpeed.x),1);
            mSkin.setAnimation("walk");
        }
        else
            mSkin.setAnimation("idle");
        //TODO position of arrow depedent of texture height, may not be a good solution
        sf::Vector2f height = {0,mSkin.height()};
        height = rotate(height,mPhi- 90/TO_DEGREES);
        mArrowStartingPoint = mSkin.getPosition() + height;
    }
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    updateFrame();
    //If invulnerable, make sprite blink
    if(!(!isVulnerable() && int(ceilf(Core::get().time()*6.f))%2==0))
        target.draw(mSkin);
    if(mAiming)
    {
        auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
        mPath.create(cstate->pathForInitials(mArrowStartingPoint,mArrowVec*8.0f,2048),2.f,saturate(mColor,.7),0.999);
        target.draw(mPath);
    }
    auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
    if(cstate->isCurrentPlayer(mID))
    {
        drawCursor(target,states);
    }
}

void Character::drawCursor(sf::RenderTarget &target, sf::RenderStates states) const
{
    constexpr float TO_DEGREES = 180.0/3.1415;
    if(mPlanet) {
        mCursor.setPosition(mPlanet->getPosOn(mPhi));
        mCursor.setRotation(mPhi*TO_DEGREES+90);
    }
    mCursor.setOrigin(8,mSkin.height()+15+sin(Core::get().time()*5)*3);
    target.draw(mCursor);
}


void Character::updateFrame() const
{
    /*mFrame = (int)(Core::get().time()*10)%3;
    if(mWalking)
        mSkin.setTextureRect({18*mFrame,0,18,30});
    else
        mSkin.setTextureRect({0,0,18,30});*/
}

void Character::update(float delta_s)
{
    for(Action a; mActionQueue.pollAction(a);)
    {
        switch(a.type)
        {
            case Action::MOVE_X:
            {
                mAiming = false;
                mActionSpeed.x += a.move.distance*(25.f/mPlanet->getRadius());
                break;
            }
            case Action::AIM:
            {
                mActionSpeed.x = 0;
                mAiming = true;
                mArrowVec = -clamp(a.aim.direction, 50);
                break;
            }
            case Action::THROW:
            {
                mAiming = false;
                auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
                //TODO tweak factor or store it somewhere
                sf::Vector2f speed = mArrowVec * 8.0f;
                SharedArrow arrow = SharedArrow(new Arrow{mArrowStartingPoint, speed,id()});
                cstate->pushArrow(arrow);
                break;
            }
            case Action::CANCEL:
            {
                mAiming = false;
                break;
            }
            default:
                break;
        }
    }

    rot(mActionSpeed.x*delta_s);
}

bool Character::isDead() const
{
    return mPV <= 0;
}

void Character::hit(int pvs)
{
    if(isVulnerable())
    {
        mPV -= pvs;
        mLastHitTime = Core::get().time();
    }
}

bool Character::isVulnerable() const
{
    return Core::get().time() - mLastHitTime > 1.f;
}

void Character::queueAction(const Action &a)
{
    mActionQueue.queue(a);
}

void Character::setPhi(float phi)
{
    mPhi = phi;
    updatePos();
}

bool Character::collideWith(const sf::Vector2f& p) const
{
    return mSkin.inBody(p);
}

const PlayerID& Character::id() const
{
    return mID;
}

sf::FloatRect Character::getBounds() const
{
    return mSkin.getGlobalBounds();
}

Character::~Character()
{
    Core::get().textureCache().free(mCursor.getTexture());
}
