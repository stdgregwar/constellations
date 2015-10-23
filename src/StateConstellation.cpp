#include "StateConstellation.h"
#include "Core.h"
#include <iostream>

using namespace std;

StateConstellation::StateConstellation()
{
}

void StateConstellation::onBegin()
{
    mPlanets.push_back(SharedPlanet(new Planet{{-35,30,0},1,20}));
    mCharacters.push_back(SharedCharacter(new Character(mPlanets.back())));
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
    sf::View view = target.getDefaultView();
    view.setCenter(0,0);
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
}

void StateConstellation::update(float delta_s)
{
    for(SharedCharacter& c: mCharacters)
    {
        c->rot(0.03);
        c->update(delta_s);
    }
}
