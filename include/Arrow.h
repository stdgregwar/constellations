#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Planet.h"
#include "Controller.h"
#include "Character.h"
#include "Counter.h"

class Arrow;

typedef std::shared_ptr<Arrow> SharedArrow;

class StateConstellation;

typedef std::shared_ptr<StateConstellation> SConst;

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

    const sf::Vector2f& getPos();
    bool hasTimeOut() const;
    bool isPut() const;
    void setCallback(std::function<void()> callback);
    void onPut() const ;
    void onTimeOut() const;
private:
    bool lastMoments() const;
    void drawCursor(sf::RenderTarget& target, SConst& cstate) const;
    void drawCounter(sf::RenderTarget& target, SConst& cstate) const;
    PlayerID mOwnerID;
    sf::Vector2f mPos;
    sf::Vector2f mSpeed;
    mutable sf::Sprite mSprite;
    mutable sf::Sprite mCursor;
    sf::Texture mTexture;
    SharedPlanet mPlanet;
    float mPhi;
    float mTimeStamp;
    bool mPut;
    std::function<void()> mCallback;
    mutable Counter mCounter;
};

#endif //ARROW_H
