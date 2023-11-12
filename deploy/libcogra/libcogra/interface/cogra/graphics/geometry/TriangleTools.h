#pragma once
#include <cogra/types.h>
#include <vector>
namespace cogra
{
namespace TriangleTools
{

/// <summary>
/// Rotaes the indices of a triangle to the right.
/// 
/// Example If i32vec3 t = [0, 1, 2], the rotateTriangleIndicesRight(t) returns [2, 0, 1].
/// </summary>
i32vec3 rotateTriangleIndicesRight(const i32vec3& t);

/// /// <summary>
/// Rotaes the indices of a triangle to the right.
/// 
/// Example If i32vec3 t = [0, 1, 2], the rotateTriangleIndicesRight(t) returns [1, 2, 0].
/// </summary>
i32vec3 rotateTriangleIndicesLeft(const i32vec3& t);


/// <summary>
/// Compares two arrays of triangles. 
/// 
/// The indices of the triangles may be arbitarliy rotated. Ignores degenerate triangles.
/// </summary>
bool compareTriangles(int32 const * const a, int32 const * const b, size_t nIndiciesA, size_t nIndicesB);

/// <summary>
/// Return if at least two indices of the triangle are identical.
/// </summary>
bool isDegenerate(const i32vec3 triangle);

/// <summary>
/// Returns a new index buffer with degenerate triangles removed.
/// </summary>
std::vector<i32vec3> removeDegenerateTriangles(i32vec3 const * const triangles, size_t nTriangles);

}
}