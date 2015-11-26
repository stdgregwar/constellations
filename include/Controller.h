#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Character.h"
#include <memory>

class Controller;
typedef std::shared_ptr<Controller> SharedController;
/**
 * @brief Interface specifying the controllers that drive the characters
 */
class Controller
{
public:
    Controller(SharedCharacter c);

    /**
     * @brief called with events of the window
     * @param e sfml event forwarded from window
     * @return bool if it want to end it's turn
     */
    virtual bool onEvent(const sf::Event& e) = 0;

    /**
     * @brief give the character associated to this controller
     * @return a character
     */
    SharedCharacter character();

    /**
     * @brief give the player ID of this controller
     * @return a player ID
     */
    const PlayerID& id();
private:
    SharedCharacter mCharacter;
};

#endif // CONTROLLER_H
