#ifndef SKIN_H
#define SKIN_H

#include <SFML/Graphics/Sprite.hpp>
#include "MathUtils.h"
#include <functional>
#include <map>



class Skin : public sf::Drawable, public sf::Transformable
{
public:
    struct Animation{
        std::function<void(sf::Sprite& body, float time)> body;
        std::function<void(sf::Sprite& lfoot, float time)> lfoot;
        std::function<void(sf::Sprite& rfoot, float time)> rfoot;
        std::function<void(sf::Sprite& eyes, float time)> eyes;
    };

    typedef std::map<std::string,Animation> AnimationSet;

    Skin(sf::Texture* skinTex, const AnimationSet& set);
    float height(){return 32;}
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void defaultAnimation();
    void setAnimation(const std::string& name);
    sf::FloatRect getGlobalBounds() const;
    void setColor(sf::Color col);
    ~Skin();
private:
    void drawBody(sf::RenderTarget& body,sf::RenderStates states) const;

    sf::Texture* mTexture;
    mutable sf::Sprite mLFoot;
    mutable sf::Sprite mRFoot;
    mutable sf::Sprite mBody;
    mutable sf::Sprite mEyes;
    Animation* mAnim;
    AnimationSet mAnimationSet;
};
namespace Animations {
const Skin::AnimationSet basic{
    {"idle",
        {
            [](sf::Sprite& s,float t){s.setPosition(0,stw(t)+2);},
            [](sf::Sprite& s,float t){s.setRotation(0);},
            [](sf::Sprite& s,float t){s.setRotation(0);},
            [](sf::Sprite& s,float t){s.setPosition(-32,stw(t-0.3)*0.5);}
        }
    },
    {"walk",
        {
            [](sf::Sprite& s,float t){s.setPosition(0,stw(t*3)+2);},
            [](sf::Sprite& s,float t){s.setRotation(stw(t*3)*90);},
            [](sf::Sprite& s,float t){s.setRotation(stw((t+0.5)*3)*90);},
            [](sf::Sprite& s,float t){s.setPosition(-32,stw(t-5+0.3)*0.5);}
        }
    }
};
}

#endif // SKIN_H