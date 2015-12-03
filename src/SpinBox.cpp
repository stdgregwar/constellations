#include "SpinBox.h"
#include <string>
#include "Button.h"
#include "Core.h"
#include <functional>

using namespace std;

SpinBox::SpinBox(const sf::String& text, int basevalue, int min, int max, std::function<void(int)> callback, int csize)
    : mValue(basevalue),mMin(min), mMax(max),mCallback(callback)
{
    sf::Font &f(*Core::get().fontCache().get("default"));
    mCaption.setFont(f);
    mCaption.setString(text+" : ");
    mCaption.setCharacterSize(csize);
    mValueText.setCharacterSize(csize);
    mValueText.setFont(f);
    mValueText.setString(to_string(mValue));
    mValueText.move(mCaption.getLocalBounds().width+30,0);
    mCallback(mValue);
}

void SpinBox::show()
{
    if(children().empty()) {
        mLeft = add(new Button("<",std::bind(&SpinBox::decrement,this)));
        mLeft->setPosition(mCaption.getLocalBounds().width+5,0);
        mRight = add(new Button(">",std::bind(&SpinBox::increment,this)));
        mRight->setPosition(mValueText.getGlobalBounds().left+mValueText.getLocalBounds().width+5,0);
    }
    Widget::show();
}

void SpinBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mCaption,states);
    target.draw(mValueText,states);
    Widget::draw(target,states);
}

void SpinBox::setValue(int val)
{
    //TODO
}

void SpinBox::increment()
{
    mValue = min(mValue+1,mMax);
    mValueText.setString(to_string(mValue));
    updateLeftRightPos();
    mCallback(mValue);
}

void SpinBox::updateLeftRightPos()
{
    mLeft->setPosition(mCaption.getLocalBounds().width+5,0);
    mRight->setPosition(mValueText.getGlobalBounds().left+mValueText.getLocalBounds().width+5,0);
}

void SpinBox::decrement()
{
    mValue = max(mValue-1,mMin);
    mValueText.setString(to_string(mValue));
    updateLeftRightPos();
    mCallback(mValue);
}
