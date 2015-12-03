#include "Button.h"
#include "Core.h"

Button::Button(const sf::String &text, std::function<void()> c, int csize)
    : mCallback(c)
{
    mText.setFont(*Core::get().fontCache().get("default"));
    mText.setString(text);
    mText.setCharacterSize(csize);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mText,states);
    Widget::draw(target,states);
}

void Button::trigger()
{
    mCallback();
}

void Button::setHovered(bool hover)
{
    mText.setColor(hover ? sf::Color::Yellow : sf::Color::White); //TODO parametrize colors
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
