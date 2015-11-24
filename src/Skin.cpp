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
    mBody.setOrigin(16,32);
    mLFoot.setOrigin(6,2);
    mRFoot.setOrigin(10,2);
    mLFoot.setPosition(0,-12);
    mRFoot.setPosition(0,-12);
    mEyes.setOrigin(-32,26);
    mBody.setScale(0.9,0.9);
    mEyes.setScale(0.9,0.9);
}

void Skin::setColor(sf::Color col)
{
    mBody.setColor(col);
}

void Skin::setAnimation(const std::string& name)
{
    AnimationSet::iterator it = mAnimationSet.find(name);
    if(it!=mAnimationSet.end())
        mAnim = &it->second;
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

sf::FloatRect Skin::getGlobalBounds() const
{
    return getTransform().transformRect(mBody.getGlobalBounds());
}

void Skin::drawBody(sf::RenderTarget &target, sf::RenderStates states) const
{
    float time = Core::get().time();
    if(mAnim)
    {
        mAnim->body(mBody,time);
        mAnim->eyes(mEyes,time);
        mAnim->lfoot(mLFoot,time);
        mAnim->rfoot(mRFoot,time);
    }

    //Draw order
    target.draw(mLFoot,states);
    target.draw(mBody,states);
    target.draw(mEyes,states);
    target.draw(mRFoot,states);
}

Skin::~Skin()
{
    Core::get().textureCache().free(mTexture);
}
