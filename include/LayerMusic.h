#ifndef LAYERMUSIC_H
#define LAYERMUSIC_H

#include "SmartMusic.h"
#include <string>
#include <map>

class LayerMusic;

typedef std::shared_ptr<LayerMusic> SharedLayerMusic;

class LayerMusic : public SmartMusic
{
public:
    LayerMusic(std::map<std::string,std::string>&& musics);
    virtual void update(float delta_s);
    virtual void play();
    virtual void pause();
    virtual void stop();
    virtual void setVolume(float volume);
    void switchTo(std::string name, float duration = 0.5f);
    ~LayerMusic();
private:
    typedef std::map<std::string,sf::Music> Musics;
    float mBaseVolume;
    float mDuration;
    float mStartTime;
    Musics mMusics;
    Musics::iterator mTo;
    Musics::iterator mFrom;
};

#endif // LAYERMUSIC_H
