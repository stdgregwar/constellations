#ifndef SKIN_H
#define SKIN_H

#include <SFML/Graphics/Sprite.hpp>
#include "MathUtils.h"
#include <map>
#include "SkinAnimation.h"

typedef std::map<std::string,SkinAnimation> AnimationSet;

class Skin : public sf::Drawable, public sf::Transformable
{

public:
    Skin(sf::Texture* skinTex, const AnimationSet& set);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void defaultAnimation();
private:
    void drawBody(sf::RenderTarget& body,sf::RenderStates states) const;

    sf::Texture* mTexture;
    mutable sf::Sprite mLFoot;
    mutable sf::Sprite mRFoot;
    mutable sf::Sprite mBody;
    mutable sf::Sprite mEyes;
    SkinAnimation* mAnim;
    AnimationSet mAnimationSet;
};

#endif // SKIN_H
