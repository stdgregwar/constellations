#include "StateTitleScreen.h"
#include "Core.h"
#include "StateConstellation.h"
#include "CaptionWidget.h"
#include "Button.h"
#include "SpinBox.h"
#include "ComboBox.h"
#include <functional>
#include <CheckBox.h>
#include "CrossFadeTransition.h"

using namespace std;

StateTitleScreen::StateTitleScreen() : mMenuWidget(new Widget()), mMatchMakingWidget(new Widget())
{
}

void StateTitleScreen::onBegin()
{
    mView.setAlpha(0.95);

    mMainWidget = mMenuWidget;
    mMenuWidget->setPosition(1280/2,720/2);
    mMatchMakingWidget->setPosition(1280*1.5,720*0.5);
    mMatchMakingWidget->setRotation(-90);

    //TITLE
    sf::Texture* titleTex = Core::get().textureCache().get("data/constellations.png");
    mTitle.setOrigin(titleTex->getSize().x/2.f,titleTex->getSize().y/2.f);
    mTitle.setTexture(*titleTex);
    mTitle.setScale(2.5f,2.5f);
    Core::get().textureCache().get("data/constellations.png")->setSmooth(false);
    mTitle.setPosition(1280/2,200);

    //MENU
    using namespace std::placeholders;
    SharedWidget start = mMenuWidget->add(new Button(L"Start!",[&]{
        mView.setTarget(*mMatchMakingWidget.get());
        mMainWidget = mMatchMakingWidget;
    }));
    start->setPosition(-150+90,+90);
    float space = 50;
    start->add(new SpinBox("Players",2,2,5,std::bind(&StateTitleScreen::setPlayerCount,this,_1)))->setPosition(0,space*1);
    start->add(new SpinBox("Life points",1,1,10,std::bind(&StateTitleScreen::setPlayerPv,this,_1)))->setPosition(0,space*2);
    start->add(new CheckBox("Hint",true,std::bind(&StateTitleScreen::setHint,this,_1)))->setPosition(0,space*3);
    start->add(new CheckBox("Friendly fire",true,std::bind(&StateTitleScreen::setSelfHit,this,_1)))->setPosition(0,space*4);
    start->add(new Button(L"Quit",[]{Core::get().endGame();}))->setPosition(0,space*5);
    mMenuWidget->show();
    start->show();
    start->setOrigin(90,90);

    //MatchMaking
    mMatchMakingWidget->add(new Button(L"Back",[&]{
        mView.setTarget(*mMenuWidget.get());
        mMainWidget = mMenuWidget;
    }, 50, sf::Color::White, sf::Color::Red))->setPosition(-1200*0.5,-700*0.5);

    float lm(-600),rm(300);
    for(int i = 1; i <= 5; i++)
    {
        mMatchMakingWidget->add(new CaptionWidget("Slot " + to_string(i)))->setPosition(lm+i*((rm-lm)/5),-300);
        mMatchMakingWidget->add(new ComboBox({
                                                 {0,"Player"},
                                                 {1,"Bot"},
                                                 {2,"Online"},
                                                 {3,"None"}
                                             },3,nullptr))->setPosition(lm+i*((rm-lm)/5),50);
    }

    mMatchMakingWidget->show();

    mBackground.setTexture(Core::get().textureCache().get("data/stars_w_4.png"),4);
    mBackground.uniformDistribution({-1280*2,-720*2,1280*4,720*4}, 1290);
    mView = Core::get().renderWindow().getDefaultView();
    mView.setTarget(*mMenuWidget.get());

    mMusic = SharedMusic(new FlatMusic("data/Constellations.ogg"));
    Core::get().soundMgr().play(mMusic,2,SoundManager::DIRECT);
}

void StateTitleScreen::update(float delta_s)
{
    //NA
    mView.update(delta_s);
    //mMainWidget->children()[0]->setRotation(stw(Core::get().time())*5);
}

void StateTitleScreen::onResume()
{
    sf::Vector2u size = Core::get().renderWindow().getSize();
    mView.setSize(size.x,size.y);
    Core::get().soundMgr().play(mMusic,2,SoundManager::CHAINED);
}

void StateTitleScreen::onEnd()
{

}

void StateTitleScreen::onPause()
{
    //mMusic->pause();
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
    target.draw(*mMenuWidget.get(),mMenuWidget->getTransform());
    target.draw(*mMatchMakingWidget.get(), mMatchMakingWidget->getTransform());
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
        //mView.setSize(e.size.width,e.size.height);
        mView.setSize(1280,720);
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
