/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_GEOMETRY_INDEXGRID_H_
#define COGRA_GRAPHICS_GEOMETRY_INDEXGRID_H_
#include <cogra/types.h>
#include <vector>
using namespace glm;
namespace cogra
{
    namespace graphics
    {
        namespace geometry
        {
            //! A class for a 2D grid.
            class IndexGrid
            {
            public:
                //! \brief Creates a 2D grid.
                //! \param[in,out]  nVerticesX Number of vertices in horizontal direction.
                //! \param[in,out]  nVerticesY Number of vertices in vertical direction.
                IndexGrid(size_t nVerticesX, size_t nVerticesY);

                //! \brief Returns the number of vertices in x direction.
                size_t getNumberOfVerticesX() const;

                //! \brief Returns the number of vertices in y direction.
                size_t getNumberOfVerticesY() const;

                //! \brief Returns a pointer to the index buffer.
                const uint32* const getIndicesPtr() const;

                //! \brief Returns the number of indices.
                size_t getNumberOfIndices() const;

                //! \brief Returns the number of vertices.
                size_t getNumberOfVertices() const;

            private:
                std::vector<uint32>         m_indices;
                size_t                      m_nVerticesX;
                size_t                      m_nVerticesY;
            };
        }
    }
}
#endif
