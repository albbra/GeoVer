#include <cogra/graphics/geometry/TriangleTopology.h>
#include <unordered_map>
#include <algorithm>
#include <glm/gtx/hash.hpp>
using namespace cogra;

namespace
{
std::vector<int32> createOppositeTable(int32 const * const  triangles, size_t nIndices)
{
  std::vector<int32> result(nIndices, -1);

  std::unordered_map<i32vec2, int32> edgeToTriangle;

  edgeToTriangle.reserve(nIndices * 2);

  auto insert = [&result, &edgeToTriangle](int32 v0, int32 v1, int32 corner)
  {
    const auto r = edgeToTriangle.find(i32vec2(v1, v0));
    if(r != edgeToTriangle.end())
    {
      result[corner] = r->second;
      result[r->second] = corner;
    }
    edgeToTriangle.emplace(i32vec2(v0, v1), corner);
  };

  auto preservesManifoldness = [&edgeToTriangle](int32 v0, int32 v1, int32 v2)
  {
    const bool degenerate = (v0 == v1) || (v1 == v2) || (v0 == v2);
    if(degenerate)
    {
      return false;
    }
    const auto edge2Exists = edgeToTriangle.find(i32vec2(v0, v1)) != edgeToTriangle.end();
    if(edge2Exists)
    {
      return false;
    }
    const auto edge0Exists = edgeToTriangle.find(i32vec2(v1, v2)) != edgeToTriangle.end();
    if(edge0Exists)
    {
      return false;
    }
    const auto edge1Exists = edgeToTriangle.find(i32vec2(v2, v0)) != edgeToTriangle.end();
    if(edge1Exists)
    {
      return false;
    }
    return true;
  };


  for(size_t tIdx = 0; tIdx < nIndices; tIdx += 3)
  {
    const auto v0 = triangles[tIdx + 0];
    const auto v1 = triangles[tIdx + 1];
    const auto v2 = triangles[tIdx + 2];

    if(preservesManifoldness(v0, v1, v2))
    {
      insert(v0, v1, static_cast<int32>(tIdx) + 2);
      insert(v1, v2, static_cast<int32>(tIdx) + 0);
      insert(v2, v0, static_cast<int32>(tIdx) + 1);
    }
  }  
  return result;
}
}

namespace cogra
{

TriangleTopology::TriangleTopology(int32 const * const triangles, size_t nIndices)
  : m_triangles(triangles, triangles + nIndices)
  , m_opposite(createOppositeTable(triangles, nIndices))

{ }

TriangleTopology::TriangleTopology(const std::vector<int32>& triangles)
  : m_triangles(triangles)
  , m_opposite(createOppositeTable(triangles.data(), triangles.size()))
{ }

int32 TriangleTopology::oppositeCornerIdx(const int32 cornerIdx) const
{
  return m_opposite[cornerIdx];
}

int32 TriangleTopology::cornerIdxToVertexIdx(const int32 cornerIdx) const
{
  return m_triangles[cornerIdx];
}

int32 TriangleTopology::cornerIdxToTriangleIdx(const int32 cornerIdx) const
{
  return cornerIdx == - 1 ? -1 : cornerIdx / 3;
}

int32 TriangleTopology::triangleIdxToCornerIdx(const int32 triangleIdx) const
{
  return triangleIdx * 3;
}

int32 TriangleTopology::nextCornerIdx(const int32 cornerIdx) const
{
  const auto triangleIdx = cornerIdxToTriangleIdx(cornerIdx);
  const auto localCornerIdx = cornerIdx - triangleIdx * 3;
  const auto nextLocalCornerIdx = localCornerIdx == 2 ? 0 : localCornerIdx + 1;
  return triangleIdx * 3 + nextLocalCornerIdx;
}

int32 TriangleTopology::previousCornerIdx(const int32 cornerIdx) const
{
  const auto triangleIdx = cornerIdxToTriangleIdx(cornerIdx);
  const auto localCornerIdx = cornerIdx - triangleIdx * 3;
  const auto previousLocalCornerIdx = localCornerIdx == 0 ? 2 : localCornerIdx - 1;
  return triangleIdx * 3 + previousLocalCornerIdx;
}

int32 TriangleTopology::leftCornerIdx(const int32 cornerIdx) const
{
  const auto p = previousCornerIdx(cornerIdx);
  return m_opposite[p];
}

int32 TriangleTopology::rightCornerIdx(const int32 cornerIdx) const
{
  const auto n = nextCornerIdx(cornerIdx);
  return m_opposite[n];
}

i32vec3 TriangleTopology::triangleIdxToTriangle(const int32 triangleIdx) const
{
  const auto baseIdx = triangleIdx * 3;
  return i32vec3(m_triangles[baseIdx + 0], m_triangles[baseIdx + 1], m_triangles[baseIdx + 2]);
}

std::deque<int32> TriangleTopology::cornerFan(const int32 cornerIdx) const
{
  std::deque<int32> result;    
  auto firstCorner = nextCornerIdx(cornerIdx);
  result.emplace_back(firstCorner);
  auto iter = previousCornerIdx(cornerIdx);
  iter = m_opposite[iter];
  while(iter != -1)
  {
    if(iter == firstCorner)
    {
      return result;
    }
    result.emplace_back(iter);
    iter = rightCornerIdx(iter);
  }

  firstCorner = previousCornerIdx(cornerIdx);
  result.emplace_front(firstCorner);

  iter = nextCornerIdx(cornerIdx);
  iter = m_opposite[iter];
  while(iter != -1)
  {
    if(iter == firstCorner)
    {
      return result;
    }
    result.emplace_front(iter);
    iter = leftCornerIdx(iter);
  }

  return result;
}
int32 TriangleTopology::leftTriangleIdx(const int32 triangleIdx) const
{
  const auto cIdx = triangleIdxToCornerIdx(triangleIdx);
  const auto lIdx = leftCornerIdx(cIdx);
  return cornerIdxToTriangleIdx(lIdx);
}
int32 TriangleTopology::rightTriangleIdx(const int32 triangleIdx) const
{
  const auto cIdx = triangleIdxToCornerIdx(triangleIdx);
  const auto rIdx = rightCornerIdx(cIdx);
  return cornerIdxToTriangleIdx(rIdx);
}
int32 TriangleTopology::oppositeTriangleIdx(const int32 triangleIdx) const
{
  const auto cIdx = triangleIdxToCornerIdx(triangleIdx);
  const auto oIdx = oppositeCornerIdx(cIdx);
  return cornerIdxToTriangleIdx(oIdx);
}
size_t TriangleTopology::nTriangles() const
{
  return m_triangles.size() / 3;
}
size_t TriangleTopology::nIndices() const
{
  return m_triangles.size();
}
}