#ifndef TRANSITION_H
#define TRANSITION_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>

class Transition
{
public:
    enum State
    {
        FIRST,
        SECOND,
        END
    };

    Transition();
    virtual State update() = 0;
    virtual void render(sf::RenderTarget& target, const sf::Texture& first, const sf::Texture& second) const = 0;
};

#endif // TRANSITION_H
