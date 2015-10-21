#include "Core.h"
#include "config.h"
#include <string>
#include "StateConstellation.h"

using namespace std;

Core* Core::mInstance = nullptr;

Core::Core()
{
    mInstance = this;
}

bool Core::init(sf::Vector2u size)
{
    mRenderWindow.create(sf::VideoMode(1280,720),"Constellations " + to_string(myproject_VERSION_MAJOR) + "." + to_string(myproject_VERSION_MINOR) ,sf::Style::Resize | sf::Style::Default);
    return mRenderWindow.isOpen();
}

bool Core::start()
{
    pushState(SharedState(new StateConstellation()));
    mRenderWindow.setVerticalSyncEnabled(true);

    while(mRenderWindow.isOpen())
    {
        for(sf::Event e; mRenderWindow.pollEvent(e);)
        {
            if(e.type == sf::Event::Closed)
                mRenderWindow.close();
        }
        mRenderWindow.clear();
        mStateStack->update(1.0/60);
        mStateStack->drawAll(mRenderWindow);
        mRenderWindow.display();
    }
}

Core* Core::get()
{
    if(!mInstance)
        new Core();
    return mInstance;
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
