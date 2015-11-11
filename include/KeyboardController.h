#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "Controller.h"
#include "Action.h"
#include <map>

typedef std::map<sf::Keyboard::Key, Action::ACTION_TYPE> KeyMapping;

/**
 * @brief Controller using keyboard event
 */
class KeyboardController : public Controller
{
public:
    KeyboardController(SharedCharacter c);
    bool onEvent(const sf::Event& e);
};

#endif // KEYBOARDCONTROLLER_H
