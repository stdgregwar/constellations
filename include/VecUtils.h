#ifndef VECUTILS_H
#define VECUTILS_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

inline float lenghtSquared(const sf::Vector2f& vec){
    return vec.x*vec.x+vec.y*vec.y;
}

inline float lenght(const sf::Vector2f& vec) {
    return sqrt(lenghtSquared(vec));
}

inline sf::Vector2f normalise(const sf::Vector2f& vec){
    return vec / lenght(vec);
}

inline float distanceSquared(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return lenghtSquared(a-b);
}

inline float distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return sqrt(distanceSquared(a,b));
}

#endif // VECUTILS_H

