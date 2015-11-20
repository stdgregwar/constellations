#ifndef CONSTELLATIONS_CONSTELLATION_H
#define CONSTELLATIONS_CONSTELLATION_H

#include "Planet.h"
#include "Controller.h"
#include "ConstellationDefine.h"
#include <list>

class Constellation;
typedef std::list<SharedController> Players;

class Constellation {
public:
    Constellation();
    void buildFromConstellationDef(ConstellationDef constellationDef, int numberOfPlayers);
    Players getPlayers();
    std::list<SharedPlanet> getPlanets();
private:
    std::list<SharedPlanet> mPlanets;
    Players mPlayers;
    const std::vector<sf::Color> mColorPool = {
            sf::Color(255,150,150),
            sf::Color(150,150,255),
            sf::Color(150,255,200),
            sf::Color(255,255,150)
    };
};


#endif //CONSTELLATIONS_CONSTELLATION_H
