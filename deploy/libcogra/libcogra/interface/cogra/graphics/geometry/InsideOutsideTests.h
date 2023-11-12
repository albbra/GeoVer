/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_GEOMETRY_INSIDEOUTSIDETESTS_H_
#define COGRA_GRAPHICS_GEOMETRY_INSIDEOUTSIDETESTS_H_
#include <cogra/types.h>
#include <vector>
#include <cogra/graphics/geometry/AxisAlignedBoundingBox.h>
#include <cogra/graphics/geometry/Plane.h>
namespace cogra
{
    namespace graphics
    {
        namespace geometry
        {
            /// <summary>
            /// A class with static methods that holds checks for geometry being inside or outside other types of geometry.
            /// </summary>
            class InsideOutsideTests
            {
            public:
                //! \brief Tests whether a set of points is inside or outside a viewing frustum.
                //!
                //! Adapted from http://www.flipcode.com/archives/Frustum_Culling.shtml and
                //! http://www.lighthouse3d.com/tutorials/view-frustum-culling/clip-space-approach-extracting-the-planes/.
                //!
                //! \tparam T Floating-point type to control the precision of the computation.
                //! \param[in]  points Vector of points to test.
                //! \param[in]  m Projective matrix that defines the viewing frustum, i.e., a matrix that transforms the points to
                //!             clip-space.
                //! \return True, if the points are inside the frustum, false it they intersect the frustum or are outside the frustum.
                template<class T>
                static bool pointsInFrustrum(const std::vector<glm::vec<3, T, glm::qualifier::defaultp> >& points, const glm::mat<4, 4, T, glm::qualifier::defaultp>& m)
                {
                    const glm::vec<4, T> row0(glm::row(m, 0));
                    const glm::vec<4, T> row1(glm::row(m, 1));
                    const glm::vec<4, T> row2(glm::row(m, 2));
                    const glm::vec<4, T> row3(glm::row(m, 3));
                    const uint32 nFrustumPlanes = 6;
                    typedef std::array<Plane<glm::vec<4, T> >, nFrustumPlanes> FrustumPlanes;
                    FrustumPlanes frustumPlanes =
                    {
                      Plane<glm::vec<4, T> >(row0 - row3),
                      Plane<glm::vec<4, T> >(-row0 - row3),
                      Plane<glm::vec<4, T> >(row1 - row3),
                      Plane<glm::vec<4, T> >(-row1 - row3),
                      Plane<glm::vec<4, T> >(row2 - row3),
                      Plane<glm::vec<4, T> >(-row2 - row3)
                    };

                    for(uint32 pIdx = 0; pIdx < nFrustumPlanes; pIdx++)
                    {
                        uint32 nOutside = 0;
                        const Plane<glm::vec<3, T> >& plane = frustumPlanes[pIdx];
                        for(auto p = points.begin(); p != points.end(); ++p)
                        {
                            if(plane.evaluate(*p) > 0)
                            {
                                nOutside++;
                            }
                        }
                        if(nOutside == points.size())
                        {
                            return false;
                        }
                    }
                    return true;
                }

                //! \brief Tests if an axis aligned bounding box is entirely inside a viewing frustum.
                //! \tparam T Floating-point type to control the precision of the computation.
                //! \param[in]  aabb Axis aligned bounding box.
                //! \param[in]  m Projective matrix that defines the viewing frustum, i.e., a matrix that transforms the aabb to
                //!             clip-space.
                //! \return True, if the AABB is inside the frustum, false it it intersects the frustum or is outside the frustum.
                template<class T>
                static bool AABBInFrustrum(const AxisAlignedBoundingBox<glm::vec<3, T, glm::qualifier::defaultp> >& aabb,
                                           const glm::mat<4, 4, T, glm::qualifier::defaultp>& m)
                {
                    const glm::vec<4, T, glm::qualifier::defaultp> row0(glm::row(m, 0));
                    const glm::vec<4, T, glm::qualifier::defaultp> row1(glm::row(m, 1));
                    const glm::vec<4, T, glm::qualifier::defaultp> row2(glm::row(m, 2));
                    const glm::vec<4, T, glm::qualifier::defaultp> row3(glm::row(m, 3));
                    struct Local
                    {
                        static T Test(const Plane< glm::vec<3, T, glm::qualifier::defaultp> >& plane,
                                      const AxisAlignedBoundingBox<glm::vec<3, T, glm::qualifier::defaultp> >& aabb)
                        {
                            return
                                std::min(aabb.getMin().x * plane.getNormalVector().x, aabb.getMax().x * plane.getNormalVector().x) +
                                std::min(aabb.getMin().y * plane.getNormalVector().y, aabb.getMax().y * plane.getNormalVector().y) +
                                std::min(aabb.getMin().z * plane.getNormalVector().z, aabb.getMax().z * plane.getNormalVector().z) +
                                plane.getDistance();
                        }
                    };
                    if(Local::Test(Plane<glm::vec<3, T, glm::qualifier::defaultp> >(row0 - row3), aabb) > 0) return false;
                    if(Local::Test(Plane<glm::vec<3, T, glm::qualifier::defaultp> >(-row0 - row3), aabb) > 0) return false;
                    if(Local::Test(Plane<glm::vec<3, T, glm::qualifier::defaultp> >(row1 - row3), aabb) > 0) return false;
                    if(Local::Test(Plane<glm::vec<3, T, glm::qualifier::defaultp> >(-row1 - row3), aabb) > 0) return false;
                    if(Local::Test(Plane<glm::vec<3, T, glm::qualifier::defaultp> >(row2 - row3), aabb) > 0) return false;
                    if(Local::Test(Plane<glm::vec<3, T, glm::qualifier::defaultp> >(-row2 - row3), aabb) > 0) return false;
                    return true;
                }
            };
        }
    }
}
#endif
