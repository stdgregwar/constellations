#ifndef CONSTELLATIONS_CONSTELLATION_H
#define CONSTELLATIONS_CONSTELLATION_H

#include "Planet.h"
#include "Controller.h"
#include "ConstellationDefine.h"
#include <list>

class Constellation;
typedef std::list<SharedController> Players;
/**
 * @brief utility class for building a constellation (map) from a constellationDef
 */
class Constellation {
public:
    Constellation();
    /**
     * @brief Build constellation from given constellationDef and add given number of players (be careful that constellationDef has room for all players)
     * @param constellationDef ConstellationDef that will be used to build a new constellation
     * @param numberOfPlayers Number of players to be added
     */
    void buildFromConstellationDef(const ConstellationDef &constellationDef, int numberOfPlayers);
    /**
     * @brief returns a List of players built previously
     */
    Players getPlayers();
    /**
     * @brief returns a List of planets built previously
     */
    std::list<SharedPlanet> getPlanets();
private:
    std::list<SharedPlanet> mPlanets;
    Players mPlayers;
    //TODO add colors
    const std::vector<sf::Color> mColorPool = {
            sf::Color(255,150,150),
            sf::Color(150,150,255),
            sf::Color(150,255,200),
            sf::Color(255,255,150)
    };
};


#endif //CONSTELLATIONS_CONSTELLATION_H
