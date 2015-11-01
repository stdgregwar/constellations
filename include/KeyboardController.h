#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "Controller.h"

class KeyboardController : public Controller
{
public:
    KeyboardController();
    void update(float delta_s);
};

#endif // KEYBOARDCONTROLLER_H
