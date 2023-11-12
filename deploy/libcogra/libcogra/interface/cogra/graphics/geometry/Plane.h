/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_GEOMETRY_PLANE_H_
#define COGRA_GRAPHICS_GEOMETRY_PLANE_H_
#include <cogra/graphics/geometry/CorrespondingTypes.h>
namespace cogra
{
    namespace graphics
    {
        namespace geometry
        {
            //! \brief Class for multi-dimensional planes.
            //! \tparam A vector type. We recommomend using glm::detail::vec2, glm::detail::vec3, or f32vec4.
            template<class VECTOR_TYPE>
            class Plane
            {
            public:
                //! Type of the vector used for the normal vector of the plane.
                typedef VECTOR_TYPE vector_type;

                //! Type for indices and sizes.
                typedef size_t size_type;

                //! Type of the scalar values.
                typedef typename VECTOR_TYPE::value_type value_type;

                //! \brief Creates an invalid plane, with all values set to zero.
                Plane()
                    : m_normalVector(0)
                    , m_distance(0)
                { }

                //! \brief Constructs a plane from a normal vector (not necessarily unit vector) and distance.
                //! \param[in]  normalVector Normal vector (need not to be
                //! \param[in]  distance Signed and weighted distance
                Plane(const vector_type& normalVector, const value_type distance)
                    : m_normalVector(normalVector)
                    , m_distance(distance)
                { }

                //! \brief Constructs a plane from normal vector and a point on the plane
                //! \param[in]  normalVector Normal vector of the plane.
                //! \param[in]  pointOnPlane Point on the plane.
                Plane(const vector_type& normalVector, const vector_type& pointOnPlane)
                    : m_normalVector(normalVector)
                    , m_distance(glm::dot(m_normalVector, pointOnPlane))
                { }

                //! \brief Explicit conversion from a vector.
                //! \param[in]  v The first elements contain the components of the normal vector, the last element contains
                //!             plane displacement.
                explicit Plane(typename getUpperDimensionVectorType<value_type, vector_type>::vector_type v)
                {
                    for(auto i = 0; i < v.length() - 1; i++)
                    {
                        m_normalVector[i] = v[i];
                    }
                    m_distance = v[v.length() - 1];
                }

                typename getUpperDimensionVectorType<value_type, vector_type>::vector_type toVector() const
                {
                    typename getUpperDimensionVectorType<value_type, vector_type>::vector_type v;
                    for(size_type i = 0; i < v.length() - 1; i++)
                    {
                        v[i] = m_normalVector[i];
                    }
                    v[v.length() - 1] = m_distance;
                    return v;
                }

                //! \brief Evaluates the plane for vector x.
                //! \param[in] x Point.
                //! \return Returns zero, if the point x is exactly on the plane. The result is negative the x is on side of the
                //! plane into which the normal vector points. The result is positive, if x is on the other side. If  the plane is
                //! normalized, the result is the signed perpendicular distance from the point x to the plane.
                //! corresponds
                value_type evaluate(const vector_type& x) const
                {
                    return glm::dot(m_normalVector, x) + m_distance;
                }

                //! \brief Returns a normalized plane.
                Plane<vector_type> getNormalized() const
                {
                    Plane<vector_type> result = *this;
                    result.normalize();
                    return result;
                }

                //! \brief Normalizes the plane.
                void normalize()
                {
                    value_type lInv = value_type(1) / glm::length(m_normalVector);
                    m_normalVector *= lInv;
                    m_distance *= lInv;
                }

                //! \brief Returns the perpendicular vector (not unit, though) vector that defines that orientation of the plane.
                const vector_type& getNormalVector() const { return m_normalVector; }

                //! \brief Sets the perpendicular vector (not unit, though) vector that defines that orientation of the plane.
                void detNormalVector(const vector_type& val) { m_normalVector = val; }

                //! \brief Returns the distance of the plane to the origin (scaled by the length of the plane's normal vector).
                value_type getDistance() const { return m_distance; }

                //! \brief Sets the distance of the plane to the origin (scaled by the length of the plane's normal vector).
                void setDistance(const value_type val) { m_distance = val; }

            private:
                //! Vector that is perpendicular to the plane.
                vector_type m_normalVector;
                //! Signed-weighted distance from the plane.
                value_type  m_distance;
            };
        }
    }
}
#endif
