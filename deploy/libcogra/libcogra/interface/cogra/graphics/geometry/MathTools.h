/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_GEOMETRY_MATHTOOLS_H_
#define COGRA_GRAPHICS_GEOMETRY_MATHTOOLS_H_
#include <cogra/types.h>


namespace cogra
{
    namespace graphics
    {
        namespace geometry
        {
            /// <summary>
            /// Computes the inverse of the perspective matrix.
            /// </summary>
            /// <param name="fovy">Field of view in y direction in radians.</param>
            /// <param name="aspect">Aspect ratio </param>
            /// <param name="zNear">Absolute value of the distance of the nearplane to the camera.</param>
            /// <param name="zFar">Absolute value of the distance of the farplane to the camera.</param>
            /// <returns>Returns in the inverse</returns>
            /// The caller must assure that 0 < zNear < zFar. Otherwise the behaviour is undefined.
            template <typename valType>
            glm::mat<4, 4, valType, glm::qualifier::defaultp> perspectiveInverse
            (
                valType const & fovy,
                valType const & aspect,
                valType const & zNear,
                valType const & zFar
            )
            {
                valType range = glm::tan(fovy / valType(2)) * zNear;
                valType left = -range * aspect;
                valType right = range * aspect;
                valType bottom = -range;
                valType top = range;

                glm::mat<4, 4, valType, glm::qualifier::defaultp> Result(valType(0));
                Result[0][0] = (right - left) / (valType(2) * zNear);
                Result[1][1] = (top - bottom) / (valType(2) * zNear);
                Result[2][3] = (zNear - zFar) / (valType(2) * zFar *  zNear);
                Result[3][2] = -valType(1);
                Result[3][3] = (zFar + zNear) / (valType(2) * zFar * zNear);
                return Result;
            }

            /// <summary>
            /// Computes the inverse of the perspective matrix with infinite far-plane distance.
            /// </summary>
            /// <param name="fovy">Field of view in y direction in radians.</param>
            /// <param name="aspect">Aspect ratio </param>
            /// <param name="zNear">Absolute value of the distance of the nearplane to the camera.</param>
            /// <returns>Returns in the inverse</returns>
            /// The caller must assure that 0 < zNear. Otherwise the behaviour is undefined.
            template <typename valType>
            glm::mat<4, 4, valType, glm::qualifier::defaultp> perspectiveInfinityInverse
            (
                valType const & fovy,
                valType const & aspect,
                valType const & zNear
            )
            {
                valType range = glm::tan(fovy / valType(2)) * zNear;
                valType left = -range * aspect;
                valType right = range * aspect;
                valType bottom = -range;
                valType top = range;

                glm::mat<4, 4, valType, glm::qualifier::defaultp> Result(valType(0));
                Result[0][0] = (right - left) / (valType(2) * zNear);
                Result[1][1] = (top - bottom) / (valType(2) * zNear);
                Result[2][3] = -valType(1) / (valType(2) * zNear);
                Result[3][2] = -valType(1);
                Result[3][3] = valType(1) / (valType(2) * zNear);
                return Result;
            }

            template<class T>
            glm::vec<2, T, glm::qualifier::defaultp> minMax(const glm::vec<2, T, glm::qualifier::defaultp> v, const T value)
            {
                glm::vec<2, T, glm::qualifier::defaultp> result;
                result.x = std::min(v.x, value);
                result.y = std::max(v.y, value);
                return result;
            }

            template<typename valType>
            glm::vec<3, valType, glm::qualifier::defaultp> dehomogenize(const glm::vec<4, valType, glm::qualifier::defaultp>& v4)
            {
                valType inv = valType(1) / v4.w;
                return glm::vec<3, valType, glm::qualifier::defaultp>(v4.x * inv, v4.y * inv, v4.z * inv);
            }

            template<typename valType>
            glm::vec<2, valType, glm::qualifier::defaultp> dehomogenize(const glm::vec<3, valType, glm::qualifier::defaultp>& v3)
            {
                valType inv = valType(1) / v3.z;
                return glm::vec<2, valType, glm::qualifier::defaultp>(v3.x * inv, v3.y * inv);
            }

            template<typename valType>
            glm::vec<4, valType, glm::qualifier::defaultp> homogenize(const glm::vec<3, valType, glm::qualifier::defaultp>& v3)
            {
                return glm::vec<4, valType, glm::qualifier::defaultp>(v3.x, v3.y, v3.z, valType(1));
            }

            template<typename valType>
            glm::vec<3, valType, glm::qualifier::defaultp> homogenize(const glm::vec<2, valType, glm::qualifier::defaultp>& v2)
            {
                return glm::vec<3, valType, glm::qualifier::defaultp>(v2.x, v2.y, valType(1));
            }

            //! \brief Computes an orthographic projective camera combined with a model view camera, that gives a good overview
            //! of a scene.
            //! \param[in]  showX True, to show the scene with the x axis pointing into vertical direction and the y axis into
            //! to a direction perpendicular to the screen. False, to show the scene with the y axis pointing into vertical
            //! direction and the x axis into a direction perpendicular to the screen.
            //! \param[in]  scaleFactor Isotropic scale factor to scale the orthographic projection/
            //! \param[in]  aspectRatio Relationship between the width and the height of the screen.
            //! \param[in]  distance Translate the scene along the z direction.
            //! \param[in]  nearPlane Distance of the near camera to the near plane  of the orthographic projection.
            //! \param[in]  farPlane Distance of the near camera to the near plane  of the orthographic projection.
            //! \return An orthographic projection matrix for getting a overview of a scene.
            template<class T>
            glm::mat<4, 4, T, glm::qualifier::defaultp> computeOverviewMatrix(bool showX, T scaleFactor, T aspectRatio, T distance, T nearPlane,
                                                                            T farPlane)
            {
                glm::mat4x4 scale = glm::scale(glm::vec<3, T, glm::qualifier::defaultp>(scaleFactor, scaleFactor, scaleFactor));
                glm::mat4x4 t;
                if(showX)
                {
                    t = glm::translate(glm::vec<3, T, glm::qualifier::defaultp>(-aspectRatio, T(-0), -distance)) * glm::rotate(glm::radians(T(-90)), 
                                                                                                                               glm::vec<3, T, glm::qualifier::defaultp>(T(0), T(1), T(0))) * scale;
                }
                else
                {
                    t = glm::translate(glm::vec<3, T, glm::qualifier::defaultp>(T(0), T(-1), distance)) * glm::rotate(glm::radians(T(90)), 
                                                                                                                       glm::vec<3, T, glm::qualifier::defaultp>(T(1), T(0), T(0))) * scale;
                }
                return glm::ortho(-aspectRatio, aspectRatio, T(-1), T(1), nearPlane, farPlane) * t;
            }

            //! \brief Mixes two values using cubic interpolation.
            //!
            //! The function is defined such that the first derivative vanishes at F(0) and F(1).
            //! \param[in,out]  u0 The value of the function at F(0)
            //! \param[in,out]  u1 The value of the function at F(1)
            //! \param[in,out]  u At what parameter the function shall be evaluated.
            //! \return The cubically interpolated value.
            template<class T, class X>
            T cubicMix(const T& u0, const T& u1, const X& u)
            {
                return glm::mix(u0, u1, 3 * u * u - 2 * u * u *u);
            }
            //! \brief Mixes two values using quintic interpolation.
            //!
            //! The function is defined such that the first and second derivative vanishes at F(0) and F(1).
            //! \param[in,out]  u0 The value of the function at F(0)
            //! \param[in,out]  u1 The value of the function at F(1)
            //! \param[in,out]  u At what parameter the function shall be evaluated.
            //! \return The quintically interpolated value.
            template<class T, class X>
            T quinticMix(const T& u0, const T& u1, const X& u)
            {
                return glm::mix(u0, u1, ((6 * u - 15) * u + 10) * u * u * u);
            }

            //! \brief Computes the bilinear function F(u,v) where
            //!   F(0,0) = Fu0v0,
            //!   F(1,0) = Fu1v0,
            //!   F(0,1) = Fu0v1,
            //!   F(1,1) = Fu1v1
            //! using bilinear interpolation.
            //! \param[in] Fu0v0 The value of the function at F(0,0).
            //! \param[in] Fu1v0 The value of the function at F(1,0).
            //! \param[in] Fu0v1 The value of the function at F(0,1).
            //! \param[in] Fu1v1 The value of the function at F(1,1).
            //! \param[in]  u The parameter value in u direction.
            //! \param[in]  v The parameter value in v direction.
            //! \return The bilinearly interpolated value F(u,v).
            template<class T, class X>
            T bilinear(const T& Fu0v0, const T& Fu1v0, const T& Fu0v1, const T& Fu1v1, const X& u, const X& v)
            {
                return glm::mix(glm::mix(Fu0v0, Fu0v1, v), glm::mix(Fu1v0, Fu1v1, v), u);
            }

            //! \brief Computes the trilinear function F(u,v,w) where
            //!   F(0,0,0) = Fu0v0w0,
            //!   F(0,1,0) = Fu0v1w0,
            //!   F(1,0,0) = Fu1v0w0,
            //!   F(1,1,0) = Fu1v1w0
            //!   F(0,0,1) = Fu0v0w1,
            //!   F(0,1,1) = Fu0v1w1,
            //!   F(1,0,1) = Fu1v0w1,
            //!   F(1,1,1) = Fu1v1w1
            //! using trilinear interpolation.
            //! The function values at F(0, 0) = F(
            //! \param[in]  Fu0v0w0 The value of the function at F(0,0,0).
            //! \param[in]  Fu1v0w0 The value of the function at F(1,0,0).
            //! \param[in]  Fu0v1w0 The value of the function at F(0,1,0).
            //! \param[in]  Fu1v1w0 The value of the function at F(1,1,0).
            //! \param[in]  Fu0v0w1 The value of the function at F(0,0,1).
            //! \param[in]  Fu1v0w1 The value of the function at F(1,0,1).
            //! \param[in]  Fu0v1w1 The value of the function at F(0,1,1).
            //! \param[in]  Fu1v1w1 The value of the function at F(1,1,1).
            //! \param[in]  u The parameter value in u direction.
            //! \param[in]  v The parameter value in v direction.
            //! \param[in]  w The parameter value in w direction.
            //! \return The tri-linearly interpolated value F(u,v,w).
            template<class T, class X>
            T trilinear(const T& Fu0v0w0, const T& Fu1v0w0, const T& Fu0v1w0, const T& Fu1v1w0,
                        const T& Fu0v0w1, const T& Fu1v0w1, const T& Fu0v1w1, const T& Fu1v1w1,
                        const X& u, const X& v, const X& w)
            {
                return glm::mix(bilinear(Fu0v0w0, Fu1v0w0, Fu0v1w0, Fu1v1w0, u, v),
                                bilinear(Fu0v0w1, Fu1v0w1, Fu0v1w1, Fu1v1w1, u, v), w);
            }
        }
    }
}
#endif
