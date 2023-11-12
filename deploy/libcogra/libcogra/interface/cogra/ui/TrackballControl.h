/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_UI_TRACKBALLCONTROL_H_
#define COGRA_UI_TRACKBALLCONTROL_H_
#include <cogra/types.h>

namespace cogra
{
    namespace ui

    {
        //! This class implements a trackball, also called arc-ball, providing intuitive rotation for objects.
        //! A trackball is like a virtual sphere. Whenever the user starts dragging the mouse, the screen positions
        //! are projected onto a virtual sphere and the corresponding z value is calculated. While dragging the mouse
        //! two float3 vectors are retrieved, out of which an axis-angle rotation is derived. We use that to interpolate a
        //! quaternion.
        //! The quaternion can then be converted into a 4x4 matrix.
        //! A possible use case is to call startRotation when starting to drag the mouse. While moving the mouse while holding
        //! the mouse button, call updateRotatio.
        //!
        //! Note, that all variables concerning screen coordinates should be normalized an interval between
        //! -1.0 and 1.0.
        class TrackballControl
        {
        public:

            //! \brief Initializes trackball.
            //! \param radius Radius of the virtual sphere.
            explicit TrackballControl(float32 radius = 0.8f);

            //! \brief Destroy the trackball
            ~TrackballControl() = default;

            //! \brief Call this, when the rotation starts, e.g., when the mouse button has been pressed.
            //!
            //! \param  pos Position on the screen space. Its components should be normalized to be between -1 and 1.
            void startRotation(const f32vec2& normalizedMouseCoordinates);

            //! \brief Call this, when updating the rotation, e.g., while the mouse button has been pressed.
            //!
            //! \param  pos Position on the screen space. Its components should be normalized to be between -1 and 1.
            void updateRotation(const f32vec2& normalizedMouseCoordinates);

            //! \brief Resets the trackball.
            void reset();

            //!Returns the current quaternion as a rotation matrix.
            glm::mat4x4 getRotationMatrix() const;

            //! \brief Returns the current quaternion.
            const f32quat& getRotationQuaterion() const;

            //! \brief Sets the quaternion.
            void setRotationQuaterion(const f32quat& q);

        private:

            //! \brief Projects x,y into a sphere and returns its the corresponding
            //! z value. If x and y are not on the sphere project them on a hyperbola
            //! sheet.
            //! Note that x, y should be between -1.0, 1.0
            //! \param x x position.
            //! \param y y position.
            //! \return z value
            float32 projectToSphere(const f32vec2& normalizedMouseCoordinates);

            //! Radius of the trackball sphere
            float32 m_radius;

            //! Position on the screen space. Its components should be normalized to be between -1 and 1.
            f32vec2 m_normalizedMouseCoordinates;

            //! Current rotation expressed as a quaternion
            f32quat m_rotation;
        };
    }
}
#endif
