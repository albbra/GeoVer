#ifndef COGRA_GRAPHICS_DRAWABLE_MESHDRAWABLEFACTOR_H
#define COGRA_GRAPHICS_DRAWABLE_MESHDRAWABLEFACTOR_H
#include <cogra/graphics/drawable/MeshDrawable.h>
namespace cogra
{
namespace io { class CograBinaryMeshFile; }
namespace graphics
{
namespace drawable
{
class MeshDrawableFactory
{
public:
    static MeshDrawable fromCograBinaryMeshFile(const cogra::io::CograBinaryMeshFile& cograBinaryMeshFile);
};
}
}
}
#endif