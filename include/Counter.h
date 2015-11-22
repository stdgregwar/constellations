#ifndef COUNTER_H
#define COUNTER_H

#include <SFML/Graphics.hpp>


class Counter : public sf::Drawable, public sf::Transformable
{
public:
    Counter(sf::Color color, int characterSize, sf::Font* font = nullptr);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void setValue(float value);
    float getValue() const;
    sf::FloatRect bounds() const;
private:
    mutable sf::Text mMain;
    mutable sf::Text mSecond;
    float mValue;
};

#endif // COUNTER_H
