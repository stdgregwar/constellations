#include "ProtoButton.h"
#include "Core.h"

ProtoButton::ProtoButton(std::function<void()> lc, std::function<void()> rc)
    : mRCallback(rc), mLCallback(lc)
{
}

void ProtoButton::Rtrigger()
{
    if(mRCallback)
        mRCallback();
}

void ProtoButton::Ltrigger()
{
    if(mLCallback)
        mLCallback();
}

bool ProtoButton::onEvent(const sf::Event& e, const sf::View &view)
{
    switch(e.type)
    {
        case sf::Event::MouseButtonReleased:
        {
            sf::Vector2f mapPos = Core::get().renderWindow().mapPixelToCoords({e.mouseButton.x,e.mouseButton.y},view);
            if(bounds().contains(mapPos))
                (e.mouseButton.button == sf::Mouse::Button::Right) ? Rtrigger() : Ltrigger();
            break;
        }
        case sf::Event::MouseMoved:
        {
            sf::Vector2f mapPos = Core::get().renderWindow().mapPixelToCoords({e.mouseMove.x,e.mouseMove.y},view);
            setHovered(bounds().contains(mapPos));
            break;
        }
    }
}
