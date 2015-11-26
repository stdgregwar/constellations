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
        std::function<void(sf::Sprite& eyes, float time)> eyes; ///eyes function
    };

    typedef std::map<std::string,Animation> AnimationSet; ///Type def for a set of animation

    /**
     * @brief construct skin with a sprite atlas texture and an animation set
     * @param skinTex
     * @param set
     */
    Skin(sf::Texture* skinTex, const AnimationSet& set);

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

    /**
     * @brief set Body and Hands color
     * @param col
     */
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
const Skin::AnimationSet basic{ ///Basic animation set
    {"idle", ///default idle animation
        {
            [](sf::Sprite& s,float t){s.setPosition(0,stw(t)+2);}, ///Body up down
            [](sf::Sprite& s,float t){s.setRotation(0);}, ///No move
            [](sf::Sprite& s,float t){s.setRotation(0);}, ///No move
            [](sf::Sprite& s,float t){s.setPosition(-32,stw(t-0.3)*0.5);} ///Dephased eye up down
        }
    },
    {"walk", ///walk animation
        {
            [](sf::Sprite& s,float t){s.setPosition(0,stw(t*3)+2);}, ///Faster body up-down
            [](sf::Sprite& s,float t){s.setRotation(stw(t*3)*90);}, ///lfoot swing
            [](sf::Sprite& s,float t){s.setRotation(stw((t+0.5)*3)*90);}, ///rfoot swing
            [](sf::Sprite& s,float t){s.setPosition(-32,stw((t+0.3)*3)*0.5);} ///faster dephased eye up down
        }
    }
};
}

#endif // SKIN_H
