#include "StateConstellation.h"
#include "Core.h"


#include <iostream>
#include <algorithm>
#include <Constellation.h>
#include "IntegrationUtils.h"
#include <random>
#include "ConstellationDefine.h"
#include "Mat4.h"
#include "KeyboardController.h"
#include "MathUtils.h"
#include "VecUtils.h"

using namespace std;

StateConstellation::StateConstellation() :
    mIState({nullptr,&StateConstellation::defaultEvent}), mYaw(0), mPitch(0)
{
}

void StateConstellation::onBegin()
{
    //Sounds
    mExplHigh.setBuffer(*Core::get().soundBufferCache().get("data/explodehigh.wav"));
    mExplLow.setBuffer(*Core::get().soundBufferCache().get("data/explodelow.wav"));

    //Textures
    mBackground.setTexture(Core::get().textureCache().get("data/stars_w_4.png"),4);
    mBackground.uniformDistribution({-1280*2,-720*2,1280*4,720*4},1200);

    Constellation constellation;
    int numbersOfMap = int(constellations.size());
    random_device rng;
    uniform_int_distribution<int> int_dist(0,numbersOfMap-1);
    int i =  int_dist(rng);
    int numberOfPlayers = Core::get().globalDict()["player_count"].toInt();
    while(constellations[i].maxNumberOfPlayers < numberOfPlayers)
    {
        i = (i +1)%numbersOfMap;
    }
    constellation.buildFromConstellationDef(constellations[i],numberOfPlayers);
    mPlanets = constellation.getPlanets();
    mPlayers = constellation.getPlayers();

    //FIRST FIX
    Mat4 mat = Mat4::identity();
    for(SharedPlanet& p : mPlanets)
    {
        p->update2DPos(mat);
    }
    for(SharedController& c : mPlayers)
    {
        c->character()->rot(0);
    }

    mCurrentPlayer = mPlayers.begin();

//    cout << Core::get().globalDict();
    using namespace std::placeholders;
    mExpl.setTexture(Core::get().textureCache().get("data/stars_w_4.png"),4);
    mExpl.setFunctions({
                       bind([](StateConstellation* s, DynamicParticles::Particle& p,float time,float dt){
                               auto pl = s->collideWithPlanet(p.pos);

                               if(!pl) {
                                    p.speed+=(s->getGravFieldAt(p.pos)-p.speed*4.f)*dt;
                               } else {
                                    p.speed = mirror(p.speed,pl->normalAt(p.pos));
                               }
                               p.pos+=p.speed*dt;
                           },this,_1,_2,_3),
                       [](const DynamicParticles::Particle& p,float time){return 1-time*0.66f < 0.f;}, //decay
                       [](const DynamicParticles::Particle& p,float time){return 0;}, //rotation
                       [](const DynamicParticles::Particle& p,float time){return max(0.f,min(.7f,6-time*4.f));}, //scale
                       nullptr, //color
                       nullptr //frame
                       });

    const sf::RenderTarget& target = Core::get().renderWindow();
    correctViews(target.getSize().x,target.getSize().y);
}

void StateConstellation::onEnd()
{
    cout << "Ending constellation state" << endl;
    mPlanets.clear();
    mPlayers.clear();
}

void StateConstellation::onResume()
{

}

void StateConstellation::onPause()
{

}

void StateConstellation::draw(sf::RenderTarget& target)
{
    target.setView(mBackView);
    target.draw(mBackground);
    //mView.zoom(1.f/2);

    target.setView(mView);


    for(SharedPlanet& p : mPlanets)
    {
        target.draw(*p);
    }

    for(SharedController& c : mPlayers)
    {
        target.draw(*c->character());
    }

    for(SharedArrow& a : mArrows)
    {
        target.draw(*a);
    }
    target.draw(mExpl);
}

void StateConstellation::update(float delta_s)
{
    if(mIState.uf)
        (*this.*mIState.uf)(delta_s); //Call ptr on function

    defaultUpdate(delta_s);
}

void StateConstellation::defaultUpdate(float delta_s)
{
    if(Core::get().isStretchin()) {
        mExplHigh.setPitch(Core::get().timeFactor());
        mExplLow.setPitch(Core::get().timeFactor());
    }
    for(SharedController& c : mPlayers)
    {
        c->character()->update(delta_s);
    }

    for(SharedArrow& a : mArrows)
    {
        a->update(delta_s);
    }

    /*mPlayers.remove_if(
                [](const SharedController& c)->bool{return c->character()->isDead();}
    );*/
    for(Players::iterator it = mPlayers.begin(); it != mPlayers.end(); it++)
    {
        constexpr float eS = 600;
        if((*it)->character()->isDead()) {
            mExplLow.play();
            mExplHigh.play();
            mExpl.uniformDistribution((*it)->character()->getBounds(),700,{-eS,-eS,2*eS,2*eS});
            if(it == mCurrentPlayer)
                nextPlayer();
            mPlayers.erase(it++);
            if(mPlayers.size() == 1)
            {
                onWin();
            }
            if(mPlayers.size() == 0)
            {
                mCurrentPlayer == mPlayers.end();
                onEquality();
            }
        }
    }
    for(Arrows::iterator it = mArrows.begin(); it != mArrows.end(); it++)
    {
        if((*it)->dead()) mArrows.erase(it++);
    }
}

void StateConstellation::rotUpdate(float delta_s)
{
    constexpr float s = 0.5;
    sf::Vector2i rel = mMousePos - mOldMousePos;
    mYaw = rel.x*s;
    mPitch = -rel.y*s;
    Mat4 mat = Mat4::rotation(Mat4::Axes::Y_AXIS,mYaw);
    mat.rotate(Mat4::Axes::X_AXIS, mPitch);
    //mat *= Mat4::perspective(Core::get().aspectRatio(),45,0.1,5000);
    //mat = Mat4::identity();
    for(SharedPlanet& p : mPlanets)
    {
        p->update2DPos(mat);
    }
    for(SharedController& c : mPlayers)
    {
        c->character()->rot(0);
    }
}

void StateConstellation::pushEvent(const sf::Event &e)
{
    if(mIState.ef)
        (*this.*mIState.ef)(e);
}

void StateConstellation::defaultEvent(const sf::Event &e)
{
    //DEACTIVATED ROTATION FOR NOW
    /*if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right){
        //const sf::Event::MouseButtonEvent& me = e;
        mOldMousePos = {e.mouseButton.x,e.mouseButton.y};
        mIState = {&StateConstellation::rotUpdate,&StateConstellation::rotEvent};
    }*/

    switch(e.type)
    {
        case sf::Event::Resized:
            correctViews(e.size.width,e.size.height);
        break;
    }


    if(mCurrentPlayer != mPlayers.end() && mPlayers.size()) {
        if((*mCurrentPlayer)->onEvent(e)){
//            nextPlayer();
        }
    }
}

void StateConstellation::rotEvent(const sf::Event &e)
{
    if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Right)
        mIState = {nullptr,&StateConstellation::defaultEvent};
    if(e.type == sf::Event::MouseMoved)
        mMousePos = {e.mouseMove.x,e.mouseMove.y};
}

void StateConstellation::waitingEvent(const sf::Event &e){

}

sf::Vector2f StateConstellation::getGravFieldAt(const sf::Vector2f &p) const
{
    sf::Vector2f field;
    for(const SharedPlanet& planet : mPlanets)
    {
        field += planet->get2DField(p);
    }
    return field*(float)25e2;
}

SharedPlanet StateConstellation::collideWithPlanet(const sf::Vector2f &p) const
{
    for(const SharedPlanet& planet : mPlanets)
    {
        if(planet->collideWith(p)) return planet;
    }
    return SharedPlanet();
}

SharedCharacter StateConstellation::collideWithCharacter(const sf::Vector2f &p) const
{
    for(SharedController c : mPlayers)
    {
        if(c->character()->collideWith(p)) return c->character();
    }
    return SharedCharacter();
}

void StateConstellation::pushArrow(SharedArrow a)
{
    mIState = {nullptr,&StateConstellation::waitingEvent};
    a->setCallback(std::bind(&StateConstellation::onArrowDecayed, this));
    mArrows.push_back(a);
}

void StateConstellation::onNewRound()
{
    cout << "New ROUND!!" << endl;
}

void StateConstellation::onWin()
{
    cout << "Player Won" << endl;

    Timer::create(2,[]{Core::get().delayedPop();});
    //Core::get().popState();
}

void StateConstellation::onEquality()
{
    cout << "Everyone is dead...." << endl;
}

void StateConstellation::nextPlayer()
{
    Players::iterator last = mCurrentPlayer++;
    if(mCurrentPlayer == mPlayers.end())
    {
        mCurrentPlayer = mPlayers.begin();
        onNewRound();
    }
}

bool StateConstellation::isCurrentPlayer(const PlayerID& id)  const
{
    return (*mCurrentPlayer)->character()->id() == id;
}

void StateConstellation::onArrowDecayed()
{
    mIState = {nullptr,&StateConstellation::defaultEvent};
    nextPlayer();
}

sf::FloatRect StateConstellation::getBounds(float margin) const
{
    float xmin(0),xmax(0),ymin(0),ymax(0);
    for(const SharedPlanet& p : mPlanets)
    {
        xmin = min(xmin,p->get3DPos().x-p->getRadius());
        xmax = max(xmax,p->get3DPos().x+p->getRadius());
        ymin = min(ymin,p->get3DPos().y-p->getRadius());
        ymax = max(ymax,p->get3DPos().y+p->getRadius());
    }
    return {xmin-margin,ymin-margin,xmax-xmin+margin,ymax-ymin+margin};
}

void StateConstellation::correctViews(float vx, float vy)
{
    mView.setCenter(0,0);
    mBackView.setSize(vx,vy);
    //mBackView.zoom(2.f);
    sf::FloatRect bounds = getBounds(150);
    float bratio = bounds.height / bounds.width;
    float vratio = vy / vx;
    if(bratio > vratio)
    {
        //Use y as reference
        mView.setSize(bounds.height/vratio,bounds.height);
    }
    else
    {
        //Use x as reference
        mView.setSize(bounds.width,bounds.width*vratio);
    }
}

std::vector<sf::Vector2f> StateConstellation::pathForInitials(sf::Vector2f pos, sf::Vector2f speed, int precision) const
{
    std::vector<sf::Vector2f> path;
    auto cstate = std::static_pointer_cast<StateConstellation>(Core::get().currentState());
    path.reserve(precision);
    //TODO tweak
    float delta_t = 1.f/60;
    constexpr unsigned substeps = 5;
    float udelta = delta_t/substeps;
    for(int i = 0; i < precision; i++)
    {
        for(int j = 0; j < substeps; j++)
        {
            using namespace std::placeholders;
            integrateEC(pos, speed, udelta, std::bind(&StateConstellation::getGravFieldAt, cstate.get(), _1));
        }
        if(collideWithPlanet(pos))
            break;
        path.push_back(pos);
    }
    return path;
}

sf::Vector2f StateConstellation::clampRect(const sf::FloatRect& rect, float margin) const
{
    sf::FloatRect bounds = {mView.getCenter().x-mView.getSize().x/2,
                            mView.getCenter().y-mView.getSize().y/2,
                            mView.getSize().x,
                            mView.getSize().y};
    float x = min(max(bounds.left+margin,rect.left),bounds.left+bounds.width-margin-rect.width);
    float y = min(max(bounds.top+margin,rect.top),bounds.top+bounds.height-margin-rect.height);
    return {x,y};
}

float StateConstellation::zoomFactor() const
{
    return mView.getSize().y / Core::get().renderWindow().getSize().y;
}
