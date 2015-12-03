#include "Widget.h"

Widget::Widget(SharedWidget parent) : mParent(parent)
{
    if(parent)
        parent->add(shared_from_this());
}

void Widget::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(mVisible)
        for(auto c : mChildren) {
            sf::RenderStates s = states;
            s.transform *= c->getTransform();
            c->draw(target,s);
        }
}

void Widget::add(SharedWidget w)
{
    w->setParent(shared_from_this());
    w->show();
    mChildren.push_back(w);
}

SharedWidget Widget::add(Widget* w)
{
    SharedWidget sw(w);
    add(sw);
    return sw;
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

sf::Transform Widget::getFullTransform() const
{
    if(!mParent.expired())
    {
        SharedWidget sw(mParent);
        return sw->getFullTransform() * getTransform();
    }
    else
        return getTransform();
}

bool Widget::onEvent(const sf::Event& e, const sf::View& view)
{

}

bool Widget::pushEvent(const sf::Event &e, const sf::View& view){
    if(mVisible)
        for(auto c : mChildren) {
            c->onEvent(e,view);
            c->pushEvent(e,view);
        }
    return true;
}
