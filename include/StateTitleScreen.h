#ifndef STATETITLESCREEN_H
#define STATETITLESCREEN_H

#include <GameState.h>
#include "StaticParticles.h"
#include "Widget.h"

class StateTitleScreen : public GameState
{
public:
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

    void launchStateConstellation();

    void setPlayerCount(int count);

    void setPlayerPv(int pv);

private:
    sf::Font mTitleFont;
    sf::Font mFont;
    sf::Text mTitle;
    sf::Text mExitText;
    StaticParticles mBackground;
    SharedWidget mMainWidget;
    sf::View mView;
};

#endif // STATETITLESCREEN_H
