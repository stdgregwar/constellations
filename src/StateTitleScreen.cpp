#include "StateTitleScreen.h"
#include "Core.h"
#include "StateConstellation.h"

StateTitleScreen::StateTitleScreen()
{

}

void StateTitleScreen::onBegin()
{
    mFont.loadFromFile("data/zeldadxt.ttf");
    mTitleFont.loadFromFile("data/gothic.ttf");

    mTitle.setFont(mTitleFont);
    mTitle.setString("Constellations");
    mStartText.setFont(mFont);
    mStartText.setString("Start!");
    mStartText.setCharacterSize(50);

    mExitText.setFont(mFont);

    mTitle.setPosition(300,50);
    mTitle.setCharacterSize(156);
    mStartText.setPosition(1280/2-100,720/2);
}

void StateTitleScreen::update(float delta_s)
{
    //NA
}

void StateTitleScreen::onResume()
{

}

void StateTitleScreen::onEnd()
{

}

void StateTitleScreen::onPause()
{

}

void StateTitleScreen::launchStateConstellation()
{
    Core::get().pushState(SharedState(new StateConstellation()));
}

void StateTitleScreen::draw(sf::RenderTarget &target)
{
    target.draw(mTitle);
    target.draw(mStartText);
}

void StateTitleScreen::pushEvent(const sf::Event &e)
{
    switch(e.type)
    {
        case sf::Event::KeyReleased:
            if(e.key.code == sf::Keyboard::Return)
                launchStateConstellation();
            if(e.key.code == sf::Keyboard::Escape)
                Core::get().endGame();
        break;
        case sf::Event::MouseButtonReleased:
            if(mStartText.getGlobalBounds().contains(e.mouseButton.x,e.mouseButton.y))
                launchStateConstellation();
        break;
        case sf::Event::MouseMoved:
            if(mStartText.getGlobalBounds().contains(e.mouseMove.x,e.mouseMove.y))
                mStartText.setColor(sf::Color::Yellow);
            else
                mStartText.setColor(sf::Color::White);
        break;
    }
}
