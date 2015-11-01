#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <memory>

class GameState;

typedef std::shared_ptr<GameState> SharedState;

/**
 * @brief Interface representing a gamestate. i.e. One of the games phases : Menu,Splash,loading,Playing,Exiting etc..
 */
class GameState
{
public:
    GameState();
    /**
     * @brief Called back when the state is pushed on the stack. Used for state initialization.
     */
    virtual void onBegin() = 0;

    /**
     * @brief Called back when the state is poped from the stack. Used for state cleaning.
     */
    virtual void onEnd() = 0;

    /**
     * @brief Called back when the state is on the top again.
     */
    virtual void onResume() = 0;

    /**
     * @brief Called back when the state is shadowed by another state.
     */
    virtual void onPause() = 0;

    /**
     * @brief Called on the render tick
     * @param target
     */
    virtual void draw(sf::RenderTarget& target) = 0;

    /**
     * @brief Called on the game tick
     * @param delta_s
     */
    virtual void update(float delta_s) = 0;

    /**
     * @brief Set child state
     * @param state
     */
    void setChild(SharedState state);

    /**
     * @brief get child state
     * @return
     */
    SharedState child();

    /**
     * @brief Helper method used to go down all the states and drawing them in ascendent order
     * @param target
     */
    void drawAll(sf::RenderTarget& target);

    /**
     * @brief state wether this state should be displayed or not
     * @param b
     */
    void setVisible(bool b);

    /**
     * @brief return if the state should be displayed
     * @return
     */
    bool isVisible();

    /**
     * @brief every event is passed to the current state trough this method
     * @param e
     */
    virtual void pushEvent(const sf::Event & e) = 0;
private:
    bool mVisible;
    SharedState mChild;
};


#endif // GAMESTATE_H
