#ifndef BIBUTTON_H
#define BIBUTTON_H

#include "ProtoButton.h"
#include <SFML/Graphics/RectangleShape.hpp>

class BiButton : public ProtoButton
{
public:
    BiButton(const sf::FloatRect& bounds, std::function<void()> lc, std::function<void()> rc);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::FloatRect bounds() const override;
private:
    sf::FloatRect mBounds;
    mutable sf::RectangleShape mRect;
};

#endif // BIBUTTON_H
