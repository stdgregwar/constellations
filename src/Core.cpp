#include "Core.h"
#include "config.h"
#include <string>
#include <iostream>
#include "StateConstellation.h"
#include "StateTitleScreen.h"

using namespace std;

Core* Core::mInstance = nullptr;

Core::Core() : mGlobalTime(0)
{
    mInstance = this;
}

bool Core::init(sf::Vector2u size)
{

    mRenderWindow.create(sf::VideoMode(1280,720),"Constellations " + to_string(myproject_VERSION_MAJOR) + "." + to_string(myproject_VERSION_MINOR) ,sf::Style::Resize | sf::Style::Default);
    mRenderWindow.setKeyRepeatEnabled(false);
    return mRenderWindow.isOpen();
}

bool Core::start()
{
    mRenderWindow.setVerticalSyncEnabled(true);

    if(mRenderWindow.isOpen())
        pushState(SharedState(new StateTitleScreen()));

    unsigned substeps = 5;

    sf::Clock clk;
    while(mRenderWindow.isOpen())
    {
        for(sf::Event e; mRenderWindow.pollEvent(e);)
        {
            if(mStateStack)
                mStateStack->pushEvent(e);

            if(e.type == sf::Event::Closed)
                endGame();
        }
        sf::Time time = clk.restart();
        mGlobalTime += time.asSeconds();
        if(mStateStack)
        {
            mRenderWindow.clear(sf::Color(30,10,30));
            for(int i = 0; i < substeps; i++)
                mStateStack->update(time.asSeconds()/substeps);
            mStateStack->drawAll(mRenderWindow);
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

Core &Core::get()
{
    if(!mInstance)
        new Core();
    return *mInstance;
}

void Core::replaceState(SharedState state)
{
    popState(); //TODO avoid resume and pause parent state
    pushState(state);
}

SharedState Core::popState()
{
    SharedState poped = mStateStack;
    mStateStack = poped->child();
    if(mStateStack)
        mStateStack->onResume();
    poped->onEnd();
    return poped;
}

SharedState Core::currentState()
{
    return mStateStack;
}

void Core::pushState(SharedState state)
{
    SharedState child = mStateStack;
    mStateStack = state;
    if(child and mStateStack) {
        mStateStack->setChild(child);
        child->onPause();
    }
    if(mStateStack)
        mStateStack->onBegin();
}

const sf::RenderWindow& Core::renderWindow(){return mRenderWindow;}

Properties& Core::globalDict(){return mGlobalDict;}

void Core::endGame()
{
    while(mStateStack)
        popState();
    mRenderWindow.close();
}
