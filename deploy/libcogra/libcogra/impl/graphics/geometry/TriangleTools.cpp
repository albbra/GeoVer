#include <cogra/graphics/geometry/TriangleTools.h>
#include <unordered_set>
#include <glm/gtx/hash.hpp>
namespace cogra
{
namespace TriangleTools
{
i32vec3 rotateTriangleIndicesRight(const i32vec3 & t)
{
  return i32vec3(t.z, t.x, t.y);
}

i32vec3 rotateTriangleIndicesLeft(const i32vec3 & t)
{
  return i32vec3(t.y, t.z, t.x);
}


bool compareTriangles(int32 const * const a, int32 const * const b, size_t nIndicesA, size_t nIndicesB)
{
  std::unordered_set<i32vec3> setA;

  for(size_t i = 0; i < nIndicesA; i += 3)
  {
    i32vec3 t(a[i], a[i + 1], a[i + 2]);
    if(isDegenerate(t))
    {
      continue;
    }
    const auto mini = glm::compMin(t);
    while(t.x != mini)
    {
      t = rotateTriangleIndicesRight(t);
    }

    setA.emplace_hint(setA.begin(), t);
  }

  for(size_t i = 0; i < nIndicesB; i += 3)
  {
    i32vec3 t(b[i], b[i + 1], b[i + 2]);
    if(isDegenerate(t))
    {
      continue;
    }

    const auto mini = glm::compMin(t);
    while(t.x != mini)
    {
      t = rotateTriangleIndicesRight(t);
    }
    if(setA.find(t) == setA.end())
    {
      return false;
    }
  }
  return true;
}

bool isDegenerate(const i32vec3 triangle)
{
  return (triangle.x == triangle.y) ||
    (triangle.x == triangle.z) ||
    (triangle.y == triangle.z);
}

std::vector<i32vec3> removeDegenerateTriangles(i32vec3 const * const triangles, size_t nTriangles)
{
  std::vector<i32vec3> result;
  for(size_t tIdx = 0; tIdx < nTriangles; tIdx++)
  {
    if(!TriangleTools::isDegenerate(triangles[tIdx]))
    {
      result.emplace_back(triangles[tIdx]);
    }
  }
  return result;
}


}
}