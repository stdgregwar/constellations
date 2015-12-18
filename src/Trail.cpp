#include "Trail.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "VecUtils.h"
#include <cmath>
#include "Core.h"

using namespace std;

Trail::Trail(float width, float dt, size_t size) : mLastPoint(10e6,10e6), mVertexArray((size+1)*2),
    mStart(4), mEnd(2), mDt(dt), mWidth(width), mLoop(false), mStarted(false),mLastTime(0)
{

}

void Trail::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(mVertexArray.empty()) //Don't do anything if empty
        return;


    if(mEnd<=mStart && mLoop)
    {
        target.draw(&mVertexArray[mStart],mVertexArray.size()-mStart,sf::TrianglesStrip,states);
        target.draw(&mVertexArray[0],mEnd,sf::TrianglesStrip,states);
    }
    else
    {
        target.draw(&mVertexArray[mStart],mEnd-mStart,sf::TrianglesStrip,states);
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
            /*sf::Vector2f c = mA;
            sf::Vector2f d = mB;*/


            /**
             * a----b
             * |   /|
             * |  / |
             * | /  |
             * c----d
            */

            size_t base = mEnd;
            mVertexArray[base+0].position = a;
            mVertexArray[base+1].position = b;
            mVertexArray[base+0].color.a = 255;
            mVertexArray[base+1].color.a = 255;

            mVertexArray[0] = mVertexArray[mVertexArray.size()-2];
            mVertexArray[1] = mVertexArray[mVertexArray.size()-1];
        }
        mLastPoint = p;
        mEnd = (mEnd)%(mVertexArray.size()-2)+2;
        if(mEnd == mStart || mLoop) {
            mStart = mEnd;
            mLoop = true;
        }
    }
    if(nDec == 0)
        empty();
    return nDec == 0;
}

