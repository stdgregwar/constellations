#ifndef STATETITLESCREEN_H
#define STATETITLESCREEN_H

#include <GameState.h>
#include "StaticParticles.h"
#include "DynamicParticles.h"
#include "Widget.h"
#include <SFML/Audio/Music.hpp>
#include "FlatMusic.h"
#include "Camera.h"
#include "NetworkManager.h"
#include "Skin.h"

class StateTitleScreen : public GameState, public NetworkManager::Receiver
{
public:
    enum Mode{
        NONE,
        PLAYER,
        BOT,
        ONLINE
    };

    StateTitleScreen();
    /**
     * @brief Called back when the state is pushed on the stack. Used for state initialization.
     */
    virtual void onBegin();

    /**
     * @brief Called back when the state is poped from the stack. Used for state cleaning.
     */
    virtual void onEnd();

    /**
     * @brief Called back when the state is on the top again.
     */
    virtual void onResume();

    /**
     * @brief Called back when the state is shadowed by another state.
     */
    virtual void onPause();

    /**
     * @brief Called on the render tick
     * @param target
     */
    virtual void draw(sf::RenderTarget& target);

    /**
     * @brief Called on the game tick
     * @param delta_s
     */
    virtual void update(float delta_s);

    /**
     * @brief every event is passed to the current state trough this method
     * @param e
     */
    virtual void pushEvent(const sf::Event & e);

    /**
     * @brief launch the playing state
     */
    void launchStateConstellation();

    /**
     * @brief set player count in global dict's property with key "player_count"
     * @param count
     */
    void setPlayerCount(int count);

    /**
     * @brief set players pv's in global dict's property with key "player_pv"
     * @param pv
     */
    void setPlayerPv(int pv);

    void setHint(bool set);

    void setSelfHit(bool set);

    void initNetworking();

    /**
     * @brief set control mode of given slot
     * @param n
     * @param id
     */
    void setSlotMode(int n, int mode);

    void rollSlotColor(int n);

    void rollSlotHat(int n);

    void onReceive(const j::Value &message);
private:

    struct Slot
    {
        Mode mode;
        int hatId;
        int colorId;
        Skin skin;
    };

    sf::Sprite mTitle;
    StaticParticles mBackground;
    SharedWidget mMainWidget;
    SharedWidget mMenuWidget;
    SharedWidget mMatchMakingWidget;

    Slot mSlots[5];

    Camera mView;
    SharedMusic mMusic;
};

#endif // STATETITLESCREEN_H
