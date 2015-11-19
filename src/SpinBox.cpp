#include "SpinBox.h"
#include <string>
#include "Button.h"
#include <functional>

using namespace std;

SpinBox::SpinBox(sf::Text caption, int basevalue, int min, int max, std::function<void(int)> callback)
    : mCaption(caption), mValue(basevalue),mMin(min), mMax(max),mValueText(caption),mCallback(callback)
{
    mValueText.setString(to_string(mValue));
    mValueText.move(mCaption.getLocalBounds().width+60,0);
    mCallback(mValue);
}

void SpinBox::show()
{
    if(children().empty()) {
        sf::Text text = mValueText;
        text.move(-30,0);
        text.setString("<");
        add(new Button(text,std::bind(&SpinBox::decrement,this)));
        text = mValueText;
        text.move(10+mValueText.getLocalBounds().width,0);
        text.setString(">");
        add(new Button(text,std::bind(&SpinBox::increment,this)));
    }
    Widget::show();
}

void SpinBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mCaption);
    target.draw(mValueText);
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
    mCallback(mValue);
}

void SpinBox::decrement()
{
    mValue = max(mValue-1,mMin);
    mValueText.setString(to_string(mValue));
    mCallback(mValue);
}
