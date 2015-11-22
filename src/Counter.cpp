#include "Counter.h"
#include "Core.h"
#include <string>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace std;

Counter::Counter(sf::Color color, int characterSize, sf::Font *font)
{
    mMain.setColor(color);
    mMain.setCharacterSize(characterSize);
    mSecond.setColor(color);
    mSecond.setCharacterSize(float(characterSize)*0.5);
    if(font){
      mMain.setFont(*font);
      mSecond.setFont(*font);
    } else {
        mSecond.setFont(*Core::get().fontCache().get("default"));
        mMain.setFont(*Core::get().fontCache().get("default"));
    }
}

void Counter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mMain,sf::RenderStates(getTransform()));
    target.draw(mSecond,sf::RenderStates(getTransform()));
}

sf::FloatRect Counter::bounds() const
{
    sf::FloatRect r1 = mMain.getGlobalBounds();
    sf::FloatRect r2 = mSecond.getGlobalBounds();
    float left = min(r1.left,r2.left);
    float top = min(r1.top,r2.top);
    float right = max(r1.left+r1.width,r2.left+r2.width);
    float bot = max(r1.top+r1.height,r2.top+r2.height);
    return {left,top,right-left,bot-top};
}

void Counter::setValue(float value)
{
    int ival = int(value); //
    int dval = int((value-ival)*100);
    mMain.setString(to_string(ival));
    mMain.setPosition(0,0);
    mSecond.setString("."+to_string(dval));
    mSecond.setPosition(mMain.getLocalBounds().width+4,mSecond.getLocalBounds().height*2);
    mValue = value;
}

float Counter::getValue() const
{
    return mValue;
}
