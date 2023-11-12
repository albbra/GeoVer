/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_PERFORMANCEQUERIES_H_
#define COGRA_GL_PERFORMANCEQUERIES_H_
#include <cogra/types.h>
#include <glad/glad.h>
#include <vector>

using namespace glm;
namespace cogra
{
    namespace gl
    {
        class PerformanceQueries
        {
        public:
            explicit PerformanceQueries(GLsizei nQueries);

            ~PerformanceQueries();

            GLsizei getNumberOfQueries() const;

            bool beginQuery(GLsizei queryID);

            bool endQuery();

            GLuint64 getTimeInNanoSeconds(GLsizei queryID) const;

            float64 getTimeInMilliSeconds(GLsizei queryID) const;

            void swap();

        private:

            std::vector< GLuint > m_queryIDBufferA;
            std::vector< GLuint > m_queryIDBufferB;

            std::vector< GLuint >&  m_frontBuffer;
            std::vector< GLuint >&  m_backBuffer;

            std::vector<GLuint64>   m_times;

            GLsizei                 m_activeQueryID;
            bool                    m_queryActive;
        };
    }
}
#endif
