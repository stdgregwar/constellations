#ifndef CHARACTER_H
#define CHARACTER_H

#include "Planet.h"
#include "Action.h"
#include "Path.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

class Character;

typedef std::shared_ptr<Character> SharedCharacter;

/**
 * @brief A character on top of a given planet
 */
class Character : public sf::Drawable
{
public:
    Character(SharedPlanet planet, sf::Color color = sf::Color::White);
    Character(const Character& other);
    Character(const Character&& other);

    /**
     * @brief rotates the character on the planet by the given angle in radians
     * @param dphi
     */
    void rot(float dphi);

    /**
     * @brief set the angle of the character around the planet in radians
     * @param phi
     */
    void setPhi(float phi);

    /**
     * @brief update the position of the character relatively to the planet
     */
    void updatePos();

    /**
     * @brief called each tick by the gamestate to update the character
     * @param delta_s
     */
    void update(float delta_s);

    /**
     * @brief draw the character on the given rendertarget
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /**
     * @brief returns true if point p collides with character
     * @param p
     */
    bool collideWith(const sf::Vector2f& p) const;

    void queueAction(const Action& a);


private:

    /**
     * @brief updates texture rect to animate sprite
     */
    void updateFrame();
    sf::Sprite mSprite;
    SharedPlanet mPlanet;
    int mFrame;
    float mFrameTime;
    sf::Vector2f mActionSpeed;
    bool mWalking;
    sf::Texture mTex;
    float mPhi;
    ActionQueue mActionQueue;
    bool mAiming;
    sf::Vector2f mArrowVec;
    sf::Vector2f mArrowStartingPoint;
    sf::Color mColor;
    static Path mPath;
};

#endif // CHARACTER_H
