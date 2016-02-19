#include "StateError.h"
#include "Core.h"

using namespace std;

StateError::StateError(const CException& e) : mType(e.type())
{
    mText.setFont(*Core::get().fontCache().get("default"));
    mText.setCharacterSize(50);
    mText.setColor(sf::Color::Red);
    mText.setString(+ e.what());
    mText.setPosition(-200,100);

    mTitle.setFont(*Core::get().fontCache().get("default"));
    mTitle.setCharacterSize(100);
    mTitle.setColor(sf::Color::Red);
    mTitle.setString(ETypeNames.at(mType));
    mTitle.setPosition(-200,-100);

    mCam.setSize(Core::get().renderWindow().getSize().x,Core::get().renderWindow().getSize().y);
    mCam.setCenter(0,0);
}

void StateError::onBegin()
{

}

void StateError::onResume()
{

}

void StateError::pushEvent(const sf::Event &e)
{
    if(e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Return)
    {
        switch(mType)
        {
            case WARNING:
                Core::get().delayedPop();
                break;
            case UNKNOWN:
            case FATAL:
                Core::get().endGame();
            default:
            break;
        }
    }
    if(e.type == sf::Event::Resized)
    {
        mCam.setSize(e.size.width,e.size.height);
    }
}

void StateError::update(float delta_s)
{

}

void StateError::draw(sf::RenderTarget &target)
{
    //target.setView(mCam);
    target.setView(mCam);
    target.draw(mText);
    target.draw(mTitle);
}

void StateError::onPause()
{

}

void StateError::onEnd()
{

}

StateError::~StateError()
{

}

