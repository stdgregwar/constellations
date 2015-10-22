#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Character.h"

/**
 * @brief Interface specifying the controllers that drive the characters
 */
class Controller
{
public:
    Controller(SharedCharacter c = SharedCharacter());
    void setCharacter(SharedCharacter c);
    SharedCharacter getCharacter();

    /**
     * @brief Called each tick by the gamestate
     * @param delta_s
     */
    virtual void update(float delta_s) = 0;
private:
    SharedCharacter mCharacter;
};

#endif // CONTROLLER_H
