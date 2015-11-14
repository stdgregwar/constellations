#ifndef PLANET_H
#define PLANET_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Mat4.h"

class Planet;

typedef std::shared_ptr<Planet> SharedPlanet;

/**
 * @brief Represet a planet with 3D coordinates projeted in 2D
 */
class Planet : public sf::Sprite
{
public:
    Planet(const sf::Vector3f& pos, float mass, float radius);
    Planet(const Planet& other);
    Planet(const Planet&& other);

    /**
     * @brief getter for 3D pos
     * @return
     */
    const sf::Vector3f& get3DPos() const;

    /**
     * @brief project 3D position on 2D space
     * @param trans
     */
    void update2DPos(const Mat4& trans);
    //void draw(sf::RenderTarget& target) const;

    /**
     * @brief get the vectorial gravitational field contribution of this planet on given position
     * @param pos
     * @return
     */
    sf::Vector2f get2DField(const sf::Vector2f& pos) const;

    /**
     * @brief test wether an other planet intersects this one
     * @param other
     * @return
     */
    bool collideWith(SharedPlanet other) const;

    /**
     * @brief test wether a given point is in the planet
     * @param point
     * @return
     */
    bool collideWith(const sf::Vector2f& point) const;

    /**
     * @brief get planet color based on mass
     * @return
     */
    sf::Color getColor() const;

    sf::Vector2f getPosOn(float angle);

    float getRadius() const {return m3DRadius;}
private:
    sf::Vector3f m3DPos;
    float m3DRadius;
    float mMass;
    sf::Texture mTexture;
};

#endif // PLANET_H
