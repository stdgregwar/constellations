#include "StateTitleScreen.h"
#include "Core.h"
#include "StateConstellation.h"
#include "Button.h"
#include "SpinBox.h"
#include <functional>
#include <CheckBox.h>
#include "CrossFadeTransition.h"

StateTitleScreen::StateTitleScreen() : mMainWidget(new Widget())
{
}

void StateTitleScreen::onBegin()
{
    using namespace std::placeholders;
    sf::Texture* titleTex = Core::get().textureCache().get("data/constellations.png");
    mTitle.setOrigin(titleTex->getSize().x/2.f,titleTex->getSize().y/2.f);
    mTitle.setTexture(*titleTex);
    mTitle.setScale(2.5f,2.5f);
    Core::get().textureCache().get("data/constellations.png")->setSmooth(false);

    mTitle.setPosition(1280/2,200);

    SharedWidget start = mMainWidget->add(new Button(L"Start!",std::bind(&StateTitleScreen::launchStateConstellation,this)));
    start->setPosition(1280/2-150+90,720/2+90);
    start->add(new SpinBox("Players",2,2,5,std::bind(&StateTitleScreen::setPlayerCount,this,_1)))->setPosition(0,60);
    start->add(new SpinBox("Life points",1,1,10,std::bind(&StateTitleScreen::setPlayerPv,this,_1)))->setPosition(0,120);
    start->add(new CheckBox("Hint",true,std::bind(&StateTitleScreen::setHint,this,_1)))->setPosition(0,180);
    start->add(new CheckBox("Friendly fire",true,std::bind(&StateTitleScreen::setSelfHit,this,_1)))->setPosition(0,240);
    start->add(new Button(L"Quit",[]{Core::get().endGame();}))->setPosition(0,300);
    mMainWidget->show();
    start->show();
    start->setOrigin(90,90);

    mBackground.setTexture(Core::get().textureCache().get("data/stars_w_4.png"),4);
    mBackground.uniformDistribution({0,0,1280,720}, 150);
    mView = Core::get().renderWindow().getDefaultView();
}

void StateTitleScreen::update(float delta_s)
{
    //NA
    //mMainWidget->children()[0]->setRotation(stw(Core::get().time())*5);
}

void StateTitleScreen::onResume()
{
    sf::Vector2u size = Core::get().renderWindow().getSize();
    mView.setSize(size.x,size.y);
}

void StateTitleScreen::onEnd()
{

}

void StateTitleScreen::onPause()
{

}

void StateTitleScreen::launchStateConstellation()
{
    setVisible(false);
    Core::get().pushState(SharedState(new StateConstellation()), new CrossFadeTransition(0.5));
}

void StateTitleScreen::draw(sf::RenderTarget &target)
{
    target.setView(mView);
    target.draw(mBackground);
    target.draw(*mMainWidget.get());
    target.draw(mTitle);
}

void StateTitleScreen::pushEvent(const sf::Event &e)
{
    mMainWidget->pushEvent(e,mView);
    switch(e.type)
    {
        case sf::Event::KeyReleased:
            if(e.key.code == sf::Keyboard::Return)
                launchStateConstellation();
            if(e.key.code == sf::Keyboard::Escape)
                Core::get().endGame();
        break;
    case sf::Event::Resized:
        mView.setSize(e.size.width,e.size.height);
    }
}

void StateTitleScreen::setPlayerCount(int count)
{
    Core::get().globalDict()["player_count"] = count;
}

void StateTitleScreen::setPlayerPv(int pv)
{
    Core::get().globalDict()["player_pv"] = pv;
}

void StateTitleScreen::setHint(bool set)
{
    Core::get().globalDict()["hint"] = set;
}

void StateTitleScreen::setSelfHit(bool set)
{
    Core::get().globalDict()["selfHit"] = set;
}
