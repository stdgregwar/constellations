#ifndef COUNTER_H
#define COUNTER_H

#include <SFML/Graphics.hpp>


/**
 * @brief Graphical representation of a chrono counter with seconds cents
 */
class Counter : public sf::Drawable, public sf::Transformable
{
public:
    /**
     * @brief construct counter
     * @param color text color
     * @param characterSize characterSize
     * @param font
     */
    Counter(sf::Color color, int characterSize, sf::Font* font = nullptr);

    /**
     * @brief draw counter on given target
     * @param target render target
     * @param states render states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /**
     * @brief sets the counter value
     * @param value value
     */
    void setValue(float value);

    /**
     * @brief gets the counter value
     * @return
     */
    float getValue() const;

    /**
     * @brief get counter global bounds
     * @return
     */
    sf::FloatRect bounds() const;
private:
    mutable sf::Text mMain;
    mutable sf::Text mSecond;
    float mValue;
};

#endif // COUNTER_H
