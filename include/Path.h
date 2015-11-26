#ifndef CONSTELLATIONS_PATH_H
#define CONSTELLATIONS_PATH_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

/**
 * @brief Class representing an arrow drawn from a path
**/
class Path : public sf::Drawable
{
public:
    Path();
    /**
     * @brief Create an arrow of a given width and color from a given path
     * @param path Vector of sf::Vector representing the arrow path
     * @param width Width of the arrow
     * @param color Color of the arrow
     * @param factor Factor which multiplies width at each iteration
     */
    void create(const std::vector<sf::Vector2f>& path, float width,const sf::Color& color, float factor = 0.99);
    /**
   * @brief draw the arrow on the given rendertarget
   * @param target
   * @param states
   */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    sf::VertexArray mVertexArray;
};


#endif //CONSTELLATIONS_PATH_H
