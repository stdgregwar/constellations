#ifndef SMARTMUSIC_H
#define SMARTMUSIC_H

#include <SFML/Audio/Music.hpp>
#include <memory>

class SmartMusic;

typedef std::shared_ptr<SmartMusic> SharedMusic;

class SmartMusic
{
public:
    SmartMusic();
    virtual void update(float delta_s) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void setVolume(float volume) = 0;
    virtual ~SmartMusic();
};

#endif // SMARTMUSIC_H
