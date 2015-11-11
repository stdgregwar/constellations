#include "KeyboardController.h"
#include <iostream>

using namespace std;

KeyboardController::KeyboardController(SharedCharacter c) : Controller(c)
{
}

bool KeyboardController::onEvent(const sf::Event& e)
{
    Action a;
    a.type = Action::NONE;
    constexpr float vr = 4;
    if(e.type == sf::Event::KeyPressed)
    {
        if(e.key.code == sf::Keyboard::Left)
            a.move.distance = -vr;
        if(e.key.code == sf::Keyboard::Right)
            a.move.distance = vr;

        cout << "Keypressed" << endl;
        a.type = Action::MOVE_X;
    }
    if(e.type == sf::Event::KeyReleased)
    {
        if(e.key.code == sf::Keyboard::Left)
            a.move.distance = +vr;
        if(e.key.code == sf::Keyboard::Right)
            a.move.distance = -vr;

        a.type = Action::MOVE_X;
        cout << "Keyreleased" << endl;
    }

    if(a.type != Action::NONE)
        character()->queueAction(a);
    return false;
}
