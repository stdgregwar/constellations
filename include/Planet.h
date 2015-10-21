#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>
#include <memory>

class Planet;

typedef std::shared_ptr<Planet> SharedPlanet;

class Planet : public sf::Drawable, public sf::CircleShape
{
public:
    Planet(const sf::Vector3f& pos, float mass, float radius);
    const sf::Vector3f& get3DPos() const;
    void update2DPos(const sf::Transform& trans);
    //void draw(sf::RenderTarget& target) const;
    sf::Vector2f get2DField(const sf::Vector2f& pos) const;
    bool collideWith(SharedPlanet other) const;
    bool collideWith(const sf::Vector2f& point) const;
    sf::Color getColor() const;
private:
    sf::Vector3f m3DPos;
    float mMass;
};

#endif // PLANET_H
