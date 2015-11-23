#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <memory>

class Timer;

typedef std::shared_ptr<Timer> SharedTimer;

class Timer
{
public:
    Timer(float duration, std::function<void()> callback);
    static SharedTimer create(float duration, std::function<void()> callback);
    bool tick(float time);
    void setTimeStamp(float t);
private:
    float mTimeStamp;
    float mDuration;
    std::function<void()> mCallback;
};

#endif // TIMER_H
