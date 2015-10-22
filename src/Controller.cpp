#include "../include/Controller.h"

Controller::Controller(SharedCharacter c) : mCharacter(c)
{

}

void Controller::setCharacter(SharedCharacter c)
{
    mCharacter = c;
}

SharedCharacter Controller::getCharacter()
{
    return mCharacter;
}
