/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/graphics/geometry/SphereGeometry.h>
namespace cogra
{
    namespace graphics
    {
        namespace geometry
        {
            SphereGeometry::SphereGeometry(uint32 nSamplesTheta, uint32 nSamplesPhi, float32 radius)
            {
                nSamplesTheta = glm::max(1u, nSamplesTheta);
                nSamplesPhi = glm::max(1u, nSamplesPhi);

                // Generate the interior samples of the sphere.
                for(uint32 i = 1; i < nSamplesTheta; i++)
                {
                    float32 u = static_cast<float32>(i) / static_cast<float32>(nSamplesTheta);
                    float32 theta = u * glm::pi<float32>();
                    float32 sinTheta = glm::sin(theta);
                    float32 cosTheta = glm::cos(theta);
                    for(uint32 j = 0; j < nSamplesPhi; j++)
                    {
                        float32 v = static_cast<float32>(j) / static_cast<float32>(nSamplesPhi);
                        float32 phi = v * 2.0f * glm::pi<float32>();
                        float32 sinPhi = glm::sin(phi);
                        float32 cosPhi = glm::cos(phi);
                        f32vec3 normal(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
                        m_positions.push_back(radius * normal);
                        m_normals.push_back(normal);
                        m_texCoords.emplace_back(u, v);
                    }
                }
                // Tessellate the interior of the sphere.
                for(uint32 i = 0; i < nSamplesTheta - 2; i++)
                {
                    for(uint32 j = 0; j < nSamplesPhi; j++)
                    {
                        m_indexBuffer.push_back(((i + 0)) * nSamplesPhi + ((j + 0) % nSamplesPhi));
                        m_indexBuffer.push_back(((i + 1)) * nSamplesPhi + ((j + 1) % nSamplesPhi));
                        m_indexBuffer.push_back(((i + 0)) * nSamplesPhi + ((j + 1) % nSamplesPhi));

                        m_indexBuffer.push_back(((i + 1)) * nSamplesPhi + ((j + 0) % nSamplesPhi));
                        m_indexBuffer.push_back(((i + 1)) * nSamplesPhi + ((j + 1) % nSamplesPhi));
                        m_indexBuffer.push_back(((i + 0)) * nSamplesPhi + ((j + 0) % nSamplesPhi));
                    }
                }

                // Add vertices at the poles.
                m_positions.emplace_back(0, 0, radius);
                m_normals.emplace_back(0, 0, 1);
                m_texCoords.emplace_back(0, 0);
                const auto northPoleIndex = static_cast<uint32>(m_positions.size() - 1);

                m_positions.emplace_back(0, 0, -radius);
                m_normals.emplace_back(0, 0, -1);
                m_texCoords.emplace_back(1, 0);
                const auto southPoleIndex = static_cast<uint32>(m_positions.size() - 1);

                // Tessellate the north pole.
                for(uint32 j = 0; j < nSamplesPhi; j++)
                {
                    m_indexBuffer.push_back(northPoleIndex);
                    m_indexBuffer.push_back((0) * nSamplesPhi + ((j) % nSamplesPhi));
                    m_indexBuffer.push_back((0) * nSamplesPhi + ((j + 1) % nSamplesPhi));
                }

                // Tessellate the south pole.
                for(uint32 j = 0; j < nSamplesPhi; j++)
                {
                    m_indexBuffer.push_back(southPoleIndex);
                    m_indexBuffer.push_back((nSamplesTheta - 2) * nSamplesPhi + ((j + 1) % nSamplesPhi));
                    m_indexBuffer.push_back((nSamplesTheta - 2) * nSamplesPhi + ((j) % nSamplesPhi));
                }
            }

            const std::vector<f32vec3>& SphereGeometry::getPositions() const
            {
                return m_positions;
            }

            std::vector<f32vec3>& SphereGeometry::getPositions()
            {
                return m_positions;
            }

            const f32vec3* const SphereGeometry::getPositionsPtr() const
            {
                return m_positions.data();
            }

            std::vector<f32vec3>& SphereGeometry::getNormals()
            {
                return m_normals;
            }

            const std::vector<f32vec3>& SphereGeometry::getNormals() const
            {
                return m_normals;
            }

            std::vector<uint32>& SphereGeometry::getIndexBuffer()
            {
                return m_indexBuffer;
            }

            const std::vector<uint32>& SphereGeometry::getIndexBuffer() const
            {
                return m_indexBuffer;
            }

            const uint32* const SphereGeometry::getIndexBufferPtr() const
            {
                return m_indexBuffer.data();
            }

            size_t SphereGeometry::getNumVertices() const
            {
                return m_positions.size();
            }

            size_t SphereGeometry::getNumTriangles() const
            {
                return m_indexBuffer.size() / 3;
            }

            size_t SphereGeometry::getNumIndices() const
            {
                return m_indexBuffer.size();
            }

            const f32vec3* const SphereGeometry::getNormalsPtr() const
            {
                return m_normals.data();
            }
        }
    }
}
