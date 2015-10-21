#include "Planet.h"
#include "VecUtils.h"

Planet::Planet(const sf::Vector3f &pos, float mass, float radius) :
    sf::CircleShape(radius), mMass(mass), m3DPos(pos), mRadius(radius)
{
    setFillColor(sf::Color::Red);
    setPosition(m2DPos);
}

const sf::Vector3f& Planet::get3DPos() const
{
    return m3DPos;
}

void Planet::update2DPos(const sf::Transform& trans)
{
    //TODO take transform into account
    setPosition({m3DPos.x, m3DPos.y});
}

/*void Planet::draw(sf::RenderTarget& target) const
{
    target.draw(mDisk);
}*/

sf::Vector2f Planet::get2DField(const sf::Vector2f& pos) const
{
    return 1.0/lenghtSquared(pos - getPosition()) * (pos-getPosition());
}

bool Planet::collideWith(SharedPlanet other) const
{

}

bool Planet::collideWith(const sf::Vector2f& point) const
{

}

sf::Color Planet::getColor() const
{

}
