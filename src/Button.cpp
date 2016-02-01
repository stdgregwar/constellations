#include "Button.h"
#include "Core.h"

Button::Button(const sf::String &text, std::function<void()> c, int csize,const sf::Color& hoveredColor,const sf::Color& defaultColor)
    : mCallback(c),mHoveredColor(hoveredColor),mDefaultColor(defaultColor)
{
    mText.setFont(*Core::get().fontCache().get("default"));
    mText.setString(text);
    mText.setCharacterSize(csize);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(visible())
        target.draw(mText,states);
    Widget::draw(target,states);
}

void Button::trigger()
{
    mCallback();
}

void Button::setHovered(bool hover)
{
    mText.setColor(hover ? mHoveredColor : mDefaultColor); //TODO parametrize colors
}

sf::FloatRect Button::bounds()
{
    return getFullTransform().transformRect(mText.getLocalBounds());
}

bool Button::onEvent(const sf::Event& e, const sf::View &view)
{
    switch(e.type)
    {
        case sf::Event::MouseButtonReleased:
        {
            sf::Vector2f mapPos = Core::get().renderWindow().mapPixelToCoords({e.mouseButton.x,e.mouseButton.y},view);
            if(bounds().contains(mapPos))
                trigger();
            break;
        }
        case sf::Event::MouseMoved:
        {
            sf::Vector2f mapPos = Core::get().renderWindow().mapPixelToCoords({e.mouseMove.x,e.mouseMove.y},view);
            setHovered(bounds().contains(mapPos));
            break;
        }
    }
}

void Button::setText(const sf::String &text)
{
    mText.setString(text);
}

void Button::setHoveredColor(const sf::Color &c)
{
    mHoveredColor = c;
}

void Button::setDefaultColor(const sf::Color &c)
{
    mDefaultColor = c;
}
