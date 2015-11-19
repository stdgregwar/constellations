#ifndef CHARACTER_H
#define CHARACTER_H

#include "Planet.h"
#include "Action.h"
#include "Path.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

class Character;

typedef std::shared_ptr<Character> SharedCharacter;
typedef unsigned PlayerID;

/**
 * @brief A character on top of a given planet
 */
class Character : public sf::Drawable
{
public:
    Character(SharedPlanet planet, const PlayerID& id, sf::Color color = sf::Color::White);
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

    void drawCursor(sf::RenderTarget &target, sf::RenderStates states) const;

    /**
     * @brief returns true if point p collides with character
     * @param p
     */
    bool collideWith(const sf::Vector2f& p) const;

    void queueAction(const Action& a);

    bool isDead() const;
    void hit(int pvs);
    const PlayerID& id() const;
    bool isVulnerable() const;

    virtual ~Character();
private:
    /**
     * @brief updates texture rect to animate sprite
     */
    void updateFrame() const;
    mutable sf::Sprite mSprite;
    SharedPlanet mPlanet;
    mutable int mFrame;
    sf::Vector2f mActionSpeed;
    bool mWalking;
    float mPhi;
    ActionQueue mActionQueue;
    bool mAiming;
    sf::Vector2f mArrowVec;
    sf::Vector2f mArrowStartingPoint;
    sf::Color mColor;
    int mPV;
    PlayerID mID;
    static Path mPath;
    mutable sf::Sprite mCursor;
    float mLastHitTime;
};

#endif // CHARACTER_H
