#ifndef COGRA_GRAPHICS_DRAWABLE_VERTEXATTRIBUTETYPEINFO_H_
#define COGRA_GRAPHICS_DRAWABLE_VERTEXATTRIBUTETYPEINFO_H_
#include <cogra/types.h>
namespace cogra
{
namespace graphics
{
namespace drawable
{
struct ui8vec1_normalized : public ui8vec1 {};
struct ui8vec2_normalized : public ui8vec2 { };
struct ui8vec3_normalized : public ui8vec3 { };
struct ui8vec4_normalized : public ui8vec4 { };

struct ui16vec1_normalized : public ui16vec1 { };
struct ui16vec2_normalized : public ui16vec2 { };
struct ui16vec3_normalized : public ui16vec3 { };
struct ui16vec4_normalized : public ui16vec4 { };

struct i16vec2_normalized : public i16vec2 { };

struct ui32vec1_normalized : public ui32vec1 { };
struct ui32vec2_normalized : public ui32vec2 { };
struct ui32vec3_normalized : public ui32vec3 { };
struct ui32vec4_normalized : public ui32vec4 { };

template<class T> struct ToNormalized { typedef typename T::type Type; };
template<> struct ToNormalized<ui8vec1> { typedef typename cogra::graphics::drawable::ui8vec1_normalized Type; };
template<> struct ToNormalized<ui8vec2> { typedef typename cogra::graphics::drawable::ui8vec2_normalized Type; };
template<> struct ToNormalized<ui8vec3> { typedef typename cogra::graphics::drawable::ui8vec3_normalized Type; };
template<> struct ToNormalized<ui8vec4> { typedef typename cogra::graphics::drawable::ui8vec4_normalized Type; };
template<> struct ToNormalized<ui16vec1> { typedef typename cogra::graphics::drawable::ui16vec1_normalized Type; };
template<> struct ToNormalized<ui16vec2> { typedef typename cogra::graphics::drawable::ui16vec2_normalized Type; };
template<> struct ToNormalized<ui16vec3> { typedef typename cogra::graphics::drawable::ui16vec3_normalized Type; };
template<> struct ToNormalized<ui16vec4> { typedef typename cogra::graphics::drawable::ui16vec4_normalized Type; };
template<> struct ToNormalized<ui32vec1> { typedef typename cogra::graphics::drawable::ui32vec1_normalized Type; };
template<> struct ToNormalized<ui32vec2> { typedef typename cogra::graphics::drawable::ui32vec2_normalized Type; };
template<> struct ToNormalized<ui32vec3> { typedef typename cogra::graphics::drawable::ui32vec3_normalized Type; };
template<> struct ToNormalized<ui32vec4> { typedef typename cogra::graphics::drawable::ui32vec4_normalized Type; };

template<> struct ToNormalized<i16vec2> { typedef typename cogra::graphics::drawable::i16vec2_normalized Type; };

struct f16vec1 : public ui16vec1 { };
struct f16vec2 : public ui16vec2 { };
struct f16vec3 : public ui16vec3 { };
struct f16vec4 : public ui16vec4 { };



/// <summary>
/// Contains information about the elements of a vertex attribute buffer.
/// </summary>
struct VertexAttributeTypeInfo
{	

	/// <summary>
  /// Creates an VertexAttributeTypeInfo
  /// </summary>
  /// <param name="dataParam">Pointer to the vertex attribute data on the CPU.</param>
  /// <param name="enumTypeParam">Underlying primtive data type, e.g. GL_FLOAT in case its a float, GL_INT if its an int.</param>
  /// <param name="numberOfComponentsParam">Number of components (e.g., 2 if its a 2D vector).</param>
  /// <param name="sizeInBytesParam">Size in bytes of an element of the vertex attribute buffer.</param>
	VertexAttributeTypeInfo(const void* const dataParam,
		uint32 enumTypeParam,
		uint32 numberOfComponentsParam,
		uint32 sizeInBytesParam);

	VertexAttributeTypeInfo(const std::nullptr_t dataParam);

	/// <summary>
	/// Constructs from a uint32 pointer.
	/// </summary>
	/// <param name="ptr">Pointer to the vertex attribute data on the CPU.</param>
	explicit VertexAttributeTypeInfo(uint32 const* const ptr);

	/// <summary>
	/// Constructs from a float32 pointer.
	/// </summary>
	/// <param name="ptr">Pointer to the vertex attribute data on the CPU.</param>
	explicit VertexAttributeTypeInfo(float32 const* const ptr);

	/// <summary>
	/// Constructs from a f32vec2 pointer.
	/// </summary>
	/// <param name="ptr">Pointer to the vertex attribute data on the CPU.</param>
	explicit VertexAttributeTypeInfo(f32vec2 const* const ptr);

	/// <summary>
	/// Constructs from a f32vec3 pointer.
	/// </summary>
	/// <param name="ptr">Pointer to the vertex attribute data on the CPU.</param>
	explicit VertexAttributeTypeInfo(f32vec3 const* const ptr);

	/// <summary>
	/// Constructs from a f32vec3 pointer.
	/// </summary>
	/// <param name="ptr">Pointer to the vertex attribute data on the CPU.</param>
	explicit VertexAttributeTypeInfo(f32vec4 const* const ptr);

	explicit VertexAttributeTypeInfo(ui32vec1 const* const ptr);
	explicit VertexAttributeTypeInfo(ui32vec2 const* const ptr);
	explicit VertexAttributeTypeInfo(ui32vec3 const* const ptr);
	explicit VertexAttributeTypeInfo(ui32vec4 const* const ptr);

	explicit VertexAttributeTypeInfo(uint16 const* const ptr);
	explicit VertexAttributeTypeInfo(ui16vec1 const* const ptr);
	explicit VertexAttributeTypeInfo(ui16vec2 const* const ptr);
	explicit VertexAttributeTypeInfo(ui16vec3 const* const ptr);
	explicit VertexAttributeTypeInfo(ui16vec4 const* const ptr);

	explicit VertexAttributeTypeInfo(ui8vec1 const* const ptr);
	explicit VertexAttributeTypeInfo(ui8vec2 const* const ptr);
	explicit VertexAttributeTypeInfo(ui8vec3 const* const ptr);
	explicit VertexAttributeTypeInfo(ui8vec4 const* const ptr);

	explicit VertexAttributeTypeInfo(ui8vec1_normalized const* const ptr);
	explicit VertexAttributeTypeInfo(ui8vec2_normalized const* const ptr);
	explicit VertexAttributeTypeInfo(ui8vec3_normalized const* const ptr);
	explicit VertexAttributeTypeInfo(ui8vec4_normalized const* const ptr);

	explicit VertexAttributeTypeInfo(ui16vec1_normalized const* const ptr);
	explicit VertexAttributeTypeInfo(ui16vec2_normalized const* const ptr);
	explicit VertexAttributeTypeInfo(ui16vec3_normalized const* const ptr);
	explicit VertexAttributeTypeInfo(ui16vec4_normalized const* const ptr);

	explicit VertexAttributeTypeInfo(ui32vec1_normalized const* const ptr);
	explicit VertexAttributeTypeInfo(ui32vec2_normalized const* const ptr);
	explicit VertexAttributeTypeInfo(ui32vec3_normalized const* const ptr);
	explicit VertexAttributeTypeInfo(ui32vec4_normalized const* const ptr);

	explicit VertexAttributeTypeInfo(i16vec2_normalized const* const ptr);

	explicit VertexAttributeTypeInfo(f16vec1 const* const ptr);
	explicit VertexAttributeTypeInfo(f16vec2 const* const ptr);
	explicit VertexAttributeTypeInfo(f16vec3 const* const ptr);
	explicit VertexAttributeTypeInfo(f16vec4 const* const ptr);

	explicit VertexAttributeTypeInfo(uint64 const* const ptr);


	/// <summary>
	/// Pointer the vertex attribute buffer on the CPU.
	/// </summary>
	const void* const data;

	/// <summary>
	/// Underlying primtive data type, e.g. GL_FLOAT in case its a float, GL_INT if its an int.
	/// </summary>
	uint32 enumType;

	/// <summary>
	/// Numbe rof components (e.g. 2, if it is a 2D vector).
	/// </summary>
	uint32 numberOfComponents;

	/// <summary>
	/// Size in bytes of an element of the vertex attribute buffer.
	/// </summary>
	uint32 sizeInBytes;

	/// <summary>
	/// Size in bytes per element.
	/// </summary>
	uint32 sizePerElement;

	/// <summary>
	/// True if the data type is normalized. This is important for interger types. In the shader, GLSL will cast them to 0.0 - 1.0.
	/// </summary>
	bool normalized;

	/// <summary>
	/// The internal format.
	/// </summary>
	uint32 sizedInternalFormat;
};
}
}
}
#endif
