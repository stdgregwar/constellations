#include "StateConstellation.h"
#include "Core.h"

StateConstellation::StateConstellation()
{
}

void StateConstellation::onBegin()
{
    mPlanets.push_back({{0,0,0},1,20}); //Yes that's how we add a planet
    mCharacters.push_back({&mPlanets.back()});
}

void StateConstellation::onEnd()
{

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
    target.setView(view);
    for(Planet& p : mPlanets)
    {
        target.draw(p);
    }
    for(Character& c : mCharacters)
    {
        target.draw(c);
    }
}

void StateConstellation::update(float delta_s)
{

}
