#include "../include/LayerMusic.h"
#include "Core.h"

using namespace std;

LayerMusic::LayerMusic(std::map<string, string> &&musics) : mBaseVolume(100)
{
    for(auto& p : musics)
    {
        if(!mMusics[p.first].openFromFile(p.second))
            throw runtime_error("Could not open " + p.second);
        mMusics[p.first].setVolume(0);
        mMusics[p.first].setLoop(true);
    }
    mTo = mMusics.begin();
    mTo->second.setVolume(mBaseVolume);
    mFrom = mMusics.end();
}

void LayerMusic::update(float delta_s)
{
    if(mFrom != mMusics.end())
    {
        float factor = (Core::get().time() - mStartTime) / mDuration;
        mFrom->second.setVolume(mBaseVolume-factor*mBaseVolume);
        mTo->second.setVolume(factor*mBaseVolume);
        if(factor > 1)
        {
            mFrom = mMusics.end();
        }
    }
}

void LayerMusic::play()
{
    for(auto& p : mMusics)
    {
        p.second.play();
    }
}

void LayerMusic::pause()
{
    for(auto& p : mMusics)
    {
        p.second.pause();
    }
}

void LayerMusic::stop()
{
    for(auto& p : mMusics)
    {
        p.second.stop();
    }
}

void LayerMusic::setVolume(float volume)
{
    mBaseVolume = volume;
    if(mTo != mMusics.end() && mFrom == mMusics.end())
        mTo->second.setVolume(mBaseVolume);
}

void LayerMusic::switchTo(string name, float duration)
{
    mDuration = duration;
    mStartTime = Core::get().time();
    mFrom = mTo;
    mTo = mMusics.find(name);
    if(mTo == mMusics.end())
        throw runtime_error("Could not find music layer named " + name);
}

LayerMusic::~LayerMusic()
{

}

