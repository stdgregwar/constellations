#ifndef CORE_H
#define CORE_H

#include <SFML/Graphics.hpp>
#include <GameState.h>
#include <list>
#include <random>
#include "Properties.h"
#include "ResourceCache.h"
#include "Timer.h"
#include "Transition.h"
#include "SoundManager.h"
#include "NetworkManager.h"

/**
 * @brief Main application class representing the whole game logic with a StateStack. Singleton class.
 */
class Core
{
    friend class Timer; //For auto timer adding
public:
    Core();
    /**
      * @brief Inits the engine with screen resolution
      */
    bool init(sf::Vector2u size = {1280,720});

    /**
     * @brief Starts the engine
     * @return
     */
    bool start();

    /**
     * @brief the heart beat of the game. Called in the main while loop.
     * @param delta_s
     */
    void update(float delta_s);

    /**
     * @brief call every draw function of the StateStack
     * @param target a rendertarget
     */
    void draw(sf::RenderTarget& target);

    /**
     * @brief get the single instance of the core. Everywhere.
     * @return
     */
    static Core& get();

    /**
     * @brief Put a new state in place of the current one
     * @param state
     */
    void replaceState(SharedState state, Transition* t = nullptr);

    /**
     * @brief popState and resume the previous one, exiting if none
     * @return
     */
    SharedState popState(Transition* t = nullptr);

    /**
     * @brief pop state on next tick
     * @return
     */
    SharedState delayedPop(Transition* t = nullptr);

    /**
     * @brief get currentState
     * @return
     */
    SharedState currentState();

    /**
     * @brief Pushes a new state on the stack, keeping the older ones and keeping drawing them
     * @param state
     */
    void pushState(SharedState state, Transition* t = nullptr);

    /**
     * @brief pop all states and close the window
     */
    void endGame();

    /**
     * @brief return global timer
     * @return global timer
     */
    float time();

    /**
     * @brief last delta_t (without substeps) of simulation
     * @return delta_t
     */
    float lastDt();

    /**
     * @brief return aspect ratio of the window
     * @return aspect ratio
     */
    float aspectRatio();

    /**
     * @brief get const view of renderwindow
     * @return
     */
    const sf::RenderWindow& renderWindow();

    /**
     * @brief stretch time with given factor duration time
     * @param factor factor of stretching (>1 is faster, <1 is slower)
     * @param duration time during which the time is stretch (in seconds)
     * @return
     */
    float timeStretch(float factor, float duration);

    /**
     * @brief tells if the Core is time stretching
     * @return true if core is stretching
     */
    bool isStretchin();

    /**
     * @brief gives current time factor (time stretch factor)
     * @return time factor
     */
    float timeFactor();


    ///Getters of managers///

    /**
     * @brief get the global dictionnary of the core
     * @return dict
     */
    Properties& globalDict();

    /**
     * @brief get the texture ResourceCache
     * @return tex cache
     */
    TextureCache& textureCache();

    /**
     * @brief get the font ResourceCache
     * @return font cache
     */
    FontCache& fontCache();

    /**
     * @brief get the sound buffer ResourceCache
     * @return soundBufferCache
     */
    SoundBufferCache& soundBufferCache();

    SoundManager& soundMgr();

    unsigned int randomSeed();
private:
    static constexpr float basic_dt = 1/60.f;

    /**
     * @brief add a timer to the core, only used by the friend class timer
     * @param timer
     * @return
     */
    float addTimer(SharedTimer timer);

    /**
     * @brief update timers
     */
    void tickTimers();

    /**
     * @brief pop states scheduled (pop top n states)
     */
    void popScheduled();

    void setTransition(Transition* t);

    TextureCache mTextureCache;
    FontCache mFontCache;
    SoundBufferCache mSoundBufferCache;
    sf::RenderWindow mRenderWindow;
    float mGlobalTime;
    float mLastDt;
    float mTimeFactor;
    float mTargetFactor;
    static Core* mInstance;
    SharedState mStateStack;
    Properties mGlobalDict;
    int mScheduledPops;
    std::list<SharedTimer> mTimers;
    Transition* mTransition;
    Transition* mScheduledTransition;
    SharedState mFromTransition;
    SoundManager mSoundManager;
    NetworkManager mNetworkManager;
    std::random_device rd;
};

#endif // CORE_H
