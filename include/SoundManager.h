#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include "SmartMusic.h"

class SoundManager
{
public:
    enum FadePolicy{
        DIRECT,
        CHAINED,
        IN_OUT
    };

    enum State{
        IDLE,
        FIRST,
        MIDDLE,
        SECOND
    };

    SoundManager();
    void update(float delta_s);
    void play(SharedMusic m, float duration = 0, FadePolicy f = DIRECT);
    void stop(float duration = 1);
    ~SoundManager();
private:
    SharedMusic mMusic;
    SharedMusic mSecondary;
    FadePolicy mFadePolicy;
    State mState;
    float mDuration;
    float mStartTime;

};

#endif // SOUNDMANAGER_H
