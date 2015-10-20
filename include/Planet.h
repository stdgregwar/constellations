#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>

class Planet
{
public:
    Planet();
private:
    sf::Vector2f m2DPos;
    sf::Vector3f m3DPos;
    float mMass;
    float mRadius;
};

#endif // PLANET_H
