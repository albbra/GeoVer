/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/types.h>
#include <cogra/graphics/drawable/ScreenFillingPrimitive.h>
#include <array>
#include <cogra/gl/OpenGLRuntimeError.h>

using namespace cogra;

namespace
{

constexpr size_t NumberVertices = 3;

std::array<f32vec4, NumberVertices> positions =
{
    f32vec4(-1, -1,  0, 1), // 0
    f32vec4(3, -1,  0, 1), // 1
    f32vec4(-1,  3,  0, 1), // 2                  
};

}

namespace cogra
{
namespace graphics
{
namespace drawable
{

ScreenFillingPrimitive::ScreenFillingPrimitive()
    : m_screenFillingMesh(MeshDrawable::Triangles, positions.size(), positions.data())
{ }

void ScreenFillingPrimitive::draw() const
{
    m_screenFillingMesh.draw();
}

}
}
}

