#include <cogra/tools/Timer.h>


namespace cogra
{

Timer::Timer()
{
}

void Timer::start()
{
    m_startTime = std::chrono::high_resolution_clock::now();
}

void Timer::pause()
{
    m_pauseTime = std::chrono::high_resolution_clock::now();
    isPaused = true;
}

void Timer::resume() {
    if(!isPaused) return;

    isPaused = false;
    auto curTime = std::chrono::high_resolution_clock::now();
    m_startTime += curTime - m_pauseTime;
}

float64 Timer::getTimeInMilliseconds() const
{
    auto end = std::chrono::high_resolution_clock::now();
    auto deltaT = end - m_startTime;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(deltaT).count()*0.000001;
}

float64 Timer::getTimeInNanoSeconds() const
{
	auto end = std::chrono::high_resolution_clock::now();
	auto deltaT = end - m_startTime;
	return static_cast<float64>(std::chrono::duration_cast<std::chrono::nanoseconds>(deltaT).count());
}


float64 Timer::getTimeInSeconds() const
{
    return getTimeInMilliseconds() * 0.001;
}
}
