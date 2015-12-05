#include <KeyboardController.h>
#include "Constellation.h"

Constellation::Constellation() { }

void Constellation::buildFromConstellationDef(const ConstellationDef& constellationDef, int numberOfPlayers)
{
    int tempNumberOfPlayers = numberOfPlayers;
    int currentPlayerNumber = 0;
    for(PlanetDef planet : constellationDef.mPlanets)
    {
        mPlanets.push_back(SharedPlanet(new Planet(planet.pos,planet.mass,planet.radius)));
        if(planet.hasPlayer && tempNumberOfPlayers > 0)
        {
            tempNumberOfPlayers--;
            mPlayers.push_back(SharedController( //Ugliest in-place construction ever
                    new KeyboardController(
                            SharedCharacter(
                                    new Character(
                                            mPlanets.back(),
                                            currentPlayerNumber,
                                            mColorPool[currentPlayerNumber%mColorPool.size()],
                                            (planet.playerAngle-90.f)/TO_DEGREES,
                                            tempNumberOfPlayers //Hat ID TODO : randomize
                                    )
                            )
                    )
            )
            );
            currentPlayerNumber++;
        }
    }
}

std::list<SharedPlanet> Constellation::getPlanets()
{
    return mPlanets;
}

Players Constellation::getPlayers()
{
    return mPlayers;
}

