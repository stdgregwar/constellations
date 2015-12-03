#ifndef SPINBOX_H
#define SPINBOX_H

#include "Widget.h"
#include <SFML/Graphics/Text.hpp>

class SpinBox : public Widget
{
public:
    SpinBox(const sf::String& text, int basevalue, int min, int max, std::function<void(int)> callback, int csize = 50);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void increment();
    void decrement();
    void show();
    void setValue(int val);
private:
    void updateLeftRightPos();
    int mValue;
    int mMin;
    int mMax;
    sf::Text mValueText;
    sf::Text mCaption;
    std::function<void(int)> mCallback;
    SharedWidget mLeft,mRight;
};

#endif // SPINBOX_H
