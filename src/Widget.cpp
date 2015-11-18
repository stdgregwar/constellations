#include "Widget.h"

Widget::Widget(SharedWidget parent) : mParent(parent)
{
    if(parent)
        parent->add(shared_from_this());
}

void Widget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(mVisible)
        for(auto c : mChildren)
            c->draw(target,states);
}

void Widget::add(SharedWidget w)
{
    w->setParent(shared_from_this());
    w->show();
    mChildren.push_back(w);
}

void Widget::add(Widget* w)
{
    add(SharedWidget(w));
}

void Widget::setParent(SharedWidget w)
{
    mParent = w;
}

void Widget::show()
{
    mVisible = true;
    for(auto c : mChildren)
        c->show();
}

void Widget::hide()
{
    mVisible = false;
    for(auto c : mChildren)
        c->hide();
}

Widgets& Widget::children()
{
    return mChildren;
}

bool Widget::visible()
{
    return mVisible;
}

bool Widget::onEvent(const sf::Event& e)
{

}

bool Widget::pushEvent(const sf::Event &e){
    if(mVisible)
        for(auto c : mChildren) {
            c->onEvent(e);
            c->pushEvent(e);
        }
    return true;
}
