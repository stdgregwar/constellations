//
// Created by raph on 11/16/15.
//

#ifndef CONSTELLATIONS_PATH_H
#define CONSTELLATIONS_PATH_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


class Path : public sf::Drawable
{
public:
    Path();
    void create(const std::vector<sf::Vector2f>& path, float width,const sf::Color& color);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    sf::VertexArray mVertexArray;
};


#endif //CONSTELLATIONS_PATH_H
