#ifndef PLANETSKIN_H
#define PLANETSKIN_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Sprite.hpp>

class PlanetSkin : public sf::Drawable
{
public:
    PlanetSkin(float radius);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    ~PlanetSkin();
private:
    void createHalo(float r, float R, const sf::Color& first, const sf::Color& second, int count = 32);
    sf::VertexArray mHalo;
    sf::Sprite mSprite;
};

#endif // PLANETSKIN_H
