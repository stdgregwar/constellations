#ifndef CAPTIONWIDGET_H
#define CAPTIONWIDGET_H

#include "Widget.h"
#include <SFML/Graphics/Text.hpp>

/**
 * @brief Used to display static text in widget fashion. Allowin it to be easly placed in space
 */
class CaptionWidget : public Widget
{
public:
    CaptionWidget(const sf::String& str, unsigned csize = 50);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    sf::Text mText;
};

#endif // CAPTIONWIDGET_H
