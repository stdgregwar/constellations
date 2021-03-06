#ifndef CROSSFADETRANSITION_H
#define CROSSFADETRANSITION_H

#include "Transition.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class CrossFadeTransition : public Transition
{
public:
    CrossFadeTransition(float duration);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    Transition::State update();
private:
    Transition::State mState;
    void setScreenColor(sf::Color c) const;
    mutable sf::VertexArray mScreen;
    float mDuration;
    float mStart;
    sf::Uint8 mTargetAlpha;
};

#endif // CROSSFADETRANSITION_H
