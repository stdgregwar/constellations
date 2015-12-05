#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <memory>
#include "Planet.h"
#include "Controller.h"
#include "Character.h"
#include "Counter.h"
#include "Trail.h"

class Arrow;

typedef std::shared_ptr<Arrow> SharedArrow;

class StateConstellation; //Parent state forward declaration

typedef std::shared_ptr<StateConstellation> SConst; //typedef of the above

class Arrow : public sf::Drawable
{
public:
    constexpr static float lifetime = 6;
    Arrow(const sf::Vector2f &pos, const sf::Vector2f &speed, const PlayerID& ownerID);
    Arrow(const Arrow& other);

    bool update(float delta_s);

    /**
    * @brief draw the arrow on the given rendertarget
    * @param target
    * @param states
    */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /**
     * @brief get the arrow position
     * @return
     */
    const sf::Vector2f& getPos() const;

    /**
     * @brief tells wether the arrow has liven more than lifetime
     * @return
     */
    bool hasTimeOut();

    /**
     * @brief is put
     * @return true if arrow is put in a planet
     */
    bool isPut() const;

    bool dead();

    /**
     * @brief setCallback
     * @param callback to be called if arrow is put or timedout
     */
    void setCallback(std::function<void()> callback);

    /**
     * @brief called when the arrow is put and call the callback
     */
    void onPut();

    /**
     * @brief called when the arrow time out and call the callback
     */
    void onTimeOut();
private:

    /**
     * @brief last moments
     * @return true if the arrow is 2s from time out
     */
    bool lastMoments() const;

    /**
     * @brief draw Cursor clamped on screen
     * @param target renderTarget
     * @param cstate the parent ConstellationState
     */
    void drawCursor(sf::RenderTarget& target, SConst& cstate) const;

    /**
     * @brief draw arrow countdown clamped on screen
     * @param target renderTarget
     * @param cstate the parent ConstellationState
     */
    void drawCounter(sf::RenderTarget& target, SConst& cstate) const;
    PlayerID mOwnerID;
    sf::Vector2f mPos;
    sf::Vector2f mSpeed;
    mutable sf::Sprite mSprite;
    mutable sf::Sprite mCursor;
    mutable Trail mTrail;
    SharedPlanet mPlanet;
    float mPhi;
    float mTimeStamp;
    bool mPut;
    bool mTimeOut;
    std::function<void()> mCallback;
    mutable Counter mCounter;
    static bool mSelfhit;

    //Sounds
    sf::Sound mSwiftSound;
    sf::Sound mPutSound;
    sf::Sound mWarnSound;
    sf::Sound mTouchSound;
    sf::Sound mThrowSound;
    sf::Sound mDeathSound;
};

#endif //ARROW_H
