#include "../include/SoundManager.h"
#include "Core.h"

SoundManager::SoundManager() : mState(IDLE), mFadePolicy(DIRECT)
{

}

void SoundManager::update(float delta_s)
{
    if(mSecondary)
        mSecondary->update(delta_s);

    if(mMusic)
        mMusic->update(delta_s);

    switch(mState)
    {
        case IDLE:
            return;
        case FIRST:
            switch(mFadePolicy){
                case CHAINED:
                {
                    float factor = (Core::get().time() - mStartTime) / mDuration;
                    if(mMusic)
                        mMusic->setVolume(100-factor*100);
                    if(mSecondary)
                        mSecondary->setVolume(factor*100);

                    if(factor > 1) {
                        mState = IDLE;
                        mMusic->pause();
                        mMusic = mSecondary;
                        mSecondary.reset();
                    }
                    break;
                }
                case IN_OUT:
                {
                    float factor = (Core::get().time() - mStartTime)*3 / mDuration;
                    if(mMusic)
                        mMusic->setVolume(100-factor*100);

                    if(factor > 1) {
                        mStartTime = Core::get().time();
                        mState = MIDDLE;
                        if(mSecondary)
                            mMusic = mSecondary;
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        case MIDDLE:
        {
            float factor = (Core::get().time() - mStartTime)*3 / mDuration;
            if(factor > 1)
            {
                mStartTime = Core::get().time();
                mState = SECOND;
            }
            break;
        }
        case SECOND:
        {
            float factor = (Core::get().time() - mStartTime)*3 / mDuration;
            if(mMusic)
                mMusic->setVolume(factor*100);

            if(factor > 1) {
                mState = IDLE;
                if(mSecondary) {
                    mMusic = mSecondary;
                    mSecondary.reset();
                }
            }
            break;
        }
    }
}

void SoundManager::play(SharedMusic m, float duration, FadePolicy f)
{
    if(m == mMusic)
        return;

    mDuration = duration;
    mStartTime = Core::get().time();
    mFadePolicy = f;
    switch(mFadePolicy){
        case DIRECT:
            if(mMusic)
                mMusic->stop();
            mMusic = m;
            if(mSecondary)
                mSecondary->pause();
            mSecondary.reset();
            mMusic->play();
            break;
        case CHAINED:
            m->play();
        case IN_OUT:
            if(mSecondary)
                mSecondary->pause();
            mSecondary = m;
            mState = FIRST;
            break;
        default:
            break;
    }
}

void SoundManager::stop(float duration)
{
    mDuration = duration;
    if(duration == 0.f)
    {
        mMusic->stop();
        mSecondary->stop();
        mState = IDLE;
    }
    else
    {
        mFadePolicy = CHAINED;
        mState = FIRST;
    }
}

SoundManager::~SoundManager()
{

}

