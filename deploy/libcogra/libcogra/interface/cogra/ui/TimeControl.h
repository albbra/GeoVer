#pragma once
#ifndef COGRA_UI_TIMECONTROL_H
#define COGRA_UI_TIMECONTROL_H
#include <cogra/types.h>
namespace cogra
{
namespace ui
{
class TimeControl
{
public:
    TimeControl();

    bool isPause() const;

    bool isStop() const;

    void play();

    void stop();

    void pause();

    float64 getTime();

    void setTime(float64 t);

    void setPeriode(float64 periode);

    float64 getPeriode() const;

    bool isPeriodic() const;

    void setSpeed(float64 speed);

    float64 getSpeed() const;    

private:    

    enum State { STOP, PLAY, PAUSE };
    
    State m_state;       

    float64 m_speed;

    float64 m_periode;

    float64 m_currentTime;

    float64 m_previousSystemTime;

    float64 periodicTime(float64 t) const;

};

}
}
#endif