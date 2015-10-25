#include "Planet.h"
#include "VecUtils.h"
#include <cmath>

Planet::Planet(const sf::Vector3f &pos, float mass, float radius) :
    sf::CircleShape(radius), mMass(mass), m3DPos(pos), m3DRadius(radius)
{
    setFillColor(getColor());
    setOrigin(radius,radius);
    //update2DPos();
}

Planet::Planet(const Planet& other) : sf::CircleShape(other), mMass(other.mMass), m3DPos(other.m3DPos)
{

}

Planet::Planet(const Planet&& other) : sf::CircleShape(other), mMass(other.mMass), m3DPos(other.m3DPos)
{

}

const sf::Vector3f& Planet::get3DPos() const
{
    return m3DPos;
}

void Planet::update2DPos(const Mat4 &trans)
{
    //TODO take transform into account
    sf::Vector3f proj = trans*m3DPos;
    setPosition({proj.x, proj.y});
    setRadius(std::abs(m3DRadius*(1+proj.z/70)));
    setOrigin(getRadius(),getRadius());
}

/*void Planet::draw(sf::RenderTarget& target) const
{
    target.draw(mDisk);
}*/

sf::Vector2f Planet::get2DField(const sf::Vector2f& pos) const
{
    return 1.f/distanceSquared(pos,getPosition()) * normalise(getPosition()-pos);
}

bool Planet::collideWith(SharedPlanet other) const
{
    return (other->getRadius()+getRadius())*(other->getRadius()+getRadius()) > distanceSquared(getPosition(),other->getPosition()); //uses squares to save a squareroot
}

bool Planet::collideWith(const sf::Vector2f& point) const
{
    return getRadius()*getRadius() > distanceSquared(point, getPosition());
}

sf::Color Planet::getColor() const
{
    return sf::Color(255/mMass,0,0);
}
