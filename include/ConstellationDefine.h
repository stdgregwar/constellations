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
/**
 *
 * You can define constellations with a list of planet and a max number of players
 *
 * Planet definition :
 * {{x,y,z},gravField,radius,canHavePlayer,angle (in degrees, relative to planet)}
 */
const std::vector<ConstellationDef> constellations = {
        {
                {
                        {{-200,-150, 0}, 0.5, 35, true, 270.f},
                        {{200, 150, 0}, 0.5, 35, true, 90.f},
                        {{0,0,0},2,20,false,0.f},
                        {{65,-70,0},2,30,false,0.f},
                        {{-65,70,0},2,35,false,0.f},
                }
                ,2
        },
        {
                {
                        {{300, 25, 0}, 0.75, 25, true, 90.f},
                        {{-300, -40, 0}, 0.75, 25, true, 270.f},
                        {{15,135,0},2.5,60,true,180.f},
                        {{-20,-85,0},2.5,60,true,0.f}
                }
                ,4
        },
        {
            {
                {{-250, -10, 0}, 0.75, 30, true, 315.f},
                {{250, 10, 0}, 0.75, 30, true, 135.f},
                {{-50,-150,0},25,25,false,0.f},
                {{50,150,0},25,25,false,0.f},
            }
            ,2
        },
        {
                {
                        {{-200, -150, 0}, 0.75, 25, true, 315.f},
                        {{200, 150, 0}, 0.75, 25, true, 135.f},
                        {{-200,150,0},0.75,25,true,225.f},
                        {{200,-150,0},0.75,25,true,45.f},
                        {{0,0,0},20,75,false,0.f}
                }
                ,4
        },
        {
                {
                        {{-150, -20, 0}, 0.75, 25, true, 315.f},
                        {{25, 110, 0}, 0.75, 25, true, 135.f},
                        {{50,-150,0},0.75,25,true,45.f},
                        {{50,40,0},2,30,false,0.f},
                        {{-35,80,0},3.5,15,false,0.f},
                        {{60,-40,0},1.75,20,false,0.f},
                        {{-45,-80,0},4.75,45,false,0.f}
                }
                ,3
        }
};

#endif //CONSTELLATIONS_MAPSDEFINE_H
