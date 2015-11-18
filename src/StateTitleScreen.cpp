#include "StateTitleScreen.h"
#include "Core.h"
#include "StateConstellation.h"
#include "Button.h"
#include <functional>

StateTitleScreen::StateTitleScreen() : mMainWidget(new Widget())
{
}

void StateTitleScreen::onBegin()
{
    mFont.loadFromFile("data/zeldadxt.ttf");
    mTitleFont.loadFromFile("data/gothic.ttf");

    mTitle.setFont(mTitleFont);
    mTitle.setString("Constellations");
    sf::Text startText;
    startText.setFont(mFont);
    startText.setString("Start!");
    startText.setCharacterSize(50);

    mExitText.setFont(mFont);

    mTitle.setPosition(300,50);
    mTitle.setCharacterSize(156);
    startText.setPosition(1280/2-100,720/2);

    mMainWidget->add(new Button(startText,std::bind(&StateTitleScreen::launchStateConstellation,this)));
    startText.setPosition(1280/2-100,720/2+60);
    startText.setString(L"Quit");
    mMainWidget->add(new Button(startText,[]{Core::get().endGame();}));


    mBackground.setTexture(Core::get().textureCache().get("data/stars_w_4.png"),4);
    mBackground.uniformDistribution({0,0,1280,720}, 150);
    mView = Core::get().renderWindow().getDefaultView();
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
    Core::get().globalDict().add({
                                     {"uneProp", 0.123},
                                     {"une string", "Voila"}
                                 });
    setVisible(false);
    Core::get().pushState(SharedState(new StateConstellation()));
}

void StateTitleScreen::draw(sf::RenderTarget &target)
{
    target.draw(mBackground);
    target.draw(*mMainWidget.get());
    target.draw(mTitle);
}

void StateTitleScreen::pushEvent(const sf::Event &e)
{
    mMainWidget->pushEvent(e);
    switch(e.type)
    {
        case sf::Event::KeyReleased:
            if(e.key.code == sf::Keyboard::Return)
                launchStateConstellation();
            if(e.key.code == sf::Keyboard::Escape)
                Core::get().endGame();
            break;
    }
}
