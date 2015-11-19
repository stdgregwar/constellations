#include "Character.h"
#include "VecUtils.h"
#include "ColorUtils.h"
#include "Path.h"
#include <cmath>
#include <iostream>
#include <Core.h>
#include <StateConstellation.h>

using namespace std;
Path Character::mPath;

Character::Character(SharedPlanet planet, const PlayerID &id, sf::Color c)
    : mPlanet(planet), mFrame(0), mWalking(true), mAiming(false), mColor(c), mPV(Core::get().globalDict()["player_pv"].toInt()*50), mID(id), mLastHitTime(0)
{
    setPhi(0);
    mSprite.setTexture(*Core::get().textureCache().get("data/chara_w_6.png"));
    mSprite.setOrigin(9,28);
    mSprite.setTextureRect({0,0,18,30});
    mSprite.setColor(mColor);
    mCursor.setTexture(*Core::get().textureCache().get("data/cursor.png"));
    mCursor.setOrigin(8,mSprite.getTextureRect().height+20);
    mCursor.setColor(saturate(mColor,.7));
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
    //If invulnerable, make sprite blink
    mSprite.setColor((!isVulnerable() && int(ceilf(Core::get().time()*6.f))%2==0) ?  sf::Color(mColor.r,mColor.g,mColor.b,0) : mColor);
    target.draw(mSprite);
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
    mCursor.setOrigin(8,mSprite.getTextureRect().height+15+sin(Core::get().time()*5)*3);
    target.draw(mCursor);
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
    return mSprite.getGlobalBounds().contains(p);
}

const PlayerID& Character::id() const
{
    return mID;
}

Character::~Character()
{
    Core::get().textureCache().free(mSprite.getTexture());
    Core::get().textureCache().free(mCursor.getTexture());
}
