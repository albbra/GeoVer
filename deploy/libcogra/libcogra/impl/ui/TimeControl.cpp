#include <cogra/ui/TimeControl.h>
#include <GLFW/glfw3.h>

namespace
{
static cogra::float64 getSystemTime()
{
    return glfwGetTime();
}
}
namespace cogra
{
namespace ui
{
TimeControl::TimeControl()
    : m_state(STOP)
    , m_speed(1.0)
    , m_periode(0)
    , m_currentTime(0)
    , m_previousSystemTime(0)
{

}

bool TimeControl::isPause() const
{
    return m_state == PAUSE;
}

bool TimeControl::isStop() const
{
    return m_state == STOP;
}

void TimeControl::play()
{
    if(m_state == PLAY)
    {
        return;
    }

    if(m_state == PAUSE)
    {
        m_previousSystemTime = getSystemTime();
        m_state = PLAY;
        return;
    }

    if(m_state == STOP)
    {
        m_previousSystemTime = getSystemTime();
        m_state = PLAY;
        m_currentTime = 0;
        return;
    }
}

void TimeControl::stop()
{
    m_state = STOP;
}

void TimeControl::pause()
{
    if(m_state == PAUSE)
    {
        return;
    }

    if(m_state == PLAY)
    {
        m_state = PAUSE;
        return;
    }
    if(m_state == STOP)
    {
        return;
    }
}

float64 TimeControl::getTime() 
{
    if(m_state == STOP)
    {
        return 0.0;
    } else
    if(m_state == PLAY)
    {
        const auto currentSystemTime = getSystemTime();
        const auto deltaT = currentSystemTime - m_previousSystemTime;        
        m_currentTime += m_speed * deltaT;        
        m_previousSystemTime = currentSystemTime;                
        return periodicTime(m_currentTime);
    } else //if(m_state == PAUSE)
    {        
        return periodicTime(m_currentTime);
    }
}

void TimeControl::setTime(float64 t)
{
    m_currentTime = t;
    m_previousSystemTime = getSystemTime();
}

void TimeControl::setPeriode(float64 periode)
{
    m_periode = periode;
}


float64 TimeControl::getPeriode() const
{
    return m_periode;
}

bool TimeControl::isPeriodic() const
{
    return m_periode != 0;
}

void TimeControl::setSpeed(float64 speed)
{
    m_speed = speed;
}
float64 TimeControl::getSpeed() const
{
    return m_speed;
}

float64 TimeControl::periodicTime(float64 t) const
{
    if(m_periode == 0.0)
    {
        return t;
    }
    else
    {
        return glm::clamp<float64>(glm::mod(t, m_periode), 0, m_periode);
    }
}
}
}