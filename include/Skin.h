#ifndef SKIN_H
#define SKIN_H

#include <SFML/Graphics/Sprite.hpp>
#include "MathUtils.h"
#include <functional>
#include <map>


/**
 * @brief procedural skin animation using lambda function to animate sprites
 */
class Skin : public sf::Drawable, public sf::Transformable
{
public:
    /**
     * @brief an animation defined by one function for one sprite describing each transformation for each sprite
     */
    struct Animation{
        std::function<void(sf::Sprite& body, float time)> body; ///Body function
        std::function<void(sf::Sprite& lfoot, float time)> lfoot; ///left foot function
        std::function<void(sf::Sprite& rfoot, float time)> rfoot; ///right foot function
        std::function<void(sf::Sprite& lhand, float time)> lhand;
        std::function<void(sf::Sprite& rhand, float time)> rhand;
        std::function<void(sf::Sprite& eyes, float time)> eyes; ///eyes function
    };

    typedef std::map<std::string,Animation> AnimationSet; ///Type def for a set of animation

    /**
     * @brief construct skin with a sprite atlas texture and an animation set
     * @param skinTex
     * @param set
     */
    Skin(sf::Texture* skinTex, sf::Texture* hatTex, int hatID, const AnimationSet& set);

    /**
     * @brief return skin height
     * @return
     */
    float height(){return 32;}

    /**
     * @brief draw skin on given target
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /**
     * @brief load first animation in animation set
     */
    void defaultAnimation();

    /**
     * @brief set running animation by its name
     * @param name
     */
    void setAnimation(const std::string& name);

    /**
     * @brief get global bounds of the skin (bounds of the body transformed to global coordinates)
     * @return
     */
    sf::FloatRect getGlobalBounds() const;

    bool inBody(const sf::Vector2f& p) const;

    /**
     * @brief set Body and Hands color
     * @param col
     */
    void setColor(sf::Color col);
    ~Skin();
private:
    void drawBody(sf::RenderTarget& body,sf::RenderStates states) const;

    sf::Texture* mTexture;
    sf::Texture* mHatTex;
    mutable sf::Sprite mHat;
    mutable sf::Sprite mLFoot;
    mutable sf::Sprite mRFoot;
    mutable sf::Sprite mBody;
    mutable sf::Sprite mEyes;
    mutable sf::Sprite mLHand;
    mutable sf::Sprite mRHand;
    Animation* mAnim;
    AnimationSet mAnimationSet;
};
namespace Animations {
const Skin::AnimationSet basic{ ///Basic animation set
    {"idle", ///default idle animation
        {
            [](sf::Sprite& s,float t){s.setPosition(0,-14+stw(t)+2);},
            [](sf::Sprite& s,float t){s.setRotation(0);},
            [](sf::Sprite& s,float t){s.setRotation(0);},
            [](sf::Sprite& s,float t){s.setRotation(20);s.setPosition(8,stw(t-0.3)*0.5-12);},
            [](sf::Sprite& s,float t){s.setRotation(20);s.setPosition(-1,stw(t-0.3)*0.5-12);},
            [](sf::Sprite& s,float t){s.setPosition(-32,stw(t-0.1)*0.5);}
        }
    },
    {"walk", ///walk animation
        {
            [](sf::Sprite& s,float t){s.setPosition(0,-14+stw(t*3)+2);},
            [](sf::Sprite& s,float t){s.setRotation(stw(t*3)*90);},
            [](sf::Sprite& s,float t){s.setRotation(stw((t+0.5)*3)*90);},
            [](sf::Sprite& s,float t){s.setRotation(stw((t+0.5)*3)*90);s.setPosition(8,stw(t-0.3)*0.5-12);},
            [](sf::Sprite& s,float t){s.setRotation(stw(t*3)*90);s.setPosition(-1,stw(t-0.3)*0.5-12);},
            [](sf::Sprite& s,float t){s.setPosition(-32,stw(t-5+0.3)*0.5);}
        }
    },
    {"victory",
        {
            [](sf::Sprite& s,float t){s.setPosition(0,-14+stw(t*3)+2);},
            [](sf::Sprite& s,float t){s.setRotation(0);},
            [](sf::Sprite& s,float t){s.setRotation(0);},
            [](sf::Sprite& s,float t){s.setRotation(stw((t+0.5)*3)*90-90);s.setPosition(6,stw(t-0.3)*0.5-12);},
            [](sf::Sprite& s,float t){s.setRotation(stw(t*3)*90-90);s.setPosition(-3,stw(t-0.3)*0.5-12);},
            [](sf::Sprite& s,float t){s.setPosition(-32,stw(t-5+0.3)*0.5);}
        }
    }
};
}

#endif // SKIN_H
