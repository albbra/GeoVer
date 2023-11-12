/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_UI_EXAMINERCONTROLLER_H_
#define COGRA_UI_EXAMINERCONTROLLER_H_
#include <cogra/types.h>
#include <cogra/ui/TrackballControl.h>
#include <cogra/ui/PitchShiftControl.h>
namespace cogra
{
    namespace ui
    {
        class ExaminerController
        {
        public:

            //! \brief Default constructor.
            ExaminerController();

            //! \brief Resets the controller to its default parameters.
            void reset();

            //! \brief Returns the rotation matrix.
            glm::mat4x4 getRotationMatrix() const;

            //! \brief Returns the rotation quaternion.
            f32quat getRotationQuaterion() const;

            //! \brief Sets the rotation quaternion.
            void setRotationQuaterion(const f32quat& r);

            //! \brief Gets the translation vector.
            f32vec3 getTranslationVector() const;

            //! \brief Sets the translation vector.
            void setTranslationVector(const f32vec3& t);

            //! \brief Returns the translation matrix,
            glm::mat4x4 getTranslationMatrix() const;

            //! \brief Returns the product of translation and rotation matrix.
            glm::mat4x4 getTransformationMatrix() const;

            //! \brief Controller Processing when the mouse button is pressed or released.
            //! \param  pressed	True, if a mouse button has just been clicked, false if it has just been released.
            //! \param  button	Which button is affected by the event. 1 for left, 2 for middle, 4 for right.
            //! \param  keyboardModifier True of a keyoard modifier key was pressed.
            //! \param  normalizedMouseCoordinates Mouse coordinates in the range [-1;1]^2            
            void click(bool pressed, int button, bool keyboardModifier, const f32vec2& normalizedMouseCoordinates);

            //! \brief Controller processing when the mouse button is moved.
            //!
            //! \param  normalizedMouseCoordinates Mouse coordinates in the range [-1;1]^2            
            void move(const f32vec2& normalizedMouseCoordinates);

            //! Aborts the mouse movement.
            void abort();

        private:
            //! True of the controller is currently in rotation mode, e.g. when the corresponding mouse button has been pressed.
            bool							m_bRotate;

            //! Trackball controller. Takes care of rotations.
            TrackballControl				m_trackball;

            //! True of the controller is currently in shift mode, e.g. when the corresponding mouse button has been pressed.
            bool							m_bShift;

            //! True of the controller is currently in pitch mode, e.g. when the corresponding mouse button has been pressed.
            bool							m_bPitch;

            //! Shift pitch controller. Takes care of translations.
            PitchShiftControl				m_pitchShiftControl;
        };
    }
}
#endif
