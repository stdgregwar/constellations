#include "../include/Skin.h"
#include "Core.h"

Skin::Skin(sf::Texture* skinTex, const AnimationSet& set)
    : mTexture(skinTex), mAnimationSet(set)
{
    defaultAnimation();
    mBody.setTexture(*mTexture);
    mEyes.setTexture(*mTexture);
    mLFoot.setTexture(*mTexture);
    mRFoot.setTexture(*mTexture);
    mBody.setTextureRect({0,0,32,32}); //TODO modularize
    mLFoot.setTextureRect({0,32,16,16});
    mRFoot.setTextureRect({0,32,16,16});
    mEyes.setTextureRect({16,32,16,16});
}

void Skin::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RenderStates s(getTransform());
    drawBody(target,s);
}

void Skin::defaultAnimation()
{
    if(mAnimationSet.size())
        mAnim = &mAnimationSet.begin()->second;
    else
        mAnim = nullptr;
}

void Skin::drawBody(sf::RenderTarget &target, sf::RenderStates states) const
{
    float time = Core::get().time();
    if(mAnim)
    {
        mAnim->body(mBody,time);
        mAnim->eyes(mEyes,time);
        mAnim->lFoot(mLFoot,time);
        mAnim->rFoot(mRFoot,time);
    }

    //Draw order
    target.draw(mLFoot);
    target.draw(mBody);
    target.draw(mEyes);
    target.draw(mRFoot);
}
