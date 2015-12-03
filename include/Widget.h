#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <memory>
#include <vector>

class Widget;
typedef std::shared_ptr<Widget> SharedWidget;
typedef std::weak_ptr<Widget> WeakWidget;
typedef std::vector<SharedWidget> Widgets;
class Widget : public std::enable_shared_from_this<Widget>, public sf::Drawable, public sf::Transformable
{
public:
    Widget(SharedWidget parent = SharedWidget());
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void add(SharedWidget w);
    SharedWidget add(Widget* w);
    virtual void show();
    void hide();
    Widgets& children();
    virtual bool onEvent(const sf::Event& e, const sf::View& view);
    bool pushEvent(const sf::Event& e, const sf::View &view);
    bool visible();
    sf::Transform getFullTransform() const;
private:
    void setParent(SharedWidget w);
    bool mVisible;
    Widgets mChildren;
    WeakWidget mParent;
};

#endif // WIDGET_H
