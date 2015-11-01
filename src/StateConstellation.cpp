#include "StateConstellation.h"
#include "Core.h"

#include <iostream>
#include "Mat4.h"

using namespace std;

StateConstellation::StateConstellation() :
    mIState({nullptr,&StateConstellation::defaultEvent}), mYaw(0), mPitch(0)
{
}

void StateConstellation::onBegin()
{
    mPlanets.push_back(SharedPlanet(new Planet{{-35,30,0},1,10}));
    mPlanets.push_back(SharedPlanet(new Planet{{35,-20,0},0.75,20}));
    mPlanets.push_back(SharedPlanet(new Planet{{35,20,-20},0.25,20}));
    mCharacters.push_back(SharedCharacter(new Character(mPlanets.back())));
    mArrows.push_back(SharedArrow(new Arrow({100,0},{0,100},0)));
}

void StateConstellation::onEnd()
{
    cout << "Ending constellation state" << endl;
    mPlanets.clear();
    mCharacters.clear();
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
    view.zoom(1.f/4);
    target.setView(view);

    for(SharedPlanet& p : mPlanets)
    {
        target.draw(*p);
    }

    for(SharedCharacter& c : mCharacters)
    {
        target.draw(*c);
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
    for(SharedCharacter& c: mCharacters)
    {
        c->rot(0);
        c->update(delta_s);
    }

    for(SharedArrow& a : mArrows)
    {
        a->update(delta_s);
        //TODO add collision support
    }
}

void StateConstellation::rotUpdate(float delta_s)
{
    constexpr float s = 1;
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
}

void StateConstellation::pushEvent(const sf::Event &e)
{
    if(mIState.ef)
        (*this.*mIState.ef)(e);
}

void StateConstellation::defaultEvent(const sf::Event &e)
{
    if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right){
        //const sf::Event::MouseButtonEvent& me = e;
        mOldMousePos = {e.mouseButton.x,e.mouseButton.y};
        mIState = {&StateConstellation::rotUpdate,&StateConstellation::rotEvent};
    }
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
    return field*(float)5e2;
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
    for(SharedCharacter& character : mCharacters)
    {
        if(character->collideWith(p)) return character;
    }
    return SharedCharacter();
}
