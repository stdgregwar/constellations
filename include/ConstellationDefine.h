#ifndef CONSTELLATIONS_MAPSDEFINE_H
#define CONSTELLATIONS_MAPSDEFINE_H

#include <list>
#include "Controller.h"
#include "MathUtils.h"
struct PlanetDef
{
    sf::Vector3f pos;
    float mass;
    float radius;
    bool hasPlayer;
    float playerAngle;
};

struct ConstellationDef
{
    std::vector<PlanetDef> mPlanets;
    int maxNumberOfPlayers;
};

const std::vector<ConstellationDef> constellations = {
        {
                {
                        {{-300,-150, 0}, 0.5, 35, true, 180.f/TO_DEGREES},
                        {{300, 150, 0}, 0.5, 35, true, 0.f/TO_DEGREES},
                        {{0,0,0},2,20,false,0.f},
                        {{65,-70,0},2,30,false,0.f},
                        {{-65,70,0},2,35,false,0.f},
                }
                ,2
        },
        {
                {
                        {{300, 0, 0}, 0.75, 25, true, 0.f},
                        {{-300, 0, 0}, 0.75, 25, true, 180.f/TO_DEGREES},
                        {{0,100,0},5,60,true,90.f/TO_DEGREES},
                        {{0,-100,0},5,60,true,270.f/TO_DEGREES}
                }
                ,4
        }
};

#endif //CONSTELLATIONS_MAPSDEFINE_H
