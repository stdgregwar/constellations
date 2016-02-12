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
#include "ColorUtils.h"
#include "BiButton.h"

using namespace std;

StateTitleScreen::StateTitleScreen() : mMenuWidget(new Widget()), mMatchMakingWidget(new Widget()),
    mSlots{
            {PLAYER,-1,0,{Core::get().textureCache().get("data/skin.png"),Core::get().textureCache().get("data/hats.png"),-1,Animations::basic}},
            {PLAYER,-1,1,{Core::get().textureCache().get("data/skin.png"),Core::get().textureCache().get("data/hats.png"),-1,Animations::basic}},
            {NONE,-1,2,{Core::get().textureCache().get("data/skin.png"),Core::get().textureCache().get("data/hats.png"),-1,Animations::basic}},
            {NONE,-1,3,{Core::get().textureCache().get("data/skin.png"),Core::get().textureCache().get("data/hats.png"),-1,Animations::basic}},
            {NONE,-1,4,{Core::get().textureCache().get("data/skin.png"),Core::get().textureCache().get("data/hats.png"),-1,Animations::basic}}
        }
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
    using namespace std::placeholders; //For using _1,_2,etc
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
        sf::FloatRect rect{lm+i*((rm-lm)/5)-3,-170,128,128};
        mSlots[i-1].skin.setRotation(-90);
        mSlots[i-1].skin.setPosition(930*2,(i-5)*((lm-rm)/5));
        mSlots[i-1].skin.setScale(4,4);
        mMatchMakingWidget->add(new BiButton(rect,bind(&StateTitleScreen::rollSlotHat,this,i-1),bind(&StateTitleScreen::rollSlotColor,this,i-1)));
        mMatchMakingWidget->add(new CaptionWidget("Slot " + to_string(i)))->setPosition(lm+i*((rm-lm)/5),-300);
        mMatchMakingWidget->add(new ComboBox({
                                                 {NONE,"None"},
                                                 {PLAYER,"Player"},
                                                 {BOT,"Bot"},
                                                 {ONLINE,"Online"}
                                             },(i<3 ? PLAYER : NONE),bind(&StateTitleScreen::setSlotMode,this,i-1,_1)))->setPosition(lm+i*((rm-lm)/5),50);
    }

    mMatchMakingWidget->show();

    mBackground.setTexture(Core::get().textureCache().get("data/stars_w_4.png"),4);
    mBackground.uniformDistribution({-1280*2,-720*2,1280*4,720*4}, 1290);
    mView = Core::get().renderWindow().getDefaultView();
    mView.setTarget(*mMenuWidget.get());

    mMusic = SharedMusic(new FlatMusic("data/Constellations.ogg"));
    Core::get().soundMgr().play(mMusic,2,SoundManager::DIRECT);
    Core::get().networkMgr().setReceiver(this);
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
    mView.setSize(1280,720);
    Core::get().soundMgr().play(mMusic,2,SoundManager::CHAINED);
}

void StateTitleScreen::onEnd()
{

}

void StateTitleScreen::onPause()
{
    //mMusic->pause();
}

void StateTitleScreen::initNetworking()
{
    Core::get().networkMgr().startNetworking([&](bool b){});
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
    for(int i = 0; i < 5; i++)
    {
        mSlots[i].skin.draw(target);
    }
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
    Core::get().globalDict().set("player_count", j::number(count));
}

void StateTitleScreen::setPlayerPv(int pv)
{
    Core::get().globalDict().set("player_pv", j::number(pv));
}

void StateTitleScreen::setHint(bool set)
{
    Core::get().globalDict().set("hint", j::boolean(set));
}

void StateTitleScreen::setSelfHit(bool set)
{
    Core::get().globalDict().set("selfHit",j::boolean(set));
}

void StateTitleScreen::setSlotMode(int n, int mode)
{
    mSlots[n].mode = (Mode)mode;
    if(mode == NONE) {
       mSlots[n].skin.setColor(sf::Color(25,25,25,255));
    } else {
        mSlots[n].skin.setColor(COLOR_POOL[mSlots[n].colorId%COLOR_POOL.size()]);
    }
}

void StateTitleScreen::rollSlotColor(int n)
{
    if(mSlots[n].mode == PLAYER || mSlots[n].mode == BOT)
    {
        mSlots[n].colorId = (mSlots[n].colorId+1)%COLOR_POOL.size();
        mSlots[n].skin.setColor(COLOR_POOL[mSlots[n].colorId]);
    }
}

void StateTitleScreen::rollSlotHat(int n)
{
    if(mSlots[n].mode == PLAYER || mSlots[n].mode == BOT)
    {
        mSlots[n].hatId = (mSlots[n].hatId + 2)%6 - 1;
        mSlots[n].skin.setHat(mSlots[n].hatId);
    }
}

void StateTitleScreen::onReceive(const j::Value &message)
{
    string kind = message["kind"].toString();

    if(mMainWidget == mMatchMakingWidget) { //In match making
        if(kind == "ConnectionRequestRes") {

        }
    }

}
