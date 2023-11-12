/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/graphics/geometry/IndexGrid.h>
#include <cogra/exceptions/RuntimeError.h>
namespace cogra
{
    namespace graphics
    {
        namespace geometry
        {
            IndexGrid::IndexGrid(size_t nVerticesX, size_t nVerticesY)
                : m_nVerticesX(nVerticesX)
                , m_nVerticesY(nVerticesY)
            {
                if(m_nVerticesX <= 1 || m_nVerticesY <= 1)
                {
                    Throw(cogra::exceptions::RuntimeError, "Invalid grid size:" << m_nVerticesX << " * " << m_nVerticesY << ".");
                }
                m_indices.reserve((m_nVerticesX - 1) * (m_nVerticesY - 1) * 2);
                for(size_t yIdx = 0; yIdx < m_nVerticesY - 1; yIdx++)
                {
                    for(size_t xIdx = 0; xIdx < m_nVerticesX - 1; xIdx++)
                    {
                        const size_t idx00 = (xIdx + 0) + (yIdx + 0) * m_nVerticesX;
                        const size_t idx10 = (xIdx + 1) + (yIdx + 0) * m_nVerticesX;
                        const size_t idx11 = (xIdx + 1) + (yIdx + 1) * m_nVerticesX;
                        const size_t idx01 = (xIdx + 0) + (yIdx + 1) * m_nVerticesX;

                        m_indices.push_back((uint32)idx00);
                        m_indices.push_back((uint32)idx01);
                        m_indices.push_back((uint32)idx10);

                        m_indices.push_back((uint32)idx10);
                        m_indices.push_back((uint32)idx01);
                        m_indices.push_back((uint32)idx11);
                    }
                }
            }

            size_t IndexGrid::getNumberOfVerticesX() const
            {
                return m_nVerticesX;
            }

            size_t IndexGrid::getNumberOfVerticesY() const
            {
                return m_nVerticesY;
            }

            const uint32* const IndexGrid::getIndicesPtr() const
            {
                return m_indices.data();
            }

            size_t IndexGrid::getNumberOfIndices() const
            {
                return m_indices.size();
            }

            size_t IndexGrid::getNumberOfVertices() const
            {
                return getNumberOfVerticesX() * getNumberOfVerticesY();
            }
        }
    }
}
