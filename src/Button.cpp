#include "Button.h"
#include "Core.h"

Button::Button(const sf::Text& text, std::function<void()> c)
    : mText(text), mCallback(c)
{

}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mText);
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
    return mText.getGlobalBounds();
}

bool Button::onEvent(const sf::Event& e)
{
    switch(e.type)
    {
        case sf::Event::MouseButtonReleased:
        {
            sf::Vector2f mapPos = Core::get().renderWindow().mapPixelToCoords({e.mouseButton.x,e.mouseButton.y},mView);
            if(mText.getGlobalBounds().contains(mapPos))
                trigger();
            break;
        }
        case sf::Event::MouseMoved:
        {
            sf::Vector2f mapPos = Core::get().renderWindow().mapPixelToCoords({e.mouseMove.x,e.mouseMove.y},mView);
            setHovered(mText.getGlobalBounds().contains(mapPos));
            break;
        }
        case sf::Event::Resized:
            mView = Core::get().renderWindow().getDefaultView();
            break;
    }
}
