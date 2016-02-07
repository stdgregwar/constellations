#include "Core.h"
#include "config.h"
#include <string>
#include <iostream>
#include "StateConstellation.h"
#include "StateTitleScreen.h"
#include <cmath>

using namespace std;

Core* Core::mInstance = nullptr;

Core::Core() : mGlobalTime(0), mTimeFactor(1), mTargetFactor(1), mTransition(nullptr),
    mTextureCache([](const std::string& id)->sf::Texture*{
                    sf::Texture* tex = new sf::Texture();
                    if(tex->loadFromFile(id))
                        return tex;
                    else{
                        delete tex;
                        return nullptr;
                    }
                }),
    mFontCache([](const std::string& id)->sf::Font*{
                sf::Font* font = new sf::Font();
                if(font->loadFromFile(id))
                    return font;
                else{
                    delete font;
                    return nullptr;
                }
            }),
    mSoundBufferCache([](const std::string& id)->sf::SoundBuffer*{
                sf::SoundBuffer* sound = new sf::SoundBuffer();
                if(sound->loadFromFile(id))
                    return sound;
                else{
                    delete sound;
                    return nullptr;
                }
            }),
    mScheduledPops(0)
{
    mInstance = this;
    //For net tests
    globalDict()["host"] = string("localhost");
    globalDict()["port"] = 1337;
}

TextureCache& Core::textureCache()
{
    return mTextureCache;
}

FontCache& Core::fontCache(){
    return mFontCache;
}


SoundBufferCache& Core::soundBufferCache()
{
    return mSoundBufferCache;
}

void Core::popScheduled()
{
    for(;mScheduledPops>0; --mScheduledPops)
    {
        popState(mScheduledTransition);
        mScheduledTransition = nullptr;
    }
}

bool Core::init(sf::Vector2u size)
{
    mNetworkManager.startNetworking([](bool b){cout << "It's " << (b ? "working!" : "shitting!") << endl;});
    mRenderWindow.create(sf::VideoMode(1280,720),"Constellations " + to_string(myproject_VERSION_MAJOR) + "." + to_string(myproject_VERSION_MINOR) ,sf::Style::Resize | sf::Style::Default);
    mRenderWindow.setKeyRepeatEnabled(false);
    return mRenderWindow.isOpen();
}

bool Core::start()
{
    mFontCache.put("default",mFontCache.loadOnly("data/8bitmadness.ttf")); //Load default font in cache
    //Clear font
    const sf::Texture& tex = mFontCache.get("default")->getTexture(50);
    ((sf::Texture*)(&tex))->setSmooth(false);

    mRenderWindow.setVerticalSyncEnabled(true);

    if(mRenderWindow.isOpen())
        pushState(SharedState(new StateTitleScreen()));

    unsigned substeps = 5;

    sf::Clock clk;
    while(mRenderWindow.isOpen())
    {
        //Pop states if needed
        tickTimers();
        popScheduled();

        for(sf::Event e; mRenderWindow.pollEvent(e);)
        {
            if(mStateStack)
                mStateStack->pushEvent(e);

            if(e.type == sf::Event::Closed)
                endGame();
        }
        sf::Time time = clk.restart();
        if(mTimeFactor > mTargetFactor)
            mTimeFactor = 0.8f*mTimeFactor+0.2f*mTargetFactor;
        else
            mTimeFactor = 0.98f*mTimeFactor+0.02f*mTargetFactor;

        mLastDt = basic_dt*mTimeFactor;
        //mLastDt = time.asSeconds()*mTimeFactor;
        mGlobalTime += mLastDt;

        mSoundManager.update(mLastDt);
        mNetworkManager.update(mLastDt);

        if(mStateStack)
        {
            mRenderWindow.clear(sf::Color(30,10,30));
            if(mTransition) {
                switch(mTransition->update())
                {
                    case Transition::END:
                        delete mTransition;
                        mTransition = nullptr;
                        mFromTransition.reset();
                        mStateStack->drawAll(mRenderWindow);
                        break;
                    case Transition::FIRST:
                        mFromTransition->draw(mRenderWindow);
                        mRenderWindow.draw(*mTransition);
                        break;
                    case Transition::SECOND:
                        mStateStack->drawAll(mRenderWindow);
                        mRenderWindow.draw(*mTransition);
                        break;
                }

            } else {
                for(int i = 0; i < substeps; i++)
                    mStateStack->update((mLastDt)/substeps);
                mStateStack->drawAll(mRenderWindow);
            }
            mRenderWindow.display();
        }
    }
}

float Core::time()
{
    return mGlobalTime;
}

float Core::aspectRatio()
{
    return (float)(mRenderWindow.getSize().y) / mRenderWindow.getSize().x;
}

float Core::timeStretch(float factor, float duration)
{
    mTargetFactor = factor;
    Timer::create(duration*factor,bind([](float* fac){*fac = 1;},&mTargetFactor));
}

 void Core::tickTimers()
 {
     for(auto it = mTimers.begin(); it != mTimers.end(); ++it)
     {
         if((*it)->tick(time())) {
             mTimers.erase(it++);
         }
     }
 }

bool Core::isStretchin()
{
    return abs(1-mTimeFactor) > 10e-2;
}

float Core::timeFactor()
{
    return mTimeFactor;
}

Core &Core::get()
{
    if(!mInstance)
        new Core();
    return *mInstance;
}

void Core::replaceState(SharedState state, Transition *t)
{
    popState(); //TODO avoid resume and pause parent state
    pushState(state);
}

SharedState Core::delayedPop(Transition* t)
{
    mScheduledPops++;
    mScheduledTransition = t;
    return mStateStack;
}

SharedState Core::popState(Transition* t)
{
    SharedState poped = mStateStack;
    mStateStack = poped->child();
    poped->onEnd();
    if(mStateStack)
    {
        mStateStack->onResume();
        mStateStack->setVisible(true);
    }
    mFromTransition = poped;
    setTransition(t);
    return poped;
}

SharedState Core::currentState()
{
    return mStateStack;
}

void Core::pushState(SharedState state, Transition* t)
{
    if(t) {
        setTransition(t);
        mFromTransition = mStateStack;
    }
    SharedState child = mStateStack;
    mStateStack = state;
    if(child and mStateStack) {
        mStateStack->setChild(child);
        child->onPause();
    }
    if(mStateStack)
        mStateStack->onBegin();
}

float Core::addTimer(SharedTimer timer)
{
    mTimers.push_back(timer);
    timer->setTimeStamp(time());
    return time();
}

const sf::RenderWindow& Core::renderWindow(){return mRenderWindow;}

Properties& Core::globalDict(){return mGlobalDict;}

void Core::endGame()
{
    while(mStateStack)
        popState();
    mRenderWindow.close();
}

void Core::setTransition(Transition *t)
{
    mTransition = t;
}

float Core::lastDt()
{
    return mLastDt;
}

SoundManager& Core::soundMgr()
{
    return mSoundManager;
}

unsigned int Core::randomSeed()
{
    return rd();
}
