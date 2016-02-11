#include "Skin.h"
#include "Core.h"
#include "VecUtils.h"

Skin::Skin(sf::Texture* skinTex, sf::Texture *hatTex, int hatID, const AnimationSet& set)
    : mTexture(skinTex), mAnimationSet(set), mHatTex(hatTex)
{
    defaultAnimation();
    mHat.setTexture(*mHatTex);
    mBody.setTexture(*mTexture);
    mEyes.setTexture(*mTexture);
    mLFoot.setTexture(*mTexture);
    mRFoot.setTexture(*mTexture);
    mRHand.setTexture(*mTexture);
    mLHand.setTexture(*mTexture);
    if(hatID == -1)
        mHat.setTextureRect({0,0,0,0});
    else
        mHat.setTextureRect({48*hatID,0,48,48});
    mBody.setTextureRect({0,0,32,32}); //TODO modularize
    mLFoot.setTextureRect({0,32,16,16});
    mRFoot.setTextureRect({0,32,16,16});
    mEyes.setTextureRect({16,32,16,16});
    mRHand.setTextureRect({0,48,16,16});
    mLHand.setTextureRect({0,48,16,16});
    mLHand.setOrigin(8,4);
    mRHand.setOrigin(8,4);
    mLHand.setPosition(0,-12);
    mRHand.setPosition(0,-12);
    mBody.setOrigin(16,16);
    mHat.setOrigin(24,32);
    mLFoot.setOrigin(6,2);
    mRFoot.setOrigin(10,2);
    mLFoot.setPosition(0,-12);
    mRFoot.setPosition(0,-12);
    mEyes.setOrigin(-25,20);
    //mBody.setScale(0.9,0.9);
    //mEyes.setScale(0.9,0.9);
}

void Skin::setColor(sf::Color col)
{
    mBody.setColor(col);
    mRHand.setColor(col);
    mLHand.setColor(col);
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

bool Skin::inBody(const sf::Vector2f& p) const
{
    sf::Vector2f bodyCenter = getTransform().transformPoint(mBody.getPosition());
    float bodyRadiusS = 12*12; //TODO Deduce
    return lengthSquared(bodyCenter-p) < bodyRadiusS;
}

void Skin::drawBody(sf::RenderTarget &target, sf::RenderStates states) const
{
    float time = Core::get().time();
    if(mAnim)
    {
        mAnim->body(mHat,time);
        mAnim->body(mBody,time);
        mAnim->eyes(mEyes,time);
        mAnim->lfoot(mLFoot,time);
        mAnim->rfoot(mRFoot,time);
        mAnim->lhand(mLHand,time);
        mAnim->rhand(mRHand,time);
    }

    //Draw order
    target.draw(mLFoot,states);
    target.draw(mLHand,states);
    target.draw(mBody,states);
    target.draw(mEyes,states);
    target.draw(mHat,states);
    target.draw(mRFoot,states);
    target.draw(mRHand,states);
}

void Skin::setHat(int id)
{
    if(id == -1)
        mHat.setTextureRect({0,0,0,0});
    else
        mHat.setTextureRect({48*id,0,48,48});
}

Skin::~Skin()
{
    Core::get().textureCache().free(mTexture);
}
