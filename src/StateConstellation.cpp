#include "StateConstellation.h"
#include "Core.h"

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

sf::Vector2f StateConstellation::getGravFieldAt(const sf::Vector2f &p)
{
    sf::Vector2f field;
    for(SharedPlanet& planet : mPlanets)
    {
        field += planet->get2DField(p);
    }
    return field;
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
}
