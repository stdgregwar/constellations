#include <Core.h>
#include "CheckBox.h"


CheckBox::CheckBox(const sf::String& caption, bool checked,std::function<void(int)> callback, int csize): mCallback(callback),mChecked(checked)
{
    sf::Font &f(*Core::get().fontCache().get("default"));
    mCaption.setFont(f);
    mCaption.setString(caption+" : ");
    mCaption.setCharacterSize(csize);
    mCheckBoxText.setCharacterSize(csize);
    mCheckBoxText.setFont(f);
    mCheckBoxText.setString("[  ]");
    mCheckBoxText.move(mCaption.getLocalBounds().width+23,0);
    mCallback(checked);
}

void CheckBox::toggle()
{
    mChecked = !mChecked;
    if(!mChecked) mCheckBox->setDefaultColor(sf::Color::Transparent);
    else mCheckBox->setDefaultColor(sf::Color::White);
    mCallback(mChecked);
}

void CheckBox::setValue(bool boolean)
{
}

void CheckBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mCaption, states);
    target.draw(mCheckBoxText, states);
    Widget::draw(target,states);
}


void CheckBox::show()
{
    if(children().empty()) {
        mCheckBox.reset(new Button("x",std::bind(&CheckBox::toggle,this)));
        add(mCheckBox);
        mCheckBox->setPosition(mCaption.getLocalBounds().width+30,0);
    }
    Widget::show();
}
