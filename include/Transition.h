#ifndef TRANSITION_H
#define TRANSITION_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>

class Transition : public sf::Drawable
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
};

#endif // TRANSITION_H
