#pragma once
/// Cogra --- Coburg Graphics Framework 2018
/// (C) 2017-2018 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_DRAWABLE_POLYLINEDRAWABLE_H_
#define COGRA_GRAPHICS_DRAWABLE_POLYLINEDRAWABLE_H_
#include <cogra/types.h>
#include <cogra/graphics/drawable/Drawable.h>
#include <cogra/graphics/drawable/MeshDrawable.h>

namespace cogra
{
namespace graphics
{
namespace drawable
{

/// <summary>
/// Draw a polyline as 
/// - a line with adjacency 
/// - points 
/// - line strip
/// as primitive.
/// 
/// This class is useful to create custom lines.
/// 
/// </summary>
class PolyLineDrawable : public Drawable
{
public:

    /// <summary>
    /// Supported primitive yype https://www.khronos.org/opengl/wiki/Primitive for details.
    /// </summary>
    enum PrimitiveType
    {
        Points = 0,
        LineStrip,
        LineLoop,
        Lines,
        LineStripAdjacency,
        LinesAdjacency
    };

    /// <summary>
    /// Creates an empty poly line.
    /// </summary>
    PolyLineDrawable();


    /// <summary>
    /// Creates a poly line. Adds a point before the first point and after the last point to support lines with adjacency.
    /// </summary>
    /// <param name="points">Points that define the polyline.</param>
    PolyLineDrawable(const std::vector<f32vec2>& points);

    /// <summary>
    /// Default destructor.
    /// </summary>
    ~PolyLineDrawable();

    //! Disallow copy constructor.
    PolyLineDrawable(const PolyLineDrawable&) = delete;

    //! Disallow assignment operator.
    PolyLineDrawable& operator=(const PolyLineDrawable&) = delete;

    PolyLineDrawable(PolyLineDrawable&& other);

    //! Use the default move-copy assignment operator.
    PolyLineDrawable& operator=(PolyLineDrawable&& other);

    /// <summary>
    /// Sets a poly line. Adds a point before the first point and after the last point to support lines with adjacency.
    /// </summary>
    /// <param name="points">Points that define the polyline.</param>    
    void setPoints(const std::vector<f32vec2>& points);

    /// <summary>
    /// Sets the primtive type for the polyline.
    /// </summary>
    void setPrimitiveType(PrimitiveType primitiveType);

    /// <summary>
    /// Returns the primtive type that is used for drawing.
    /// </summary>   
    PrimitiveType getPrimtiveType() const;

    /// <summary>
    /// Draws the polyline.
    /// </summary>
    void draw() const override;
private:
    size_t      m_startIdx;

    size_t      m_maxIdx;

    MeshDrawable m_lineDrawable;

    void setStartIdxMaxIdx(PrimitiveType primitiveType);
};

}
}
}

#endif