#include <cogra/graphics/drawable/PolyLineDrawable.h>

namespace cogra
{
namespace graphics
{
namespace drawable
{

PolyLineDrawable::PolyLineDrawable()
    : m_startIdx(0)
    , m_maxIdx(0)
{ }

PolyLineDrawable::PolyLineDrawable(const std::vector<f32vec2>& points)
{
    setPoints(points);

}

PolyLineDrawable::~PolyLineDrawable() { }

PolyLineDrawable::PolyLineDrawable(PolyLineDrawable&& other)
    : m_startIdx(other.m_startIdx)
    , m_maxIdx(other.m_maxIdx)    
{
    m_lineDrawable = std::move(other.m_lineDrawable);
}

//! Use the default move-copy assignment operator.
PolyLineDrawable& PolyLineDrawable::operator=(PolyLineDrawable&& other)
{
    if(this != &other)
    {
        m_startIdx = other.m_startIdx;
        m_maxIdx = other.m_maxIdx;
        m_lineDrawable = std::move(m_lineDrawable);
    }
    return *this;
}

void PolyLineDrawable::setPoints(const std::vector<f32vec2>& points)
{
    if(points.size() == 0)
    {
        return;
    }

    if(points.size() == 1)
    {
        std::vector<f32vec2> p;
        p.reserve(2);
        p.emplace_back(points[0]);
        p.emplace_back(points[0]);
        p.emplace_back(points[0]);
        p.emplace_back(points[0]);
        m_lineDrawable = MeshDrawable(MeshDrawable::LineStripAdjacency, p.size(), p.data());
        setStartIdxMaxIdx(getPrimtiveType());

    }
    else
    {
        std::vector<f32vec2> p;
        p.reserve(points.size() + 2);
        p.emplace_back(points[0] - (points[1] - points[0]));
        p.insert(p.end(), points.begin(), points.end());
        p.emplace_back(points[points.size() - 1] + (points[points.size() - 1] - points[points.size() - 2]));
        m_lineDrawable = MeshDrawable(MeshDrawable::LineStripAdjacency, p.size(), p.data());
        setStartIdxMaxIdx(getPrimtiveType());
    }
}

void PolyLineDrawable::setPrimitiveType(PrimitiveType primitiveType)
{
    switch(primitiveType)
    {
        case Points:
            m_lineDrawable.setPrimitiveType(MeshDrawable::Points);
            break;
        case LineStrip:
            m_lineDrawable.setPrimitiveType(MeshDrawable::LineStrip);
            break;
        case LineLoop:
            m_lineDrawable.setPrimitiveType(MeshDrawable::LineLoop);
            break;
        case Lines:
            m_lineDrawable.setPrimitiveType(MeshDrawable::Lines);
            break;
        case LineStripAdjacency:
            m_lineDrawable.setPrimitiveType(MeshDrawable::LineStripAdjacency);
            break;
        case LinesAdjacency:
            m_lineDrawable.setPrimitiveType(MeshDrawable::LinesAdjacency);
            break;
        default:
            m_lineDrawable.setPrimitiveType(MeshDrawable::Points);
    }
    setStartIdxMaxIdx(primitiveType);
}

PolyLineDrawable::PrimitiveType PolyLineDrawable::getPrimtiveType() const
{
    const auto meshPrimtiveType = m_lineDrawable.getPrimitiveType();
    switch(meshPrimtiveType)
    {
        case Points:
            return Points;
        case LineStrip:
            return LineStrip;
        case LineLoop:
            return LineLoop;
        case Lines:
            return Lines;
        case LineStripAdjacency:
            return LineStripAdjacency;
        case LinesAdjacency:
            return LinesAdjacency;
        default:
            return Points;
    }
}

void PolyLineDrawable::draw() const
{
    m_lineDrawable.draw(m_startIdx, m_maxIdx);
}

void PolyLineDrawable::setStartIdxMaxIdx(PrimitiveType primitiveType)
{
    if(primitiveType == MeshDrawable::LineStripAdjacency || primitiveType == MeshDrawable::LinesAdjacency)
    {
        m_startIdx = 0;
        m_maxIdx = m_lineDrawable.getNumVertices();
    }
    else
    {
        m_startIdx = 1;
        m_maxIdx = m_lineDrawable.getNumVertices() - 2;
    }
}
}
}
}