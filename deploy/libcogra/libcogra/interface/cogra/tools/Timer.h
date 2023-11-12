#pragma once
#ifndef COGRA_TIMER_H
#define COGRA_TIMER_H
#include <cogra/types.h>

#include <chrono>
namespace cogra
{
class Timer
{
public:
    Timer();

    void start();
    void pause();
    void resume();

    float64 getTimeInMilliseconds() const;

	float64 getTimeInNanoSeconds() const;

    float64 getTimeInSeconds() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock>   m_startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock>   m_pauseTime;
    bool isPaused = false;
};
}
#endif