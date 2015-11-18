#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Widget.h"
#include <functional>

class Button : public Widget
{
public:
    Button(const sf::Text& text, std::function<void()> c);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void trigger();
    void setHovered(bool hover);
    sf::FloatRect bounds();
    bool onEvent(const sf::Event& e);
private:
    bool mHovered;
    sf::View mView;
    sf::Text mText;
    std::function<void()> mCallback;
};

#endif // BUTTON_H
