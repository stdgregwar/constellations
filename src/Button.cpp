#include "Button.h"
#include "Core.h"

Button::Button(const sf::String &text, std::function<void()> c, int csize,const sf::Color& hoveredColor,const sf::Color& defaultColor)
    : ProtoButton(c,nullptr),mHoveredColor(hoveredColor),mDefaultColor(defaultColor)
{
    const sf::Texture& tex = Core::get().fontCache().get("default")->getTexture(csize);
    ((sf::Texture*)(&tex))->setSmooth(false);
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

void Button::setEnabled(bool enabled)
{
    mText.setColor(enabled ? mDefaultColor : sf::Color(64,64,64));
    ProtoButton::setEnabled(enabled);
}

void Button::setHovered(bool hover)
{
    if(enabled())
        mText.setColor(hover ? mHoveredColor : mDefaultColor); //TODO parametrize colors
}

sf::FloatRect Button::bounds() const
{
    return getFullTransform().transformRect(mText.getLocalBounds());
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
