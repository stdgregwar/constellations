#ifndef VECUTILS_H
#define VECUTILS_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cmath>
#include <limits>

const sf::FloatRect INFRECT(
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            -std::numeric_limits<float>::max(),
            -std::numeric_limits<float>::max()
);

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

//Dot product on operator *
inline float operator*(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return a.x*b.x+a.y*b.y;
}

/**
 * @brief mirror the given vector by the given normal only if it goes toward the plane
 * @param d vector direction
 * @param n normal vector
 * @return d if d in same 'direction' than n, d mirrored by n otherwise
 */
inline sf::Vector2f bounce(const sf::Vector2f& d, const sf::Vector2f& n)
{
    float r = (2.f*d*n);
    if(r < 0)
        return d - r*n;
    else
        return d;
}

inline sf::FloatRect rectUnion(const sf::FloatRect& first, const sf::FloatRect& second)
{
    sf::FloatRect r;
    r.left = std::min(first.left,second.left);
    r.top = std::min(first.top,second.top);
    r.width = std::max(first.left+first.width,second.left+second.width);
    r.height = std::max(first.top+first.height,second.top+second.height);
    r.width -= r.left;
    r.height -= r.top;
    return r;
}

#endif // VECUTILS_H

