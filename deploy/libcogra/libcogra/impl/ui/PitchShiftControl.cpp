/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/ui/PitchShiftControl.h>
namespace cogra
{
    namespace ui

    {
        PitchShiftControl::PitchShiftControl(f32vec3 defaultTranslation)
            : m_shift(0.0f, 0.0f)
            , m_pitch(0.0f, 0.0f)
            , m_translation(defaultTranslation)
            , m_defaultTranslation(defaultTranslation)
        { }

        PitchShiftControl::~PitchShiftControl() = default;

        void PitchShiftControl::startPitch(const f32vec2& normalizedMousePosition)
        {
            m_pitch = normalizedMousePosition;
        }

        void PitchShiftControl::updatePitch(const f32vec2& normalizedMousePosition)
        {
            f32vec2 delta = normalizedMousePosition - m_pitch;
            m_translation.x += delta.x;
            m_translation.y += delta.y;
            m_pitch = normalizedMousePosition;
        }

        void PitchShiftControl::startShift(const f32vec2& normalizedMousePosition)
        {
            m_shift = normalizedMousePosition;
        }      

        void PitchShiftControl::updateShift(const f32vec2& normalizedMousePosition)
        {
            f32vec2 delta = normalizedMousePosition - m_shift;
            m_translation.z -= delta.y;
            m_shift = normalizedMousePosition;
        }
       
        void PitchShiftControl::reset()
        {
            m_translation = m_defaultTranslation;
            m_pitch = f32vec2(0, 0);
            m_shift = f32vec2(0, 0);
        }

        f32vec3 PitchShiftControl::getTranslation() const
        {
            return m_translation;
        }

        void PitchShiftControl::setTranslation(const f32vec3 val)
        {
            m_translation = val;
        }

        glm::mat4 PitchShiftControl::getTranslationMatrix() const
        {
            glm::mat4 result;
            result = glm::translate(m_translation);
            return result;
        }
    }
}
