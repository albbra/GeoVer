/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/gl/PerformanceQueries.h>
#include <cogra/gl/OpenGLRuntimeError.h>
namespace cogra
{
    namespace gl
    {
        PerformanceQueries::PerformanceQueries(GLsizei nQueries)
            : m_queryIDBufferA(static_cast<size_t>(nQueries))
            , m_queryIDBufferB(static_cast<size_t>(nQueries))
            , m_frontBuffer(m_queryIDBufferA)
            , m_backBuffer(m_queryIDBufferB)
            , m_times(static_cast<size_t>(nQueries))
            , m_queryActive(false)
        {
            GL_SAFE_CALL(glGenQueries(nQueries, m_queryIDBufferA.data()));
            GL_SAFE_CALL(glGenQueries(nQueries, m_queryIDBufferB.data()));
            // issue a dummy query so that some data (probably 0) is in the m_frontBuffer
            for(GLuint x : m_frontBuffer)
            {
                GL_SAFE_CALL(glBeginQuery(GL_TIME_ELAPSED, x));
                GL_SAFE_CALL(glEndQuery(GL_TIME_ELAPSED));
            }
        }

        PerformanceQueries::~PerformanceQueries()
        {
            auto nQueries = getNumberOfQueries();
            glDeleteQueries(nQueries, m_queryIDBufferA.data());
            glDeleteQueries(nQueries, m_queryIDBufferB.data());
        }

        GLsizei PerformanceQueries::getNumberOfQueries() const
        {
            return (GLsizei)(m_queryIDBufferA.size());
        }

        bool PerformanceQueries::beginQuery(GLsizei queryID)
        {
            if(m_queryActive)
            {
                return false;
            }
            else
            {
                m_activeQueryID = queryID;
                GL_SAFE_CALL(glBeginQuery(GL_TIME_ELAPSED, m_backBuffer[queryID]));
                m_activeQueryID = queryID;
                m_queryActive = true;
                return true;
            }
        }

        bool PerformanceQueries::endQuery()
        {
            if(m_queryActive)
            {
                GL_SAFE_CALL(glEndQuery(GL_TIME_ELAPSED));
                m_queryActive = false;
                GLint available = 0;
                while(available == 0)
                {
                    glGetQueryObjectiv(m_frontBuffer[m_activeQueryID], GL_QUERY_RESULT_AVAILABLE, &available);
                }
                GL_SAFE_CALL(glGetQueryObjectui64v(m_frontBuffer[m_activeQueryID], GL_QUERY_RESULT, &m_times[m_activeQueryID]));
                return true;
            }
            else
            {
                return false;
            }
        }

        GLuint64 PerformanceQueries::getTimeInNanoSeconds(GLsizei queryID) const
        {
            return m_times[queryID];
        }

        float64 PerformanceQueries::getTimeInMilliSeconds(GLsizei queryID) const
        {
            return ((float64)m_times[queryID] * (float64)1e-6);
        }

        void PerformanceQueries::swap()
        {
            std::swap(m_frontBuffer, m_backBuffer);
        }
    }
}
