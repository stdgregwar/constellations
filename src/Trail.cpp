#include "Trail.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "VecUtils.h"
#include <cmath>
#include "Core.h"

using namespace std;

Trail::Trail(float width, float dt, size_t size) : mLastPoint(10e6,10e6), mVertexArray(size*6),
    mStart(0), mEnd(0), mDt(dt), mWidth(width), mLoop(false), mStarted(false),mLastTime(0)
{

}

void Trail::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(mVertexArray.empty()) //Don't do anything if empty
        return;


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

void Trail::empty()
{
    mVertexArray.clear();
    mStart = mEnd = 0;
}

bool Trail::addPoint(const sf::Vector2f &p)
{
    if(mVertexArray.empty()) //Don't do anything if empty
        return true;

    int nDec(0);
    float dt = Core::get().lastDt();
    for(sf::Vertex& v : mVertexArray) {
        v.color.a = max(0,int(v.color.a-(480*dt)));
        if(v.color.a != 0)
            nDec++;
    }

    if(!mStarted){
        mLastPoint = p;
        mA = mB = p;
        mStarted = true;
    }

    float time = Core::get().time();
    if(time-mLastTime >= mDt)
    {
        mLastTime = time;

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


            mVertexArray[base+0].color.a = 255;
            mVertexArray[base+2].color.a = 255;
            mVertexArray[base+3].color.a = 255;

            //Temp
            mVertexArray[base+1].color.a = 255-8;
            mVertexArray[base+4].color.a = 255-8;
            mVertexArray[base+5].color.a = 255-8;


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
    if(nDec == 0)
        empty();
    return nDec == 0;
}

