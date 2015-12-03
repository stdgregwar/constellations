#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Widget.h"
#include <functional>

/**
 * @brief Represent a button that can be given to a widget
 *
 * The widget is given a callback to call if the button is pressed
 */
class Button : public Widget
{
public:
    /**
     * @brief Copy the text given and use it's location/boundaries as loc/b for the button
     * @param text an sf::Text instance
     * @param c callback function
     */
    Button(const sf::String& text, std::function<void()> c, int csize = 50);

    /**
     * @brief draw the button on the given target
     * @param target
     * @param states
     */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /**
     * @brief called when the button is triggered
     */
    void trigger();

    /**
     * @brief set if the button is hovered
     * @param hover
     */
    void setHovered(bool hover);

    /**
     * @brief bounds of the button
     * @return
     */
    sf::FloatRect bounds();

    /**
     * @brief called with each event of the renderwindow, check if button is clicked
     * @param e
     * @return
     */
    bool onEvent(const sf::Event& e, const sf::View& view);
private:
    bool mHovered;
    sf::Text mText;
    std::function<void()> mCallback;
};

#endif // BUTTON_H
