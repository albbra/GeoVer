/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_GEOMETRY_INTRINSICCAMERA_H_
#define COGRA_GRAPHICS_GEOMETRY_INTRINSICCAMERA_H_
#include <cogra/graphics/geometry/MathTools.h>

namespace cogra
{
namespace graphics
{
namespace geometry
{
//! A class that holds intrinsic camera parameters.
//! \tparam T Any type of floating-point type works.
template<class T>
class IntrinsicCamera
{
public:
  //! \brief Constructor for creating a class holding intrinsic camera properties.
  //! It is in the caller's responsibility to assure the correctness of the parameters.
  //! \param[in]  nearPlaneDistance Distance from camera to camera near plane. Must be positive.
  //! \param[in]  farPlaneDistance Distance from camera to camera far plane. Must be positive and larger than
  //!             nearPlaneDistance.
  //! \param[in]  fieldOfViewDegree Field of view in degrees in vertical direction. Must be positive and smaller than
  //!             180 degrees.
  //! \param[in]  aspectRatio Relation between width over height of the view port.c Must be positive.
  explicit IntrinsicCamera(T nearPlaneDistance = T(1) / T(64), T farPlaneDistance = T(64), T fieldOfViewDegree = T(30),
                           T aspectRatio = T(16) / T(9))
    : m_nearPlaneDistance(nearPlaneDistance)
    , m_farPlaneDistance(farPlaneDistance)
    , m_fieldOfViewYDegrees(fieldOfViewDegree)
    , m_aspectRatio(aspectRatio)
  { }

  //! \brief Returns the distance of the camera to the camera's near plane.
  T getNearPlaneDistance() const
  {
    return m_nearPlaneDistance;
  }

  //! \brief Sets the distance of the camera to the camera's near plane.
  //! It is in the caller's responsibility to make sure that this value is
  //! - positive
  //! - smaller than GetFarPlaneDistance().
  //! \param[in]  val Value of the near plane distance. If the value is non-positive, the behavior is undefined.
  void setNearPlaneDistance(T val)
  {
    m_nearPlaneDistance = val;
  }

  //! \brief Returns field of view in degrees in vertical direction.
  T getFieldOfViewYDegrees() const
  {
    return m_fieldOfViewYDegrees;
  }

  //! \brief Sets the field of view in degrees in vertical direction.
  //! \param[in]  val The value of the field of view in degrees. Must be positive and smaller than 180 degrees.
  void setFieldOfViewYDegrees(T val)
  {
    m_fieldOfViewYDegrees = val;
  }

  //! \brief Return the distance of the camera to the far plane. Can be infinity.
  T getFarPlaneDistance() const
  {
    return m_farPlaneDistance;
  }
  //! \brief Sets the distance of the camera to the far plane. Can be infinity.
  //! It is in the caller's responsibility to make sure that this value is
  //! - positive
  //! - larger than GetNearPlaneDistance().
  void setFarPlaneDistance(T val)
  {
    m_farPlaneDistance = val;
  }

  //! \brief Returns the relation between width over height of the view port.
  T getAspectRatio() const
  {
    return m_aspectRatio;
  }

  //! \brief Sets the relation between width over height of the view port.
  //! \param[in,out]  val  Positive value.
  void setAspectRatio(T val)
  {
    if(val == 0 || std::isnan(val))
    {
      return;
    }
    m_aspectRatio = val;
  }

  //! \brief Returns the projection matrix.
  glm::mat<4, 4, T, glm::qualifier::defaultp> getMatrix() const
  {
    if(m_farPlaneDistance == std::numeric_limits<T>::infinity())
    {
      return glm::infinitePerspective(glm::radians(m_fieldOfViewYDegrees), m_aspectRatio, m_nearPlaneDistance);
    }
    else
    {
      return glm::perspective(glm::radians(m_fieldOfViewYDegrees), m_aspectRatio, m_nearPlaneDistance, m_farPlaneDistance);
    }
  }

  //! \brief Returns the inverse projection matrix.
  glm::mat<4, 4, T, glm::qualifier::defaultp> getInverseMatrix() const
  {
    if(m_farPlaneDistance == std::numeric_limits<T>::infinity())
    {
      return perspectiveInfinityInverse(glm::radians(m_fieldOfViewYDegrees), m_aspectRatio, m_nearPlaneDistance);
    }
    else
    {
      return perspectiveInverse(glm::radians(m_fieldOfViewYDegrees), m_aspectRatio, m_nearPlaneDistance, m_farPlaneDistance);
    }
  }

  //! \brief Returns the field of view in degrees in x direction.
  T getFieldOfViewXDegrees() const
  {
    return T(2.0) * glm::atan(m_aspectRatio * glm::tan(T(0.5) * m_fieldOfViewYDegrees));
  }

private:
  //! Distance from camera to camera near plane.
  T                   m_nearPlaneDistance;

  //! Distance from camera to camera far plane.
  T                   m_farPlaneDistance;

  //! Field of view in degrees in vertical direction.
  T                   m_fieldOfViewYDegrees;

  //! Relation between width over height of the view port.
  T                   m_aspectRatio;
};
}
}
}
#endif
