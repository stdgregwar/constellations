#include "CaptionWidget.h"
#include "Core.h"

CaptionWidget::CaptionWidget(const sf::String &str, unsigned csize)
{
    mText.setFont(*Core::get().fontCache().get("default"));
    mText.setString(str);
    mText.setCharacterSize(csize);
}

void CaptionWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mText,states);
    Widget::draw(target,states);
}

