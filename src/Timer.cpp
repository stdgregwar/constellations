#include "Timer.h"
#include "Core.h"

using namespace std;

Timer::Timer(float duration, std::function<void()> callback)
    : mDuration(duration), mCallback(callback)
{
}


SharedTimer Timer::create(float duration, std::function<void()> callback)
{
    SharedTimer timer(new Timer(duration,callback));
    Core::get().addTimer(timer);
    return timer;
}


void Timer::setTimeStamp(float t)
{
    mTimeStamp = t;
}

bool Timer::tick(float time){
    if(time >= mTimeStamp+mDuration) {
        mCallback();
        return true;
    }
    return false;
}

