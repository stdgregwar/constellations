#ifndef STATECONSTELLATION_H
#define STATECONSTELLATION_H

#include "GameState.h"
#include "Character.h"
#include "Planet.h"
#include "Controller.h"
#include "Arrow.h"
#include "StaticParticles.h"
#include "DynamicParticles.h"
#include <list>
#include <vector>

class StateConstellation;
typedef std::shared_ptr<StateConstellation> SharedStateConstellation;
typedef void (StateConstellation::*UpdateFunc)(float); //Ptr on method update, conform to all method with same signature
typedef void (StateConstellation::*EventFunc)(const sf::Event& e); //Ptr on event handler method
/**
 * @brief The main state of the game where the gameplay happends
 */
class StateConstellation : public GameState
{
public:
    StateConstellation();

    /**
     * @brief //Struct representing internal state. One update method and one event method
     *
     * Used to make a tiny-statemachine inside the ConstellationState
     */
    struct InternalState
    {
        UpdateFunc uf;
        EventFunc ef;
    };

    /**
     * @brief Setups the scene and add game actors (planets and characters)..
     */
    void onBegin();
    void onEnd();
    void onResume();
    void onPause();
    void draw(sf::RenderTarget& target);
    void update(float delta_s);
    void pushEvent(const sf::Event& e);

    //Updates methods
    void rotUpdate(float delta_s);
    void defaultUpdate(float delta_s);

    //Events methods
    void rotEvent(const sf::Event& e);
    void waitingEvent(const sf::Event &e);
    void defaultEvent(const sf::Event& e);

    /**
     * @brief get vectorial gravitational field at given point p
     * @param p point to sample grav field
     * @return grav field
     */
    sf::Vector2f getGravFieldAt(const sf::Vector2f &p) const;

    /**
     * @brief check wether a given point is in a planet
     * @param p point
     * @return nullptr or the first planet colliding with point
     */
    SharedPlanet collideWithPlanet(const sf::Vector2f &p) const;

    /**
     * @brief check wether a given point is in a character
     * @param p point
     * @return nullptr or the first intersected character
     */
    SharedCharacter collideWithCharacter(const sf::Vector2f &p) const;

    /**
     * @brief add arrow to the state
     * @param a
     */
    void pushArrow(SharedArrow a, bool addCallback = true);

    /**
     * @brief called when the Player iterator return on the first player
     */
    void onNewRound();

    /**
     * @brief called when a player win (alone in player pool)
     */
    void onWin(SharedController winner);

    //Seems very improbable to be called
    /**
     * @brief should never be called except on a draw with simultaneous death (never in fact)
     */
    void onEquality();

    /**
     * @brief increments player iterator to next player
     */
    void nextPlayer();

    /**
     * @brief isCurrentPlayer
     * @param id
     * @return true if the given player ID is the same as player in player iterator
     */
    bool isCurrentPlayer(const PlayerID& id)  const;

    /**
     * @brief called by arrows when they put in a planet or when they time out
     */
    void onArrowDecayed();

    /**
     * @brief return a vector of points that would follow an arrow if thrown with given initials conditions
     * @param pos position
     * @param speed speed
     * @param precision max pts count
     * @return vector of points
     */
    std::vector<sf::Vector2f> pathForInitials(sf::Vector2f pos, sf::Vector2f speed, int precision) const;

    /**
     * @brief return the bound of the constellation with given margin
     * @param margin margin
     * @return
     */
    sf::FloatRect getBounds(float margin = 0) const;

    /**
     * @brief return the amount of zoom of the mainView
     * @return
     */
    float zoomFactor() const;

    /**
     * @brief return the top-left point of the given rect after constraining it in the View
     * @param rect a rect
     * @param margin a margin
     * @return
     */
    sf::Vector2f clampRect(const sf::FloatRect& rect, float margin = 5) const;
private:

    /**
     * @brief correct views ratio and zoom with respect to render target
     * @param vx
     * @param vy
     */
    void correctViews(float vx, float vy);

    typedef std::list<SharedController> Players;
    typedef std::vector<SharedArrow> Arrows;

    InternalState mIState;
    sf::Vector2i mOldMousePos;
    sf::Vector2i mMousePos;
    float mYaw;
    float mPitch;

    std::list<SharedPlanet> mPlanets;
    Players mPlayers;
    Players::iterator mCurrentPlayer;
    Arrows mArrows;
    StaticParticles mBackground;
    DynamicParticles mExpl;
    sf::View mView;
    sf::View mBackView;

    sf::Sound mExplLow;
    sf::Sound mExplHigh;
};

#endif // STATECONSTELLATION_H
