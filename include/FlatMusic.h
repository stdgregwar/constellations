#ifndef FLATMUSIC_H
#define FLATMUSIC_H

#include "SmartMusic.h"
#include <string>

class FlatMusic : public SmartMusic
{
public:
    FlatMusic(std::string file);
    virtual void update(float delta_s);
    virtual void play();
    virtual void pause();
    virtual void stop();
    virtual void setVolume(float volume);
    ~FlatMusic();
private:
    sf::Music mMusic;
};

#endif // FLATMUSIC_H
