/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/ui/ExaminerController.h>
namespace cogra
{
    namespace ui

    {
        ExaminerController::ExaminerController()
            : m_bRotate(false)
            , m_bShift(false)
            , m_bPitch(false)

        {
            reset();
        }

        void ExaminerController::reset()
        {
            m_bRotate = false;
            m_bShift = false;
            m_bPitch = false;
            m_pitchShiftControl.reset();
            m_trackball.reset();
        }

        glm::mat4x4 ExaminerController::getRotationMatrix() const
        {
            return m_trackball.getRotationMatrix();
        }

        glm::mat4x4 ExaminerController::getTranslationMatrix() const
        {
            return m_pitchShiftControl.getTranslationMatrix();
        }

        glm::mat4x4 ExaminerController::getTransformationMatrix() const
        {
            return getTranslationMatrix() * getRotationMatrix();
        }

        void ExaminerController::click(bool pressed, int button, bool keyboardModifier, const f32vec2& normalizedMouseCoordinates)
        {
            if(button == 1)
            {
                if(pressed)
                {
                    if(keyboardModifier)
                    {
                        m_bShift = true;
                        m_bRotate = false;
                        m_pitchShiftControl.startShift(normalizedMouseCoordinates);
                    }
                    else
                    {
                        m_bRotate = true;
                        m_bShift = false;
                        m_trackball.startRotation(normalizedMouseCoordinates);
                    }
                }
                else
                {
                    m_bRotate = false;
                    m_bShift = false;
                }
            }

            if(button == 2)
            {
                if(pressed)
                {
                    m_bPitch = true;
                    m_pitchShiftControl.startPitch(normalizedMouseCoordinates);
                }
                else
                {
                    m_bPitch = false;
                }
            }
        }

        void ExaminerController::move(const f32vec2& normalizedMouseCoordinates)
        {
            if(m_bRotate)
            {
                m_trackball.updateRotation(normalizedMouseCoordinates);
            }
            if(m_bPitch)
            {
                m_pitchShiftControl.updatePitch(normalizedMouseCoordinates);
            }
            if(m_bShift)
            {
                m_pitchShiftControl.updateShift(normalizedMouseCoordinates);
            }
        }

        void ExaminerController::abort()
        {
            m_bRotate = false;
            m_bShift = false;
            m_bPitch = false;
        }

        f32quat ExaminerController::getRotationQuaterion() const
        {
            return m_trackball.getRotationQuaterion();
        }

        void ExaminerController::setRotationQuaterion(const f32quat& r)
        {
            m_trackball.setRotationQuaterion(r);
        }

        f32vec3 ExaminerController::getTranslationVector() const
        {
            return m_pitchShiftControl.getTranslation();
        }

        void ExaminerController::setTranslationVector(const f32vec3& t)
        {
            m_pitchShiftControl.setTranslation(t);
        }
    }
}
