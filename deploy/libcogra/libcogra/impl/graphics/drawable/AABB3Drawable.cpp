/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/graphics/drawable/AABB3Drawable.h>
#include <array>
#include <cogra/gl/OpenGLRuntimeError.h>
using namespace cogra::graphics::drawable;
namespace
{
const cogra::uint32 NumberVertices = 8;
const cogra::uint32 NumberOfIndices = 24;

std::array<cogra::f32vec3, NumberVertices> positions
=
{
cogra::f32vec3(0.0f, 0.0f, 0.0f),
cogra::f32vec3(1.0f, 0.0f, 0.0f),
cogra::f32vec3(1.0f, 1.0f, 0.0f),
cogra::f32vec3(0.0f, 1.0f, 0.0f),
cogra::f32vec3(0.0f, 0.0f, 1.0f),
cogra::f32vec3(1.0f, 0.0f, 1.0f),
cogra::f32vec3(1.0f, 1.0f, 1.0f),
cogra::f32vec3(0.0f, 1.0f, 1.0f)
};

std::array<cogra::uint32, NumberOfIndices> indexBuffer =
{ 
    0, 1,
    1, 2,
    2, 3,
    3, 0,
    4, 5,
    5, 6,
    6, 7,
    7, 4,
    0, 4,
    1, 5,
    2, 6,
    3, 7 };
}

namespace cogra
{
namespace graphics
{
namespace drawable
{
AABB3Drawable::AABB3Drawable()
    : m_unitBoundingBox(::indexBuffer.data(), ::indexBuffer.size(),
                        MeshDrawable::PrimitiveType::Lines, ::positions.size(), 
                        ::positions.data())
{
}

AABB3Drawable::~AABB3Drawable()
{
}

void AABB3Drawable::draw() const
{
    m_unitBoundingBox.draw();
}

cogra::f32mat4 AABB3Drawable::unitCubeToAABB(const cogra::graphics::geometry::AABB3& aabb)
{
    f32vec3 t = aabb.getMin();
    f32vec3 s = aabb.getDiagonal();
    f32mat4 m(1.0);
    m[3].x = t.x;
    m[3].y = t.y;
    m[3].z = t.z;
    m[3].w = 1.0f;
    m[0].x = s.x;
    m[1].y = s.y;
    m[2].z = s.z;
    return m;
}

}
}
}
