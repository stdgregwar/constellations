#include "Character.h"
#include <cmath>

Character::Character(Planet* planet) : mPlanet(planet)
{
    setPhi(0);
}

void Character::rot(float dphi)
{
    mPhi += dphi;
    updatePos();
}

void Character::updatePos()
{
    if(mPlanet) {
        sf::Vector2f r = sf::Vector2f(cos(mPhi),sin(mPhi)) * mPlanet->getRadius();
        setPosition(mPlanet->getPosition()+r);
        setRotation(mPhi);
    }
}

void Character::setPhi(float phi)
{
    mPhi = phi;
    updatePos();
}
