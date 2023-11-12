#include <cogra/ui/WireFrameWidget.h>
#include <imgui/imgui.h>

namespace cogra
{
namespace ui
{

WireFrameWidget::WireFrameWidget()
  : m_enableWireframe(false)
  , m_lineWidth(1.0f)
  , m_polygonOffsetFactor(-0.5f)
  , m_polygonOffsetUnits(0.0f)
  , m_wireFrameColor(1.0f, 1.0f, 1.0f)
{

}

void WireFrameWidget::drawUI()
{
  if(ImGui::CollapsingHeader("Wire Frame"))
  {
    ImGui::Checkbox("Overlay Wire Frame", &m_enableWireframe);
    ImGui::ColorEdit3("Wire Frame Color", glm::value_ptr(m_wireFrameColor));
    ImGui::SliderFloat("Line Width", &m_lineWidth, 0.1f, 32.0f);
    ImGui::SliderFloat("Polygon Factor", &m_polygonOffsetFactor, -32.0f, 32.0f);
    ImGui::SliderFloat("Polygon Offset", &m_polygonOffsetUnits, -32.0f, 32.0f);
  }
}

cogra::float32 WireFrameWidget::getLineWidth() const
{
  return m_lineWidth;
}

cogra::float32 WireFrameWidget::getPolygonOffsetFactor() const
{
  return  m_polygonOffsetFactor;
}

cogra::float32 WireFrameWidget::getPolygonOffsetUnits() const
{
  return m_polygonOffsetUnits;
}

cogra::f32vec3 WireFrameWidget::getWireframeColor() const
{
  return m_wireFrameColor;
}

void WireFrameWidget::setWireframeColor(const cogra::f32vec3 & color)
{
  m_wireFrameColor = color;
}

}
}