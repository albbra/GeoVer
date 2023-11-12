#pragma once
#include <cogra/types.h>
#include <vector>
#include <deque>
namespace cogra
{
/// <summary>
/// A data structure that represents Jarek Rossignac's Corner Table.
/// 
/// The data strucutres works as follows: Suppose, we have a mesh, for example:
/// 
///        5-----4
///       / \   / \
///      /   \ /   \
///     6-----2-----3
///      \   / \   /
///       \ /   \ /
///        0-----1      
/// 
/// 
/// We have a regular index buffer for that:
/// [0, 1, 2]
/// [2, 1, 3]
/// [2, 3, 4]
/// [5, 2, 4]
/// [6, 2, 5]
/// [6, 0, 2].
/// 
/// In this data structure, we store them in m_triangles.
/// 
/// The corresponding _corners_ are indicies into  that index buffer. 
/// In the example that would be:
/// [ 0,  1,  2]
/// [ 3,  4,  5]
/// [ 6,  7,  8]
/// [ 9, 10, 11]
/// [12, 13, 14]
/// [15, 16, 17].
/// 
/// Those corners are just consecutive integer numbers. 
/// Therefore, we do not have to store them explicitly in this data structure.
/// 
/// Now, here comes the important part: 
/// For each corner we define an _opposite corner_.
/// Given a corner index that is defined within a triangle.
/// Take the triangle-edge that opposite to our corner.
/// At that edge you find A) one or B) two triangles. 

/// A) If there is only one triangle, then our corner has opposite corner -1.

/// Example: Consider the fourth triangle [5, 2, 4]. 
/// Its corners are [ 9, 10, 11].
/// For corner 10 (vertex 2) the opposite edge is [4, 5].
/// At that edge, there is only one triangle, i.e., the triangle of our corner.
/// So the opposite corner of our corner 10 is -1.
/// 
/// B) If there are two triangles at that edge, then take the _opposite-triangle_ , i.e., that is the triangle not containing of our corner.
/// 
/// Example: Consider again the fourth triangle [5, 2, 4]. 
/// Its corners are [ 9, 10, 11].
/// For corner 11 (vertex 4) the opposite edge is [5, 2].
/// At that edge, there are triangles, i.e., the triangle of our corner [5, 2, 4] and the opposite-triangle [6, 2, 5]
/// 
/// Within the opposite-triangle, we need to find the only vertex that is not shared between the opposite-triangle and the original triangle.
/// We call the vertex the _opposite vertex_.
/// 
/// Example: The vertex not shared by triangle [5, 2, 4] and the opposite-triangle [6, 2, 5] within the oppsite-triangle is 6.
/// 
/// For that vertex, we determine the corner index and we are done:
/// This corner index is then, the opposite corner to our original corner.
/// 
/// Example: The opposite-triangle [6, 2, 5] has corners [12, 13, 14]. 
/// The vertex with index 6 has corner index 12.
/// 
/// If we do that for every corner, we get the following opposite table.
/// In this data structure, we sotre that information in m_opposite.
/// 
/// Example: For the triangle mesh above, the opposite array looks like that:
/// [ 5, 15, -1]
/// [-1,  8,  0]
/// [-1,  9,  4]
/// [ 7, -1, 12]
/// [11, -1, 16]
/// [ 1, 14, -1]
/// 
/// Give that opposite table, we can find the previous and next triangle to a fgiven triangle and fan around, amongst other things.
/// 
/// </summary>
class TriangleTopology
{
public:
  /// <summary>
  /// Creates a corner table data structure from an index buffer. 
  /// </summary>
  /// <param name="triangles">Index buffer, three indices make a triangle.</param>
  /// <param name="nIndices">Number of indicies (not number of triangles!)</param>
  TriangleTopology(int32 const * const triangles, size_t nIndices);

  /// <summary>
  /// Constructor provided for convinience to create a corner table data structure from an index buffer.
  /// </summary>
  /// <param name="triangles">Index buffer, three indices make a triangle.</param>
  explicit TriangleTopology(const std::vector<int32>& triangles);

  /// <summary>
  /// Returns the oppositve corner index.  
  /// </summary>
  int32 oppositeCornerIdx(const int32 cornerIdx) const;

  /// <summary>
  /// Given a corner index, return the corresponding vertex index.
  /// </summary>
  int32 cornerIdxToVertexIdx(const int32 cornerIdx) const;

  /// <summary>
  /// Given a corner index, return the correpsonding triangle, index.
  /// </summary>
  int32 cornerIdxToTriangleIdx(const int32 cornerIdx) const;

  /// <summary>
  /// Given a triangle index, return the corresponding corner index.
  /// </summary>
  int32 triangleIdxToCornerIdx(const int32 triangleIdx) const;

  /// <summary>
  /// Given a corner index, compute the next corner with the triangle.
  /// </summary>
  int32 nextCornerIdx(const int32 cornerIdx) const;

  /// <summary>
  /// Given a corner index, compute the previous corner with the triangle.
  /// </summary>
  int32 previousCornerIdx(const int32 cornerIdx) const;

  /// <summary>
  /// Given a corner index, compute the corner index to the left to that corner in the neighboring triangle.
  /// </summary>
  int32 leftCornerIdx(const int32 cornerIdx) const;

  /// <summary>
/// Given a corner index, compute the corner index to the right to that corner in the neighboring triangle.
/// </summary>
  int32 rightCornerIdx(const int32 cornerIdx) const;

  /// <summary>
  /// Given a triangle index, return all three indices to that triangle.
  /// </summary>
  i32vec3 triangleIdxToTriangle(const int32 triangleIdx) const;

  /// <summary>
  /// For a given corner index, return all corner indices that share the same vertex index. 
  /// </summary>
  std::deque<int32> cornerFan(const int32 cornerIdx) const;

  /// <summary>
  /// Given a triangle index, return the triangle index of the left triangle.
  /// </summary>
  int32 leftTriangleIdx(const int32 triangleIdx) const;

  /// <summary>
  /// Given a triangle index, return the triangle index of the right triangle.
  /// </summary>
  int32 rightTriangleIdx(const int32 triangleIdx) const;

  /// <summary>
  /// Given a triangle index, return the triangle index of the opposite triangle.
  /// </summary>
  int32 oppositeTriangleIdx(const int32 triangleIdx) const;

  /// <summary>
  /// Returns the number of triangles.
  /// </summary>  
  size_t nTriangles() const;

  /// <summary>
  /// Returns the number of indices.
  /// </summary>
  /// <returns></returns>
  size_t nIndices() const;

private:
  std::vector<int32> m_triangles;
  std::vector<int32> m_opposite;
};
}