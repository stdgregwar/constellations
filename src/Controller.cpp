#include "../include/Controller.h"

Controller::Controller(SharedCharacter c) : mCharacter(c)
{

}

SharedCharacter Controller::character()
{
    return mCharacter;
}
