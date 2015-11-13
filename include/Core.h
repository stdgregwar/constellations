#ifndef CORE_H
#define CORE_H

#include <SFML/Graphics.hpp>
#include <GameState.h>
#include "Properties.h"

/**
 * @brief Main application class representing the whole game logic with a StateStack. Singleton class.
 */
class Core
{
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
    void replaceState(SharedState state);

    /**
     * @brief popState and resume the previous one, exiting if none
     * @return
     */
    SharedState popState();

    /**
     * @brief get currentState
     * @return
     */
    SharedState currentState();

    /**
     * @brief Pushes a new state on the stack, keeping the older ones and keeping drawing them
     * @param state
     */
    void pushState(SharedState state);

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
     * @brief return aspect ratio of the window
     * @return aspect ratio
     */
    float aspectRatio();

    /**
     * @brief get const view of renderwindow
     * @return
     */
    const sf::RenderWindow& renderWindow();

    Properties& globalDict();
private:
    sf::RenderWindow mRenderWindow;
    float mGlobalTime;
    static Core* mInstance;
    SharedState mStateStack;
    Properties mGlobalDict;
};

#endif // CORE_H
