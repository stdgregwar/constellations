#ifndef SKINANIMATION_H
#define SKINANIMATION_H

#include "MathUtils.h"
#include <SFML/Graphics/Sprite.hpp>

class SkinAnimation
{
public:
    SkinAnimation();
    virtual void rFoot(sf::Sprite& foot,float t) = 0;
    virtual void lFoot(sf::Sprite& foot,float t) = 0;
    virtual void body(sf::Sprite& body,float t) = 0;
    virtual void eyes(sf::Sprite& e, float t) = 0;
};

#endif // SKINANIMATION_H
