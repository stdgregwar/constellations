#include "Character.h"
#include "VecUtils.h"
#include <cmath>
#include <iostream>
using namespace std;

Character::Character(SharedPlanet planet) : mPlanet(planet), mFrame(0), mWalking(true), mAiming(false)
{
    setPhi(0);
    mTex.loadFromFile("data/chara_w_6.png");
    mSprite.setTexture(mTex);
    mSprite.setOrigin(9,28);
    mSprite.setTextureRect({0,0,18,30});
    //setColor(sf::Color::Red);
}

Character::Character(const Character& other)
    : mTex(other.mTex), mSprite(other.mSprite), mPlanet(other.mPlanet), mFrame(0), mWalking(other.mWalking), mAiming(other.mAiming)
{
    setPhi(other.mPhi);
}

Character::Character(const Character&& other)
    : mTex(other.mTex), mSprite(other.mSprite), mPlanet(other.mPlanet), mFrame(0), mWalking(other.mWalking)
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
    }
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite,states);
    if(mAiming)
    {
        sf::Vector2f height = {0,mSprite.getGlobalBounds().height};
        height = VECUTILS_H::rotate(height,mPhi- 90/TO_DEGREES);

        sf::Vertex line[] =
                {
                        mSprite.getPosition()+height,
                        mSprite.getPosition()+height+mArrowVec
                };
        target.draw(line,2,sf::Lines);
    }
}

void Character::updateFrame()
{
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
                mAiming = false;
                mActionSpeed.x += a.move.distance;
                break;
            case Action::AIM:
                mActionSpeed.x = 0;
                mAiming = true;
                mArrowVec = VECUTILS_H::clamp(a.aim.direction,50);

                break;
            case Action::THROW:
                mAiming = false;
                break;
            case Action::CANCEL:
                mAiming = false;
                break;
            default:
                break;
        }
    }
    mFrameTime+=delta_s;
    mFrame = (int)(mFrameTime*10)%3;
    rot(mActionSpeed.x*delta_s);
    updateFrame();
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
