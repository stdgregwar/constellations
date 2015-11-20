#ifndef CONSTELLATIONS_INTEGRATIONUTILS_H
#define CONSTELLATIONS_INTEGRATIONUTILS_H

#include <SFML/System/Vector2.hpp>
#include <utility>
#include <functional>

inline void integrateRG4(sf::Vector2f &position, sf::Vector2f &speed, float dt,
                         std::function<sf::Vector2f(const sf::Vector2f &p, const sf::Vector2f &v)> const &eq)
{

            // clang-format off
            auto const& k1  = speed;
            auto const& k1p = eq(position, speed);
            auto const& k2  = speed + dt / 2.f * k1p;
            auto const& k2p = eq(position + dt / 2.f * k1, speed + dt / 2.f * k1p);
            auto const& k3  = speed + dt / 2.f * k2p;
            auto const& k3p = eq(position + dt / 2.f * k2, speed + dt / 2.f * k2p);
            auto const& k4  = speed + dt * k3p;
            auto const& k4p = eq(position + dt / 2.f * k3, speed + dt / 2.f * k3p);

            auto const& newPosition = position + dt / 6.f * (k1  + 2.f * k2  + 2.f * k3  + k4);
            auto const& newSpeed    = speed    + dt / 6.f * (k1p + 2.f * k2p + 2.f * k3p + k4p);

            position = newPosition;
            speed = newSpeed;
}

inline void integrateEC(sf::Vector2f &position, sf::Vector2f &speed, float dt,
                        std::function<sf::Vector2f(const sf::Vector2f &p, const sf::Vector2f &v)> const &eq)
{
    speed += eq(position, speed) * dt;
    position += speed * dt;
}

#endif //CONSTELLATIONS_INTEGRATIONUTILS_H
