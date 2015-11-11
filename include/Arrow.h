//
// Created by raph on 10/23/15.
//

#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Planet.h"

class Arrow;

typedef std::shared_ptr<Arrow> SharedArrow;

class Arrow : public sf::Drawable
{
public:

    Arrow(const sf::Vector2f &pos, const sf::Vector2f &speed, float timeStamp);
    Arrow(const Arrow& other);

    bool update(float delta_s);

    /**
    * @brief draw the arrow on the given rendertarget
    * @param target
    * @param states
    */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    const sf::Vector2f& getPos();

private:
    sf::Vector2f mPos;
    sf::Vector2f mSpeed;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    SharedPlanet mPlanet;
    float mPhi;
    float mTimeStamp;
};

#endif //ARROW_H
