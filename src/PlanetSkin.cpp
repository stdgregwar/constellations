#include "../include/PlanetSkin.h"
#include <SFML/Graphics/BlendMode.hpp>
#include "Core.h"
#include <cmath>
#include "MathUtils.h"

PlanetSkin::PlanetSkin(float radius)
{
    createHalo(radius-1,radius*1.5,sf::Color(0x222233ff),sf::Color(0x000000ff));
    mSprite.setTexture(*Core::get().textureCache().get("data/planet.png"));
    mSprite.setOrigin(mSprite.getTexture()->getSize().x/2,mSprite.getTexture()->getSize().y/2);
    mSprite.setScale(radius/25.f,radius/25.f);
}

void PlanetSkin::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RenderStates hStates = states;
    hStates.blendMode  = sf::BlendAdd;
    float s = 1+stw(Core::get().time()*2)*0.008;
    hStates.transform = hStates.transform.scale(s,s);
    target.draw(mHalo,hStates);
    target.draw(mSprite,states);
}

void PlanetSkin::createHalo(float r, float R, const sf::Color& first, const sf::Color& second, int count)
{
    mHalo.resize((count+1)*6);
    mHalo.setPrimitiveType(sf::Triangles);

    sf::Vertex c,d;
    sf::Vertex a({r,0});
    a.color = first;
    sf::Vertex b({R,0});
    b.color = second;
    for(int i = 0; i < count; i++)
    {
        //TODO texcoords for panoramas
        c = a; d = b;
        float angle = 2*M_PI*(float(i+1)/count);
        a.position = {r*cos(angle),r*sin(angle)};
        b.position = {R*cos(angle),R*sin(angle)};

        sf::Vertex* quad = &mHalo[i*6];
        quad[0] = b;
        quad[1] = a;
        quad[2] = c;
        quad[3] = c;
        quad[4] = d;
        quad[5] = b;
    }
}

PlanetSkin::~PlanetSkin()
{
    Core::get().textureCache().free(mSprite.getTexture());
}
