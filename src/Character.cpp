#include "Character.h"
#include <cmath>

Character::Character(SharedPlanet planet) : mPlanet(planet), mFrame(0), mWalking(true)
{
    setPhi(0);
    mTex.loadFromFile("data/chara_w_6.png");
    mSprite.setTexture(mTex);
    mSprite.setOrigin(9,28);
    mSprite.setTextureRect({0,0,18,30});
    //setColor(sf::Color::Red);
}

Character::Character(const Character& other)
    : mTex(other.mTex), mSprite(other.mSprite), mPlanet(other.mPlanet), mFrame(0), mWalking(other.mWalking)
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
                mActionSpeed.x += a.move.distance;
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
