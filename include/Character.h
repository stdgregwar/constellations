#ifndef CHARACTER_H
#define CHARACTER_H

#include "Planet.h"
#include "Action.h"
#include "Path.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include "Skin.h"

class Character;

typedef std::shared_ptr<Character> SharedCharacter;
typedef unsigned PlayerID;

/**
 * @brief A character on top of a given planet
 */
class Character : public sf::Drawable
{
public:
    Character(SharedPlanet planet, const PlayerID& id, sf::Color color = sf::Color::White, float phi = 0.f, int hatID = 0);
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
     * @brief draw the character (and if current player its cursor) on the given rendertarget
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /**
     * @brief returns true if point p collides with character
     * @param p
     */
    bool collideWith(const sf::Vector2f& p) const;
    /**
    * @brief Add given action to character's action queue
    * @param a Action to queue
    */
    void queueAction(const Action& a);

    /**
     * @brief Return true if character is dead
     */
    bool isDead() const;
    /**
     * @brief Reduces characters HP from given amounts
     * @param pvs Amount of HP to remove
     */
    void hit(int pvs);
    /**
     * @brief Give the id of the player
     */
    const PlayerID& id() const;
    /**
     * @brief Return true if character is vulnerable
     */
    bool isVulnerable() const;

    /**
     * @brief Return the bounds of the character
     */
    sf::FloatRect getBounds() const;

    const Skin& skin(){return mSkin;}

    virtual ~Character();
private:
    /**
     * @brief updates texture rect to animate sprite
     */
    void updateFrame() const;

    /**
     * @brief draw a cursor above the character on the given rendertarget
     * @param target
    * @param states
     */
    void drawCursor(sf::RenderTarget &target, sf::RenderStates states) const;
    mutable Skin mSkin;
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
