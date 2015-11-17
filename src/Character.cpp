#include "Character.h"
#include "VecUtils.h"
#include "Path.h"
#include <cmath>
#include <iostream>
#include <Core.h>
#include <StateConstellation.h>

using namespace std;
Path Character::mPath;

Character::Character(SharedPlanet planet, const PlayerID &id, sf::Color c)
    : mPlanet(planet), mFrame(0), mWalking(true), mAiming(false), mColor(c), mPV(25), mID(id)
{
    setPhi(0);
    mSprite.setTexture(*Core::get().textureCache().get("data/chara_w_6.png"));
    mSprite.setOrigin(9,28);
    mSprite.setTextureRect({0,0,18,30});
    mSprite.setColor(mColor);
}

Character::Character(const Character& other)
    : mSprite(other.mSprite), mPlanet(other.mPlanet), mFrame(0), mWalking(other.mWalking), mAiming(other.mAiming), mArrowStartingPoint{0,0}, mPV(other.mPV)
{
    setPhi(other.mPhi);
}

Character::Character(const Character&& other)
    :  mSprite(other.mSprite), mPlanet(other.mPlanet), mFrame(0), mWalking(other.mWalking), mPV(other.mPV)
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
    constexpr float TO_DEGREES = 180.0/3.1415;
    if(mPlanet) {
        mSprite.setPosition(mPlanet->getPosOn(mPhi));
        mSprite.setRotation(mPhi*TO_DEGREES+90);
        //TODO position of arrow depedent of texture height, may not be a good solution
        sf::Vector2f height = {0,mSprite.getTextureRect().height};
        height = rotate(height,mPhi- 90/TO_DEGREES);
        mArrowStartingPoint = mSprite.getPosition() + height;
    }
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    updateFrame();
    target.draw(mSprite);
    if(mAiming)
    {
        auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
        mPath.create(cstate->pathForInitials(mArrowStartingPoint,mArrowVec*8.0f,16),2.f,mColor,0.999);
        target.draw(mPath);
    }
}

void Character::updateFrame() const
{
    mFrame = (int)(Core::get().time()*10)%3;
    if(mWalking)
        mSprite.setTextureRect({18*mFrame,0,18,30});
    else
        mSprite.setTextureRect({0,0,18,30});
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
                mActionSpeed.x += a.move.distance;
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
                SharedArrow arrow = SharedArrow(new Arrow{mArrowStartingPoint, speed, 0,id()});
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

bool Character::isDead()
{
    return mPV <= 0;
}

void Character::hit(int pvs)
{
    mPV -= pvs;
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
    return mSprite.getGlobalBounds().contains(p);
}

const PlayerID& Character::id()
{
    return mID;
}

Character::~Character()
{
    Core::get().textureCache().free(mSprite.getTexture());
}
