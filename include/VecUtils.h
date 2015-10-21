#ifndef VECUTILS_H
#define VECUTILS_H

#include <SFML/System/Vector2.hpp>

float lenghtSquared(const sf::Vector2f& vec){
    return vec.x*vec.x+vec.y*vec.y;
}

#endif // VECUTILS_H

