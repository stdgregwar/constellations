#include "ComboBox.h"

using namespace std;

ComboBox::ComboBox(const Choices& choices, unsigned def, std::function<void(unsigned id)> callback, unsigned csize, const sf::Color& hoverColor, const sf::Color& mainColor)
    : mChoices(choices), mCallback(callback), mDefault(def), mDeployed(false)
{
}

void ComboBox::show()
{
    if(children().empty())
    {
        mMainButton = static_pointer_cast<Button>(add(new Button("--- \\/",bind(&ComboBox::clicked,this))));
        float height = 0;
        for(const pair<unsigned,string>& p : mChoices)
        {
            if(mDefault == p.first)
            {
                mMainButton->setText(p.second.substr(0,4) + ".\\/");
                choose(p.first);
            }
            SharedWidget w = add(new Button(p.second, bind(&ComboBox::choose, this, p.first)));
            w->setPosition(0,height+=40);
            mBChoices.push_back(w);
        }
    }
    //mMainButton->show();
    Widget::show();
    hideChoices();
}

void ComboBox::clicked()
{
    if(mDeployed){
        hideChoices();
    } else {
        showChoices();
    }
    mDeployed = !mDeployed;
}

void ComboBox::choose(unsigned id)
{
    mMainButton->setText(mChoices[id].substr(0,4)+".\\/");
    if(mCallback)
        mCallback(id);
    hideChoices();
    mDeployed = false;
}

void ComboBox::showChoices()
{
    for(SharedWidget& w : mBChoices)
        w->show();
}

void ComboBox::hideChoices()
{
    for(SharedWidget& w : mBChoices)
        w->hide();
}
