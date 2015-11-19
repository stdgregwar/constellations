#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "Controller.h"
#include "Action.h"
#include <map>

typedef std::map<sf::Keyboard::Key, Action::ACTION_TYPE> KeyMapping;
typedef std::map<sf::Keyboard::Key, bool> KeysState;

/**
 * @brief Controller using keyboard event
 */
class KeyboardController : public Controller
{
public:
    KeyboardController(SharedCharacter c);
    bool onEvent(const sf::Event& e);
private:
    enum STATE
    {
        AIM,
        MOVE,
        WAITING
    };

    bool pressKey(sf::Keyboard::Key key);
    bool releaseKey(sf::Keyboard::Key key);

    STATE mState;
    sf::Vector2f mOldMousePos;
    sf::Vector2f mMousePos;
    KeysState mKeysState;
};

#endif // KEYBOARDCONTROLLER_H
