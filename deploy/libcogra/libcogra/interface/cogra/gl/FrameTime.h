/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_FRAMETIME_H_
#define COGRA_GL_FRAMETIME_H_
#include <cstdint>
#include <cogra/types.h>
//#include <glad/glad.h>
#include <cogra/tools/Timer.h>
using namespace glm;
namespace cogra
{
    namespace gl
    {
        //! FrameTime helps measuring wall-clock frame times for single frames and average frame times across multiple
        //! frames.
        class FrameTime
        {
        public:
            //! \brief Creates an object for determine frame time and frames per second.
            FrameTime();

            //! \brief Records the time.
            //! Call this function when starting a frame.
            void startFrame();

            //! \brief Returns the time measured between two successive StartFrame calls.
            //! \return Time in nanoseconds (that is 1e-9 seconds).
			float64  getTimeInNanoSeconds() const;

            //! Returns the time in milliseconds.
            //!\ return Time in milliseconds.
            float64 getTimeInMilliSeconds() const;

            //! \brief Returns the frames-per-second
            float64 getFramesPerSecond() const;

            //! \brief Returns the time measured over GetNumberOfFramesToAverageOver() StartFrame calls.
            //! \return Time in nanoseconds (that is 1e-9 seconds).
            float64 getAverageTimeInNanoSeconds() const;

            //! \brief Returns the time measured over GetNumberOfFramesToAverageOver() StartFrame calls.
            //!\ return Time in milliseconds.
            float64 getAverageTimeInMilliSeconds() const;

            //! \brief Returns the frames-per-second average over GetNumberOfFramesToAverageOver() frames.
            float64 getAverageFramesPerSecond() const;

            //! \brief Returns the number of frames to average over.
            uint32 getNumberOfFramesToAverageOver() const;

            //! \brief Sets the number of frames to average over.
            //! \param numberOfFramesToAverageOver Number of frames to average the time over.
            void setNumberOfFramesToAverageOver(uint32 numberOfFramesToAverageOver);

        private:
            //! Time stamp at the previous StartFrame call.
            float64  m_previousTimeStamp;

            //! Time stamp at the current StartFrame call.
			float64  m_currentTimeStamp;

            //! Time stamp at the time the last average period started.
			float64  m_previousAverageTimeStamp;

            //! Time stamp at the time the current average period started.
			float64  m_currentAverageTimeStamp;

            //! Number of frames to average the frame time over.
            uint32   m_numberOfFramesToAverageOver;

            //! Counts the number of frames in an averaging period.
            uint32    m_numberOfFrames;

			Timer m_timer;
        };
    }
}
#endif
