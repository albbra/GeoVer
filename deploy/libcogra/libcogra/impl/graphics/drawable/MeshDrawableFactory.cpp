#include <cogra/graphics/drawable/MeshDrawableFactory.h>
#include <cogra/io/CograBinaryMeshFile.h>
namespace cogra
{
namespace graphics
{
namespace drawable
{

MeshDrawable MeshDrawableFactory::fromCograBinaryMeshFile(const cogra::io::CograBinaryMeshFile & cograBinaryMeshFile)
{
    std::vector<VertexAttributeTypeInfo> vertexAttribInformation;
    vertexAttribInformation.emplace_back(cograBinaryMeshFile.getPositionsPtr(), GL_FLOAT, 3, static_cast<uint32>(sizeof(f32vec3)));
    for(GLuint aIdx = 0; aIdx < cograBinaryMeshFile.getNumAttributes(); aIdx++)
    {
        vertexAttribInformation.emplace_back(cograBinaryMeshFile.getAttributePtr(aIdx), GL_FLOAT, cograBinaryMeshFile.getAttributeComponents(aIdx), cograBinaryMeshFile.getAttributeElementSize(aIdx));
    }
    return MeshDrawable(cograBinaryMeshFile.getTriangleIndices(), cograBinaryMeshFile.getNumTriangles() * 3, 
                        MeshDrawable::PrimitiveType::Triangles, 
                        cograBinaryMeshFile.getNumVertices(), 
                        vertexAttribInformation);
}

}
}
}