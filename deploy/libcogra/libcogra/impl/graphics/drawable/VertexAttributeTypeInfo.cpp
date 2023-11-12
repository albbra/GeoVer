#include <cogra/graphics/drawable/VertexAttributeTypeInfo.h>
#include <glad/glad.h>
namespace cogra
{
namespace graphics
{
namespace drawable
{



VertexAttributeTypeInfo::VertexAttributeTypeInfo(const void* const dataParam, uint32 enumTypeParam, uint32 numberOfComponentsParam, uint32 sizeInBytesParam)
	: data(dataParam)
	, enumType(enumTypeParam)
	, numberOfComponents(numberOfComponentsParam)
	, sizeInBytes(sizeInBytesParam)
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(0)
{

}

VertexAttributeTypeInfo::VertexAttributeTypeInfo(const std::nullptr_t dataParam)
	: data(dataParam)
	, enumType(GL_INT)
	, numberOfComponents(0)
	, sizeInBytes(0)
	, sizePerElement(0)
	, normalized(false)
	, sizedInternalFormat(0)
{
}


VertexAttributeTypeInfo::VertexAttributeTypeInfo(uint32 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_INT)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(uint32))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_R32UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(float32 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_FLOAT)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(float32))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_R32F)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(f32vec2 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_FLOAT)
	, numberOfComponents(2)
	, sizeInBytes(sizeof(f32vec2))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RG32F)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(f32vec3 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_FLOAT)
	, numberOfComponents(3)
	, sizeInBytes(sizeof(f32vec3))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RGB32F)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(f32vec4 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_FLOAT)
	, numberOfComponents(4)
	, sizeInBytes(sizeof(f32vec4))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui32vec1 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_INT)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(ui32vec1))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_R32UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui32vec2 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_INT)
	, numberOfComponents(2)
	, sizeInBytes(sizeof(ui32vec2))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RG32UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui32vec3 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_INT)
	, numberOfComponents(3)
	, sizeInBytes(sizeof(ui32vec3))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RGB32UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui32vec4 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_INT)
	, numberOfComponents(4)
	, sizeInBytes(sizeof(ui32vec4))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RGBA32UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(uint16 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_SHORT)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(uint16))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_R16UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui16vec1 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_SHORT)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(ui16vec1))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_R16UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui16vec2 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_SHORT)
	, numberOfComponents(2)
	, sizeInBytes(sizeof(ui16vec2))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RG16UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui16vec3 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_SHORT)
	, numberOfComponents(3)
	, sizeInBytes(sizeof(ui16vec3))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RGB16UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui16vec4 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_SHORT)
	, numberOfComponents(4)
	, sizeInBytes(sizeof(ui16vec4))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RGBA16UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui8vec1 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_BYTE)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(ui8vec1))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_R8UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui8vec2 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_BYTE)
	, numberOfComponents(2)
	, sizeInBytes(sizeof(ui8vec2))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RG8UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui8vec3 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_BYTE)
	, numberOfComponents(3)
	, sizeInBytes(sizeof(ui8vec3))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RGB8UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui8vec4 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_BYTE)
	, numberOfComponents(4)
	, sizeInBytes(sizeof(ui8vec4))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RGBA8UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui8vec1_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_BYTE)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(ui8vec1))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_R8)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui8vec2_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_BYTE)
	, numberOfComponents(2)
	, sizeInBytes(sizeof(ui8vec2))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RG8)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui8vec3_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_BYTE)
	, numberOfComponents(3)
	, sizeInBytes(sizeof(ui8vec3))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RGB8)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui8vec4_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_BYTE)
	, numberOfComponents(4)
	, sizeInBytes(sizeof(ui8vec4))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RGBA8)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui16vec1_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_SHORT)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(ui16vec1))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_R16)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui16vec2_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_SHORT)
	, numberOfComponents(2)
	, sizeInBytes(sizeof(ui16vec2))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RG16)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui16vec3_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_SHORT)
	, numberOfComponents(3)
	, sizeInBytes(sizeof(ui16vec3))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RGB16)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui16vec4_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_SHORT)
	, numberOfComponents(4)
	, sizeInBytes(sizeof(ui16vec4))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RGBA16)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui32vec1_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_INT)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(ui32vec1))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_R32UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui32vec2_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_INT)
	, numberOfComponents(2)
	, sizeInBytes(sizeof(ui32vec2))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RG32UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui32vec3_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_INT)
	, numberOfComponents(3)
	, sizeInBytes(sizeof(ui32vec3))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RGB32UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(ui32vec4_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_UNSIGNED_INT)
	, numberOfComponents(4)
	, sizeInBytes(sizeof(ui32vec4))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RGBA32UI)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(i16vec2_normalized const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_SHORT)
	, numberOfComponents(2)
	, sizeInBytes(sizeof(ui16vec2))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RG16)
{ }


VertexAttributeTypeInfo::VertexAttributeTypeInfo(f16vec1 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_HALF_FLOAT)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(ui16vec1))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_R16)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(f16vec2 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_HALF_FLOAT)
	, numberOfComponents(2)
	, sizeInBytes(sizeof(ui16vec2))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RG16)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(f16vec3 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_HALF_FLOAT)
	, numberOfComponents(3)
	, sizeInBytes(sizeof(ui16vec3))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RGB16)
{ }

VertexAttributeTypeInfo::VertexAttributeTypeInfo(f16vec4 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_HALF_FLOAT)
	, numberOfComponents(4)
	, sizeInBytes(sizeof(ui16vec4))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(true)
	, sizedInternalFormat(GL_RGBA16)
{ }


// This is not going to work with OpenGL
VertexAttributeTypeInfo::VertexAttributeTypeInfo(uint64 const* const ptr)
	: data(static_cast<const void* const>(ptr))
	, enumType(GL_DOUBLE)
	, numberOfComponents(1)
	, sizeInBytes(sizeof(uint64))
	, sizePerElement(sizeInBytes / numberOfComponents)
	, normalized(false)
	, sizedInternalFormat(GL_RG32F)
{ }
}
}
}