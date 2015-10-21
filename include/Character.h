#ifndef CHARACTER_H
#define CHARACTER_H

#include "Planet.h"
#include <SFML/Graphics/Sprite.hpp>

class Character : public sf::Sprite
{
public:
    Character(Planet* planet);
    void rot(float dphi);
    void setPhi(float phi);
    void updatePos();
private:
    Planet* mPlanet;
    float mPhi;

};

#endif // CHARACTER_H
