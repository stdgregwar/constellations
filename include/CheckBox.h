#ifndef CONSTELLATIONS_CHECKBOX_H
#define CONSTELLATIONS_CHECKBOX_H


#include "Widget.h"
#include "Button.h"
#include <SFML/Graphics/Text.hpp>

class CheckBox : public Widget
{
public:
    CheckBox(const sf::String& caption, bool checked,std::function<void(int)> callback,int csize = 50);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void toggle();
    void show();
    void setValue(bool boolean);

private:
    bool mChecked;
    sf::Text mCaption;
    sf::Text mCheckBoxText;
    SharedButton mCheckBox;
    std::function<void(int)> mCallback;
};


#endif //CONSTELLATIONS_CHECKBOX_H
