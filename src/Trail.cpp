#include "Trail.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "VecUtils.h"
#include <cmath>

using namespace std;

Trail::Trail(float width, float threshold, size_t size) : mLastPoint(10e6,10e6), mVertexArray(size*6),
    mStart(0), mEnd(0), mWidth(width), mThreshold(threshold), mLoop(false), mStarted(false)
{

}

void Trail::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(mEnd<=mStart && mLoop)
    {
        target.draw(&mVertexArray[mStart],mVertexArray.size()-mStart,sf::Triangles,states);
        target.draw(&mVertexArray[0],mEnd,sf::Triangles,states);
    }
    else
    {
        target.draw(&mVertexArray[mStart],mEnd-mStart,sf::Triangles,states);
    }
}

void Trail::addPoint(const sf::Vector2f &p)
{
    for(sf::Vertex& v : mVertexArray)
        v.color.a = max(0,v.color.a-2);

    if(!mStarted){
        mLastPoint = p;
        mA = mB = p;
        mStarted = true;
    }
    if(lengthSquared(p-mLastPoint) > mThreshold*mThreshold)
    {

        if(mEnd != mStart || mLoop)
        {
            sf::Vector2f a = p + perpendicularNorm(p-mLastPoint)*mWidth;
            sf::Vector2f b = p + perpendicularNorm(p-mLastPoint)*-mWidth;
            sf::Vector2f c = mA;
            sf::Vector2f d = mB;


            /**
             * a----b
             * |   /|
             * |  / |
             * | /  |
             * c----d
            */

            size_t base = (mEnd)%mVertexArray.size();

            mVertexArray[base+0].position = a;
            mVertexArray[base+1].position = c;
            mVertexArray[base+2].position = b;
            mVertexArray[base+3].position = b;
            mVertexArray[base+4].position = c;
            mVertexArray[base+5].position = d;
            for(int i = 0; i < 6; i++)
            {
                mVertexArray[base+i].color.a = 255;
            }
            mA = a;
            mB = b;
        }
        mLastPoint = p;
        mEnd = (mEnd+6)%mVertexArray.size();
        if(mEnd == mStart || mLoop) {
            mStart = mEnd;
            mLoop = true;
        }
    }

}

