#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "Button.h"
#include <SFML/Graphics/Text.hpp>

class ComboBox : public Widget
{
    typedef std::map<unsigned,std::string> Choices;
public:
    ComboBox(const Choices& choices,unsigned def, std::function<void(unsigned id)> callback, unsigned csize = 50, const sf::Color& hoverColor = sf::Color::Yellow, const sf::Color& mainColor = sf::Color::White);
    void clicked();
    void choose(unsigned id);
    void show();
    bool onEvent(const sf::Event &e, const sf::View &view);
private:
    void showChoices();
    void hideChoices();

    Choices mChoices;
    unsigned mDefault;
    SharedButton mMainButton;
    std::function<void(unsigned id)> mCallback;
    std::vector<SharedWidget> mBChoices;
    sf::FloatRect mBounds;
    bool mDeployed;
};

#endif // COMBOBOX_H
