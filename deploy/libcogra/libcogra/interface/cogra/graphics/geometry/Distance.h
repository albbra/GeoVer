/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_GEOMETRY_DISTANCE_H_
#define COGRA_GRAPHICS_GEOMETRY_DISTANCE_H_
#include <cogra/types.h>
#include <cogra/graphics/geometry/IntrinsicCamera.h>
#include <cogra/graphics/geometry/AxisAlignedBoundingBox.h>

namespace cogra
{
    namespace graphics
    {
        namespace geometry
        {
            //! \brief A class that contains static methods for computing distances between different types of geometry.
            class Distance
            {
            public:
                //! \brief Computes the optimal distance from an axis aligned bounding box to projective camera. The distance is
                //! computed such, fully sees the bounding box along the x and the y direction.
                //! \tparam T Floating-point type to control the precision of the computation.
                //! \param[in]  aabb Axis aligned bounding box.
                //! \param[in]  P Matrix P, that projects point onto the clip space.
                //! \param[in]  M Matrix M, that projects the point into eye space.
                //! \return The distance from the camera to the bounding box such, that the bounding box is fully visible.
                template<class T>
                static T computeOptimalDistanceToCamera(const AxisAlignedBoundingBox<glm::vec<3, T, glm::qualifier::defaultp> >& aabb,
                                                        const glm::mat<4, 4, T, glm::qualifier::defaultp>& P, const glm::mat<4, 4, T, glm::qualifier::defaultp>& M)
                {
                    const glm::vec<4, T, glm::qualifier::defaultp> lower = M * glm::vec<4, T, glm::qualifier::defaultp>(aabb.getMin(), 1);
                    const T zx = -((lower.x * (P[0][0] + P[0][3]) + (P[3][0] + P[3][3])) / (P[2][0] - P[2][3])) - lower.z;
                    const T zy = -((lower.y * (P[1][1] + P[1][3]) + (P[3][1] + P[3][3])) / (P[2][1] - P[2][3])) - lower.z;
                    return std::max(zx, zy);
                }

                //! \brief Computes the optimal distance from an axis aligned bounding box to projective camera. The distance is
                //! computed such, fully sees the bounding box along the x and the y direction.
                //! \tparam T Floating-point type to control the precision of the computation.
                //! \param[in]  aabb Axis aligned bounding box.
                //! \param[in]  camera Matrix, that projects point onto the clip space.
                //! \param[in]  M Matrix, that projects the point into eye space.
                //! \return The distance from the camera to the bounding box such, that the bounding box is fully visible.

                template<class T>
                static T computeOptimalDistanceToCamera(
                    const AxisAlignedBoundingBox< glm::vec<3, T, glm::qualifier::defaultp> >& aabb,
                    const IntrinsicCamera<T>& camera,
                    const glm::mat<4, 4, T, glm::qualifier::defaultp>& M
                )
                {
                    const glm::vec<4, T> lower = M * glm::vec<4, T>(aabb.getMin(), 1);
                    const glm::vec<4, T> upper = M * glm::vec<4, T>(aabb.getMax(), 1);
                    T zx = T(0.5) * (upper.x - lower.x) / std::tan(T(0.5) * glm::radians(camera.getFieldOfViewXDegrees()));
                    T zy = T(0.5) * (upper.y - lower.y) / std::tan(T(0.5) * glm::radians(camera.getFieldOfViewYDegrees()));
                    return std::max(zx, zy) - (lower.z);
                }

                //! \brief Computes the minimum distance along the z axis from (0,0,0) to the corner points of an axis aligned
                //! bounding box.
                //! \tparam T Floating-point type to control the precision of the computation.
                //! \param[in]  aabb Bounding box.
                //! \param[in]  toEyeSpace Matrix, that transforms the bounding box to eye space.
                //! \return 2D Vector with minimum and maximum distance contained in the x and y coordinate, respectively.
                template<class T>
                static glm::vec<2, T, glm::qualifier::defaultp> computeMinMaxDistanceToBoundingBox(
                    const AxisAlignedBoundingBox<glm::vec<3, T, glm::qualifier::defaultp> >& aabb,
                    const glm::mat<4, 4, T, glm::qualifier::defaultp>& toEyeSpace)
                {
                    glm::vec<4, T, glm::qualifier::defaultp> row = glm::row(toEyeSpace, 2);
                    glm::vec<2, T, glm::qualifier::defaultp> z(std::numeric_limits<T>::max(), -std::numeric_limits<T>::max());
                    z = minMax(z, -glm::dot(row, glm::vec<4, T, glm::qualifier::defaultp>(aabb.get(0), 1)));
                    z = minMax(z, -glm::dot(row, glm::vec<4, T, glm::qualifier::defaultp>(aabb.get(1), 1)));
                    z = minMax(z, -glm::dot(row, glm::vec<4, T, glm::qualifier::defaultp>(aabb.get(2), 1)));
                    z = minMax(z, -glm::dot(row, glm::vec<4, T, glm::qualifier::defaultp>(aabb.get(3), 1)));
                    z = minMax(z, -glm::dot(row, glm::vec<4, T, glm::qualifier::defaultp>(aabb.get(4), 1)));
                    z = minMax(z, -glm::dot(row, glm::vec<4, T, glm::qualifier::defaultp>(aabb.get(5), 1)));
                    z = minMax(z, -glm::dot(row, glm::vec<4, T, glm::qualifier::defaultp>(aabb.get(6), 1)));
                    z = minMax(z, -glm::dot(row, glm::vec<4, T, glm::qualifier::defaultp>(aabb.get(7), 1)));
                    return z;
                }
            };
        }
    }
}
#endif
