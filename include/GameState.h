#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <memory>

class GameState;

typedef std::shared_ptr<GameState> SharedState;

class GameState
{
public:
    GameState(SharedState parent);
    virtual void onBegin() = 0;
    virtual void onEnd() = 0;
    virtual void onResume() = 0;
    virtual void onPause() = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    virtual void update(float delta_s) = 0;
    void setChild(SharedState state);
    void setParent(SharedState state);
    SharedState parent();
    SharedState child();
private:
    SharedState mParent;
    SharedState mChild;
};


#endif // GAMESTATE_H
