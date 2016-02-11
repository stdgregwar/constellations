#ifndef PROTOBUTTON_H
#define PROTOBUTTON_H


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Widget.h"
#include <functional>

class ProtoButton;
typedef std::shared_ptr<ProtoButton> SharedProtoButton;
/**
 * @brief Represent a button that can be given to a widget
 *
 * The widget is given a callback to call if the button is pressed
 */
class ProtoButton : public Widget
{
public:
    /**
     * @brief Copy the text given and use it's location/boundaries as loc/b for the button
     * @param text an sf::Text instance
     * @param c callback function
     */
    ProtoButton(std::function<void()> lc,std::function<void()> rc);

    /**
     * @brief called when the button is triggered with left click
     */
    void Ltrigger();

    /**
     * @brief called when the button is triggered with right click
     */
    void Rtrigger();

    /**
     * @brief set if the button is hovered
     * @param hover
     */
    virtual void setHovered(bool hover){mHovered = hover;}

    /**
     * @brief bounds of the button
     * @return
     */
    //sf::FloatRect bounds() const;

    bool hovered() const{return mHovered;}

    /**
     * @brief called with each event of the renderwindow, check if button is clicked
     * @param e
     * @return
     */
    bool onEvent(const sf::Event& e, const sf::View& view);
private:
    bool mHovered;
    std::function<void()> mLCallback,mRCallback;
};

#endif // PROTOBUTTON_H
