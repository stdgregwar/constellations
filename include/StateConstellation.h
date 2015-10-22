#ifndef STATECONSTELLATION_H
#define STATECONSTELLATION_H

#include "GameState.h"
#include "Character.h"
#include "Planet.h"
#include <list>

/**
 * @brief The main state of the game where the gameplay happends
 */
class StateConstellation : public GameState
{
public:
    StateConstellation();
    void onBegin();
    void onEnd();
    void onResume();
    void onPause();
    void draw(sf::RenderTarget& target);
    void update(float delta_s);
private:
    std::list<SharedPlanet> mPlanets;
    std::list<SharedCharacter> mCharacters;
};

#endif // STATECONSTELLATION_H
