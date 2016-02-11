#include "BiButton.h"
#include  "Core.h"
#include "MathUtils.h"

BiButton::BiButton(const sf::FloatRect& bounds, std::function<void()> lc, std::function<void()> rc) : ProtoButton(lc,rc), mBounds(bounds), mRect(sf::Vector2f(mBounds.width,mBounds.height))
{
    mRect.setPosition(mBounds.left,mBounds.top);

}

void BiButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(hovered()) {
        mRect.setFillColor(sf::Color(48,48,48,stw(Core::get().time())*64+128));
        states.blendMode = sf::BlendAdd;
        target.draw(mRect,states);
    }
}

sf::FloatRect BiButton::bounds() const
{
    return Widget::getFullTransform().transformRect(mBounds);
}

