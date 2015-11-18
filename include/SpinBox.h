#ifndef SPINBOX_H
#define SPINBOX_H

#include "Widget.h"
#include <SFML/Graphics/Text.hpp>

class SpinBox : public Widget
{
public:
    SpinBox(sf::Text caption, int basevalue, int min, int max, std::function<void(int)> callback);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void increment();
    void decrement();
    void show();
    void setValue(int val);
private:
    int mValue;
    int mMin;
    int mMax;
    sf::Text mValueText;
    sf::Text mCaption;
    std::function<void(int)> mCallback;
};

#endif // SPINBOX_H
