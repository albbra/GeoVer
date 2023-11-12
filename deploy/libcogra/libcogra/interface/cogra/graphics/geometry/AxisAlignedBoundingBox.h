/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_GEOMETRY_AXISALGINEDBOUNDINGBOX_H_
#define COGRA_GRAPHICS_GEOMETRY_AXISALGINEDBOUNDINGBOX_H_
#include <cogra/types.h>
#include <vector>
#include <algorithm>
#include <cogra/graphics/geometry/CorrespondingTypes.h>
#include <cogra/graphics/geometry/MathTools.h>
namespace cogra
{
    namespace graphics
    {
        namespace geometry
        {
            //! \brief Class for an axis-aligned bounding box.
            //! \tparam VECTOR_TYPE GLM Vector type.
            template<class VECTOR_TYPE>
            class AxisAlignedBoundingBox
            {
            public:
                typedef VECTOR_TYPE vector_type;
                typedef typename VECTOR_TYPE::value_type value_type;
                typedef size_t size_type;
                typedef typename getCorrespondingMatrixType<value_type, typename getUpperDimensionVectorType<value_type, vector_type>::vector_type >::matrix_type matrix_type;

                //! \brief Sets the bounding of a single point.
                //! \param[in]  p0 Point to set the bounding box from.
                explicit AxisAlignedBoundingBox(const vector_type& p0)
                    : m_min(p0)
                    , m_max(p0)
                { }

                //! \brief Sets the bounding of make up of two points point.
                //! \param[in]  p0 First point to set the bounding box from.
                //! \param[in]  p1 Second point to set the bounding box from.
                AxisAlignedBoundingBox(const vector_type& p0, const vector_type& p1)
                    : m_min(glm::min(p0, p1))
                    , m_max(glm::max(p0, p1))
                { }

                //! \brief Sets the bounding box to one that spans the entire span of valid numbers.
                AxisAlignedBoundingBox()
                    : m_min(+std::numeric_limits<value_type>::max())
                    , m_max(-std::numeric_limits<value_type>::max())
                { }

                //! \brief Computes the bounding box from an array of points.
                //! \param[in]  points Pointer to the array of points.
                //! \param[in]  nPoints Number of points in the array.
                AxisAlignedBoundingBox(const vector_type* const points, size_t nPoints)
                    : m_min(+std::numeric_limits<value_type>::max())
                    , m_max(-std::numeric_limits<value_type>::max())

                {
                    add(points, nPoints);
                }

                //! \brief Computes the bounding box from a vector of points.
                //! \param[in]  points Vector of points.
                explicit AxisAlignedBoundingBox(const std::vector<vector_type>& points)
                    : m_min(+std::numeric_limits<value_type>::max())
                    , m_max(-std::numeric_limits<value_type>::max())
                {
                    add(points);
                }

                //! \brief Adds a single point to the bounding box.
                //! \param[in]  Point to add to the bounding box.
                void add(const vector_type& point)
                {
                    for(auto c = 0; c < point.length(); c++)
                    {
                        m_min[c] = std::min(m_min[c], point[c]);
                        m_max[c] = std::max(m_max[c], point[c]);
                    }
                }

                //! \brief Adds an array of points to the bounding box.
                //! \param[in]  points Pointer to the array of points.
                //! \param[in]  nPoints Number of points in the array.
                void add(const vector_type* const points, size_t nPoints)
                {
                    for(auto pIdx = 0; pIdx < nPoints; pIdx++)
                    {
                        add(points[pIdx]);
                    }
                }

                //! \brief Adds a vector of points to the bounding box.
                //! \param[in]  points Vector of points.
                void add(const std::vector<vector_type>& points)
                {
                    add(points.data(), points.size());
                }

                //! \brief Computes the union from this bounding box with another box.
                //! \param[in]  other Other bounding box used to compute the bounding box.
                void add(const AxisAlignedBoundingBox& other)
                {
                    for(auto c = 0; c < m_min.length(); c++)
                    {
                        m_min[c] = std::min(m_min[c], other.m_min[c]);
                        m_max[c] = std::max(m_max[c], other.m_max[c]);
                    }
                }

                //! \brief Computes the bounding box from an array of points.
                //! \param[in]  points Pointer to the array of points.
                //! \param[in]  nPoints Number of points in the array.
                void set(const vector_type* const points, size_t nPoints)
                {
                    reset();
                    add(points, nPoints);
                }

                //! \brief Computes the bounding box from a vector of points.
                //! \param[in]  points Vector of points.
                void set(const std::vector<vector_type>& points)
                {
                    set(points.data(), points.size());
                }

                //! \brief Resets the bounding box to one that spans the entire span of valid numbers.
                void reset()
                {
                    m_min = vector_type(+std::numeric_limits<value_type>::max());
                    m_max = vector_type(-std::numeric_limits<value_type>::max());
                }

                //! \brief Returns the center of the bounding box.
                vector_type getCenter() const
                {
                    return static_cast<value_type>(0.5) * (m_min + m_max);
                }

                //! \brief Returns the diagonal from the minimum to the upper corner.
                vector_type getDiagonal() const
                {
                    return m_max - m_min;
                }

                //! \brief Returns the length of the largest side of the bounding box.
                value_type getMaxSideLength() const
                {
                    return glm::compMax(getDiagonal());
                }

                //! \brief Returns the length of the smallest side of the bounding box.
                value_type getMinSideLength() const
                {
                    return glm::compMin(getDiagonal());
                }

                //! \brief Returns factor that is required to scale the bounding box to one whose largest side has length one and
                //! maintaining the relations among the sides of the bounding box.
                value_type getIsotropicScaleFactor() const
                {
                    return static_cast<value_type>(1) / (getMaxSideLength());
                }

                //! \brief Returns the matrix that transform the bounding box the origin and scales it to have side length one
                //! along its largest directions. At the same time, it maintains the relations among the sides.
                //! \return
                matrix_type getNormalizationMatrix() const
                {
                    matrix_type normalizationMatrix(0);

                    const value_type s = getIsotropicScaleFactor();
                    const vector_type c = getCenter();
                    for(auto cIdx = 0; cIdx < c.length(); cIdx++)
                    {
                        normalizationMatrix[cIdx][cIdx] = s;
                        normalizationMatrix[c.length()][cIdx] = -s * c[cIdx];
                    }
                    normalizationMatrix[c.length()][c.length()] = 1;
                    return normalizationMatrix;
                }

                //! \brief Gets the minimum coordinates of the bounding box.
                vector_type getMin() const { return m_min; }

                //! \brief Gets the maximum coordinates of the bounding box.
                vector_type getMax() const { return m_max; }

                //! \brief Returns the i-th corner point of the bounding box.
                //! \param[in,out]  i The index of the corner point. Goes from 0 to number of corner points minus. If the least
                //! significant bit of i is set,  Otherwise the resulting vector's first component corresponds to the first component of the
                //! minimum corner. If the second-least significant bit is (not) set, then resulting vector's second component
                //! corresponds to the second component of the (minimum) maximum corner. An so forth.
                //! \return The i-th corner point of the bounding box.
                vector_type get(size_type i) const
                {
                    vector_type result;
                    for(auto dim = 0; dim < result.length(); dim++)
                    {
                        result[dim] = (((i >> dim) & 1) == 1) ? getMax()[dim] : getMin()[dim];
                    }
                    return result;
                }

                //! \brief Transforms the bounding box with that matrix.
                //! In case the matrix is projective, the bounding box will be projective (i.e. divide by the last component).
                //! \param[in] A transformation matrix (it may be projective).
                //! \return The transformed bounding box.
                AxisAlignedBoundingBox<VECTOR_TYPE> transform(const matrix_type& matrix) const
                {
                    return AxisAlignedBoundingBox<VECTOR_TYPE>(
                        cogra::graphics::geometry::dehomogenize(matrix * cogra::graphics::geometry::homogenize(m_min)),
                        cogra::graphics::geometry::dehomogenize(matrix * cogra::graphics::geometry::homogenize(m_max)));
                }

                //!\brief Returns true if the point is inside the bounding box, false otherwise.
                //! \param[in] The point that we wish test.
                //! \return True, if the point is inside.
                bool isInside(const vector_type point) const
                {
                    for(auto dim = 0; dim < vector_type::length(); dim++)
                    {
                        if(!(m_min[dim] <= point[dim] && point[dim] <= m_max[dim]))
                        {
                            return false;
                        }
                    }
                    return true;
                }

            private:
                //! Minimum corner of the bounding box.
                vector_type           m_min;
                //! Maximum corner of the bounding box.
                vector_type           m_max;
            };

            typedef AxisAlignedBoundingBox<glm::vec<3, float32, glm::qualifier::defaultp> > AABB3;
            typedef AxisAlignedBoundingBox<glm::vec<2, float32, glm::qualifier::defaultp> > AABB2;
        }
    }
}
#endif
