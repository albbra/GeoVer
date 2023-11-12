/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_GEOMETRY_SPHEREGEOMETRY_H_
#define COGRA_GRAPHICS_GEOMETRY_SPHEREGEOMETRY_H_
#include <cogra/types.h>
#include <vector>

namespace cogra
{
    namespace graphics
    {
        namespace geometry
        {
            //! \brief A triangle tessellation of a sphere.
            class SphereGeometry
            {
            public:
                //! \brief Creates a triangle tessellation of a sphere.
                //! The sphere is sampled in polar coordinates.
                //! \param[in,out]  nSamplesTheta Number of samples along the longitude axis.
                //! \param[in,out]  nSamplesPhi Number of samples along the latitude axis.
                //! \param[in,out]  radius Radius of the sphere.
                SphereGeometry(uint32 nSamplesTheta, uint32 nSamplesPhi, float32 radius);

                //! \return Returns the positions as vector.
                std::vector<f32vec3>& getPositions();

                //! \return Returns the positions as vector.
                const std::vector<f32vec3>& getPositions() const;

                //! \return Returns a pointer to the positions.
                const f32vec3* const getPositionsPtr() const;

                //! \return Returns the normal vectors as a vectors.
                std::vector<f32vec3>& getNormals();

                //! \return Returns the normal vectors as a vectors.
                const std::vector<f32vec3>& getNormals() const;

                //! \return Returns the normal vectors as a vectors.
                const f32vec3* const getNormalsPtr() const;

                //! \return Returns index buffer as vector.
                std::vector<uint32>& getIndexBuffer();

                //! \return Returns index buffer as vector.
                const std::vector<uint32>& getIndexBuffer() const;

                //! \return Returns index buffer as vector.
                const uint32* const getIndexBufferPtr() const;

                //! \return Returns the number of vertices.
                size_t getNumVertices() const;

                //! \return Returns the number of triangles.
                size_t getNumTriangles() const;

                //! \return Returns the number of indices..
                size_t getNumIndices() const;

            private:
                std::vector<f32vec3>			m_positions;
                std::vector<f32vec3>			m_normals;
                std::vector<f32vec2>			m_texCoords;
                std::vector<uint32>			    m_indexBuffer;
            };
        }
    }
}
#endif
