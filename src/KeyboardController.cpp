#include "KeyboardController.h"

KeyboardController::KeyboardController()
{
}

void KeyboardController::update(float delta_s)
{
    constexpr float vr = 1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        getCharacter()->rot(vr*delta_s);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        getCharacter()->rot(-vr*delta_s);
}
