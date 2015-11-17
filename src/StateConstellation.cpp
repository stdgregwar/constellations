#include "StateConstellation.h"
#include "Core.h"


#include <iostream>
#include <algorithm>
#include "Mat4.h"
#include "KeyboardController.h"

using namespace std;

StateConstellation::StateConstellation() :
    mIState({nullptr,&StateConstellation::defaultEvent}), mYaw(0), mPitch(0)
{
}

void StateConstellation::onBegin()
{

    sf::Texture tex;
    tex.loadFromFile("data/stars_w_4.png");
    mBackground.setTexture(tex,4);
    mBackground.uniformDistribution({-1280,-720,1280*2,720*2},500);

    mPlanets.push_back(SharedPlanet(new Planet({-100,80,0},1,25)));
    mPlanets.push_back(SharedPlanet(new Planet({140,80,0},0.75,25)));
    mPlanets.push_back(SharedPlanet(new Planet({0,-160,0},0.25,25)));
    mPlayers.push_back(SharedController( //Ugliest in-place construction ever
                           new KeyboardController(
                               SharedCharacter(
                                   new Character(
                                                   mPlanets.back(),1,sf::Color(255,150,150)
                                                   )
                                    )
                               )
                           )
                       );
    mPlayers.push_back(SharedController( //Same same... but different
                           new KeyboardController(
                               SharedCharacter(
                                   new Character(
                                       mPlanets.front(),2,sf::Color(150,150,255))
                                   )
                               )
                           )
                       );
    //mArrows.push_back(SharedArrow(new Arrow({100,0},{0,100},0)));

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
    sf::View view;
    view.setCenter(0,0);
    view.setViewport({0,0,1,1});
    view.setSize(target.getSize().x,target.getSize().y);

    target.setView(view);
    target.draw(mBackground);
    view.zoom(1.f/2);

    target.setView(view);


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
}

void StateConstellation::update(float delta_s)
{
    if(mIState.uf)
        (*this.*mIState.uf)(delta_s); //Call ptr on function

    defaultUpdate(delta_s);
}

void StateConstellation::defaultUpdate(float delta_s)
{
    for(SharedController& c : mPlayers)
    {
        c->character()->update(delta_s);
    }

    for(SharedArrow& a : mArrows)
    {
        a->update(delta_s);
        //TODO add collision support
    }

    /*mPlayers.remove_if(
                [](const SharedController& c)->bool{return c->character()->isDead();}
    );*/
    for(Players::iterator it = mPlayers.begin(); it != mPlayers.end(); it++)
    {
        if((*it)->character()->isDead()) {
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
    if(mCurrentPlayer != mPlayers.end() && mPlayers.size()) {
        if((*mCurrentPlayer)->onEvent(e)){
            nextPlayer();
        }
    }
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
}

void StateConstellation::rotEvent(const sf::Event &e)
{
    if(e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Right)
        mIState = {nullptr,&StateConstellation::defaultEvent};
    if(e.type == sf::Event::MouseMoved)
        mMousePos = {e.mouseMove.x,e.mouseMove.y};
}

sf::Vector2f StateConstellation::getGravFieldAt(const sf::Vector2f &p)
{
    sf::Vector2f field;
    for(SharedPlanet& planet : mPlanets)
    {
        field += planet->get2DField(p);
    }
    return field*(float)25e2;
}

SharedPlanet StateConstellation::collideWithPlanet(const sf::Vector2f &p)
{
    for(SharedPlanet& planet : mPlanets)
    {
        if(planet->collideWith(p)) return planet;
    }
    return SharedPlanet();
}

SharedCharacter StateConstellation::collideWithCharacter(const sf::Vector2f &p)
{
    for(SharedController c : mPlayers)
    {
        if(c->character()->collideWith(p)) return c->character();
    }
    return SharedCharacter();
}

void StateConstellation::pushArrow(SharedArrow a)
{
    mArrows.push_back(a);
}

void StateConstellation::onNewRound()
{
    cout << "New ROUND!!" << endl;
}

void StateConstellation::onWin()
{
    cout << "Player Won" << endl;
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

std::vector<sf::Vector2f> StateConstellation::pathForInitials(sf::Vector2f pos, sf::Vector2f speed, int precision)
{
    std::vector<sf::Vector2f> path;
    path.reserve(precision);
    //TODO tweak
    float delta_t = 1.f/60;
    constexpr unsigned substeps = 5;
    float udelta = delta_t/substeps;
    for(int i = 0; i < precision; i++)
    {
        for(int j = 0; j < substeps; j++)
        {
            sf::Vector2f acc = getGravFieldAt(pos);
            speed += acc * udelta;
            pos += speed * udelta;
        }
        if(collideWithPlanet(pos))
            break;
        path.push_back(pos);
    }
    return path;
}
