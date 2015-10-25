#ifndef STATECONSTELLATION_H
#define STATECONSTELLATION_H

#include "GameState.h"
#include "Character.h"
#include "Planet.h"
#include "Arrow.h"
#include <list>

class StateConstellation;
typedef std::shared_ptr<StateConstellation> SharedStateConstellation;
/**
 * @brief The main state of the game where the gameplay happends
 */
class StateConstellation : public GameState
{
public:
    StateConstellation();

    /**
     * @brief Setups the scene and add game actors (planets and characters)..
     */
    void onBegin();


    void onEnd();
    void onResume();
    void onPause();
    void draw(sf::RenderTarget& target);
    void update(float delta_s);

    sf::Vector2f getGravFieldAt(const sf::Vector2f &p);
    SharedPlanet collideWithPlanet(const sf::Vector2f &p);
    SharedCharacter collideWithCharacter(const sf::Vector2f &p);
private:
    std::list<SharedPlanet> mPlanets;
    std::list<SharedCharacter> mCharacters;
    std::list<SharedArrow> mArrows;
};

#endif // STATECONSTELLATION_H
