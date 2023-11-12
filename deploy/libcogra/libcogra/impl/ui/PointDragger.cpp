#include <cogra/ui/PointDragger.h>

namespace cogra
{
namespace ui
{
void PointDragger::onMouseDown(const f32vec2 & position, std::vector<f32vec2>& points, const float32 radius)
{
    m_selectedPoint = isPointHit(position, points, radius);
}

void PointDragger::onMouseUp()
{
    m_selectedPoint = c_noPointSelected;
}
bool PointDragger::onMouseMove(const f32vec2 & position, std::vector<f32vec2>& controlPoints) const
{
    if(c_noPointSelected != m_selectedPoint)
    {
        if(m_selectedPoint < controlPoints.size())
        {
            controlPoints[m_selectedPoint] = position;
        }
        return true;
    }
    else
    {
        return false;
    }
}

uint32 PointDragger::getSelectedPoint() const
{
    return m_selectedPoint;
}

void PointDragger::setSelectedPoint(uint32 index)
{
    m_selectedPoint = index;
}

bool PointDragger::isAnyPointSelected() const
{
    return m_selectedPoint != c_noPointSelected;
}
uint32 PointDragger::isPointHit(const f32vec2 & position, const std::vector<f32vec2>& points, const float32 radius) const
{
    auto selectedPoint = c_noPointSelected;
    auto  minDistance = std::numeric_limits<float32>::max();
    uint32 idx = 0;
    for(auto c : points)
    {
        const auto distance = glm::length(position - c);
        if(distance < radius && distance < minDistance)
        {
            selectedPoint = idx;
            minDistance = distance;
        }
        idx++;
    }
    return selectedPoint;
}
}
}