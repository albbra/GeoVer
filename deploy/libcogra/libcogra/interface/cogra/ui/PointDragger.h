/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 - 2018 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#pragma once
#ifndef COGRA_UI_POINTDRAGGER_H
#define COGRA_UI_POINTDRAGGER_H
#include <cogra/types.h>
#include <vector>
using namespace cogra;
namespace cogra
{
namespace ui
{
class PointDragger
{
public:

    void onMouseDown(const f32vec2& position, std::vector<f32vec2>& points, const float32 radius);

    void onMouseUp();

    bool onMouseMove(const f32vec2& position, std::vector<f32vec2>& controlPoints) const;

    uint32 getSelectedPoint() const;

    void setSelectedPoint(uint32 index);

    bool isAnyPointSelected() const;

private:
    static constexpr auto c_noPointSelected = static_cast<uint32>(-1);

    uint32 m_selectedPoint = c_noPointSelected;

    uint32 isPointHit(const f32vec2& position, const std::vector<f32vec2>& points, const float32 radius) const;
};
}
}
#endif