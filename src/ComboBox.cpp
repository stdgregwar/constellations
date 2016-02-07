#include "ComboBox.h"
#include "Core.h"
#include <limits>
#include "VecUtils.h"

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

bool ComboBox::onEvent(const sf::Event &e, const sf::View &view)
{

    if(e.type == sf::Event::MouseMoved && mDeployed)
    {
        sf::Vector2f mapPos = Core::get().renderWindow().mapPixelToCoords({e.mouseMove.x,e.mouseMove.y},view);
        if(!mBounds.contains(mapPos))
            hideChoices();
    }
}

void ComboBox::clicked()
{
    if(mDeployed){
        hideChoices();
    } else {
        showChoices();
    }
}

void ComboBox::choose(unsigned id)
{
    mMainButton->setText(mChoices[id].substr(0,4)+".\\/");
    if(mCallback)
        mCallback(id);
    hideChoices();
}

void ComboBox::showChoices()
{
    sf::FloatRect m(INFRECT);
    m = rectUnion(m,mMainButton->bounds());
    mDeployed = true;
    for(SharedWidget& w : mBChoices)
    {
        w->show();
        m = rectUnion(m,w->bounds());
    }
    mBounds = m;
}

void ComboBox::hideChoices()
{
    mDeployed = false;
    for(SharedWidget& w : mBChoices)
        w->hide();
}
