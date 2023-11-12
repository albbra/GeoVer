/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/gl/FrameTime.h>
#include <cogra/tools/Timer.h>
using namespace glm;
namespace cogra
{
    namespace gl
    {
        FrameTime::FrameTime()
            : m_previousTimeStamp(0)
            , m_currentTimeStamp(0)
            , m_previousAverageTimeStamp(0)
            , m_currentAverageTimeStamp(0)
            , m_numberOfFramesToAverageOver(64)
            , m_numberOfFrames(0)
        {
			m_previousTimeStamp = m_timer.getTimeInNanoSeconds();
			m_currentTimeStamp = m_timer.getTimeInNanoSeconds();
        }

        void FrameTime::startFrame()
        {
            m_previousTimeStamp = m_currentTimeStamp;
			m_currentTimeStamp = m_timer.getTimeInNanoSeconds();
            if(m_numberOfFrames >= m_numberOfFramesToAverageOver)
            {
                m_previousAverageTimeStamp = m_currentAverageTimeStamp;
                m_currentAverageTimeStamp = m_currentTimeStamp;
                m_numberOfFrames = 0;
            }

            m_numberOfFrames++;
        }

		float64  FrameTime::getTimeInNanoSeconds() const
        {
            return m_currentTimeStamp - m_previousTimeStamp;
        }

        float64 FrameTime::getTimeInMilliSeconds() const
        {
            return (float64)(getTimeInNanoSeconds()) * 1e-6;
        }

        float64 FrameTime::getFramesPerSecond() const
        {
            const float64 nanoSecondsPerSeconds = 1e9;
            return (nanoSecondsPerSeconds / (float64)(getTimeInNanoSeconds()));
        }

        float64 FrameTime::getAverageTimeInNanoSeconds() const
        {
            return static_cast<float64>(m_currentAverageTimeStamp - m_previousAverageTimeStamp)/ static_cast<float64>(m_numberOfFramesToAverageOver);
        }

        float64 FrameTime::getAverageTimeInMilliSeconds() const
        {
            return getAverageTimeInNanoSeconds() * 1e-6;
        }

        float64 FrameTime::getAverageFramesPerSecond() const
        {
            const float64 nanoSecondsPerSeconds = 1e9;
            return (nanoSecondsPerSeconds / (float64)(getAverageTimeInNanoSeconds()));
        }

        uint32 FrameTime::getNumberOfFramesToAverageOver() const
        {
            return m_numberOfFramesToAverageOver;
        }

        void FrameTime::setNumberOfFramesToAverageOver(uint32 numberOfFramesToAverageOver)
        {
            m_numberOfFramesToAverageOver = numberOfFramesToAverageOver;
        }
    }
}
