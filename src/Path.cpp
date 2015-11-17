//
// Created by raph on 11/16/15.
//

#include "Path.h"
#include "VecUtils.h"



Path::Path(){}

void Path::create(const std::vector<sf::Vector2f> &path, float width,const sf::Color& color, float factor)
{
    if(path.size() < 2) //Cannot create path with only one point
        return;
    mVertexArray.resize((path.size() - 1)*6);
    mVertexArray.setPrimitiveType(sf::Triangles);

    //Tail
    /**
     * a----b
     * |   /|
     * |  / |
     * | /  |
     * c----d
    */

    sf::Vector2f a = path[1] + perpendicularNorm(path[1]-path[0])*width;
    sf::Vector2f b = path[1] + perpendicularNorm(path[1]-path[0])*-width;
    sf::Vector2f c = path[0] + perpendicularNorm(path[0]-path[1])*-width;
    sf::Vector2f d = path[0] + perpendicularNorm(path[0]-path[1])*width;

    mVertexArray[0].position = a;
    mVertexArray[1].position = c;
    mVertexArray[2].position = path[1];
    mVertexArray[3].position = path[1];
    mVertexArray[4].position = d;
    mVertexArray[5].position = b;

    for(int i = 0; i < 6; i++)
    {
        mVertexArray[i].color = color;
    }

    //Body

    for(int i = 1; i < path.size()-2; i++)
    {
        int j = i*6;
        c = a;
        d = b;
        a = path[i+1] + perpendicularNorm(path[i+1]-path[i])*width;
        b = path[i+1] + perpendicularNorm(path[i+1]-path[i])*-width;

        mVertexArray[j].position = a;
        mVertexArray[j+1].position = c;
        mVertexArray[j+2].position = d;
        mVertexArray[j+3].position = d;
        mVertexArray[j+4].position = b;
        mVertexArray[j+5].position = a;

        for(int k = 0; k < 6; k++)
        {
            mVertexArray[j+k].color = color;
        }

        width *= factor;
    }

    //Head
    int i = path.size()-2;
    int j = path.size()-1;
    sf::Vector2f sub = path[j]-path[i];

    a = path[i] + perpendicularNorm(sub)*width*2.0f;
    b = path[i] + perpendicularNorm(sub)*-width*2.0f;
    a -= normalise(sub)*width;
    b -= normalise(sub)*width;

    mVertexArray[i*6+0].position = path[j];
    mVertexArray[i*6+1].position = a;
    mVertexArray[i*6+2].position = path[i];
    mVertexArray[i*6+3].position = path[i];
    mVertexArray[i*6+4].position = b;
    mVertexArray[i*6+5].position = path[j];

    for(int k = 0; k < 6; k++)
    {
        mVertexArray[i*6+k].color = color;
    }
}

void Path::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mVertexArray,states);
}
