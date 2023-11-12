#pragma once
#ifndef COGRA_UI_WIREFRAMEWIDGET_H
#define COGRA_UI_WIREFRAMEWIDGET_H
#include <cogra/types.h>
namespace cogra
{
namespace ui
{
class WireFrameWidget
{
public:
  WireFrameWidget();

  void drawUI();

  bool isWireFrameEnabled() const
  {
    return m_enableWireframe;
  }

  cogra::float32 getLineWidth() const;

  cogra::float32 getPolygonOffsetFactor() const;

  cogra::float32 getPolygonOffsetUnits() const;

  cogra::f32vec3 getWireframeColor() const;

  void setWireframeColor(const cogra::f32vec3& color);

private:
  bool            m_enableWireframe;
  cogra::float32  m_lineWidth;
  cogra::float32  m_polygonOffsetFactor;
  cogra::float32  m_polygonOffsetUnits;
  cogra::f32vec3  m_wireFrameColor;
};

}
}
#endif