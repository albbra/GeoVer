/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/ui/TrackballControl.h>
namespace cogra
{
    namespace ui
    {
        TrackballControl::TrackballControl(float32 radius)
            : m_radius(radius)
            , m_normalizedMouseCoordinates(0, 0)
            , m_rotation(glm::angleAxis(0.0f, f32vec3(0, 0, -1)))
        { }

        void TrackballControl::startRotation(const f32vec2& normalizedMouseCoordinates)
        {
            m_normalizedMouseCoordinates = normalizedMouseCoordinates;
        }

        void TrackballControl::updateRotation(const f32vec2& normalizedMouseCoordinates)
        {
            if(normalizedMouseCoordinates.x == m_normalizedMouseCoordinates.x && normalizedMouseCoordinates.y == m_normalizedMouseCoordinates.y)
            {
                return;
            }
            f32vec3 p1 = f32vec3(m_normalizedMouseCoordinates.x, m_normalizedMouseCoordinates.y, projectToSphere(m_normalizedMouseCoordinates));
            f32vec3 p2 = f32vec3(normalizedMouseCoordinates.x, normalizedMouseCoordinates.y, projectToSphere(normalizedMouseCoordinates));
            f32vec3 a = glm::normalize(glm::cross(p2, p1));

            float32 phi = 2.0f * glm::asin(glm::clamp(glm::length(p1 - p2) / (2.0f * m_radius), -1.0f, 1.0f));
            m_rotation = m_rotation * glm::angleAxis(phi, a);
            m_rotation = glm::normalize(m_rotation);
            m_normalizedMouseCoordinates = normalizedMouseCoordinates;
        }

        float32 TrackballControl::projectToSphere(const f32vec2& normalizedMouseCoordinates)
        {
            float32 d, t, z;
            d = normalizedMouseCoordinates.x * normalizedMouseCoordinates.x + normalizedMouseCoordinates.y * normalizedMouseCoordinates.y;
            if(d < m_radius * m_radius * 0.5f)
            {
                z = sqrtf(m_radius * m_radius - d);
            }
            else
            {
                t = m_radius * m_radius / 2.0f;
                z = t / sqrtf(d);
            }
            return z;
        }

        void TrackballControl::reset()
        {
            m_rotation = glm::angleAxis(0.0f, f32vec3(0, 0, -1));
        }

        glm::mat4x4 TrackballControl::getRotationMatrix() const
        {
            return glm::transpose(glm::toMat4(m_rotation));
        }

        const f32quat& TrackballControl::getRotationQuaterion() const
        {
            return m_rotation;
        }

        void TrackballControl::setRotationQuaterion(const f32quat& q)
        {
            m_rotation = q;
        }
    }
}
