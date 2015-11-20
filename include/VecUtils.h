#ifndef VECUTILS_H
#define VECUTILS_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

inline float lengthSquared(const sf::Vector2f &vec){
    return vec.x*vec.x+vec.y*vec.y;
}

inline float lenght(const sf::Vector2f& vec)
{
    return sqrt(lengthSquared(vec));
}

inline sf::Vector2f normalise(const sf::Vector2f& vec)
{
    return vec / lenght(vec);
}

inline float distanceSquared(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return lengthSquared(a - b);
}

inline float distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return sqrt(distanceSquared(a,b));
}

inline float angle(const sf::Vector2f& v)
{
    return atan2(v.y,v.x);
}

inline sf::Vector2f clamp(sf::Vector2f vect,float size)
{
    if(lenght(vect) > size){
        return normalise(vect) * size;
    }
    return vect;
}

inline sf::Vector2f rotate(sf::Vector2f vect, float angle)
{
    float cs = std::cos(angle);
    float sn = std::sin(angle);


    float px = vect.x * cs - vect.y * sn;
    float py = vect.x * sn + vect.y * cs;
    return sf::Vector2f{px,py};
}

inline sf::Vector2f perpendicularNorm(sf::Vector2f vect)
{
    vect = normalise(vect);
    return sf::Vector2f{vect.y,-vect.x};
}

#endif // VECUTILS_H

