#ifndef TRANSITION_H
#define TRANSITION_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>

class Transition : public sf::Drawable
{
public:
    enum Draw
    {
        FIRST,
        SECOND
    };

    Transition();
    void setTexture(sf::Texture* tex);
    virtual Draw update() = 0;
    const sf::Texture* tRender() const;
private:
    sf::Texture* mTexture;
};

#endif // TRANSITION_H
