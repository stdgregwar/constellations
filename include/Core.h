#ifndef CORE_H
#define CORE_H

#include <SFML/Graphics.hpp>
#include <GameState.h>

class Core
{
public:
    Core();
    bool init(sf::Vector2u size = {1280,720});
    bool start();
    void update(float delta_s);
    void draw(sf::RenderTarget& target);
    static Core* get();
    void replaceState(SharedState state);
    SharedState popState();
    SharedState currentState();
    void pushState(SharedState state);
private:
    sf::RenderWindow mRenderWindow;
    static Core* mInstance;
    SharedState mStateStack;

};

#endif // CORE_H
