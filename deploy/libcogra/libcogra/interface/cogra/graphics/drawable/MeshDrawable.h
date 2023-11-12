/// Cogra --- Coburg Graphics Framework 2018
/// (C) 2017-2018 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GRAPHICS_DRAWABLE_MESHDRAWABLE_H_
#define COGRA_GRAPHICS_DRAWABLE_MESHDRAWABLE_H_
#include <cogra/types.h>
#include <cogra/graphics/drawable/Drawable.h>
#include <glad/glad.h>
#include <vector>
#include <cogra/gl/OpenGLRuntimeError.h>
#include <cogra/graphics/drawable/VertexAttributeTypeInfo.h>
namespace cogra
{
namespace graphics
{
namespace drawable
{
class MeshDrawable : public Drawable
{
public:
	/// <summary>
	/// The underlying primitve type. See https://www.khronos.org/opengl/wiki/Primitive for details.
	/// </summary>
	enum PrimitiveType
	{
		Points = 0,
		LineStrip,
		LineLoop,
		Lines,
		LineStripAdjacency,
		LinesAdjacency,
		TriangleStrip,
		TriangleFan,
		Triangles,
		TriangleStripAdjacency,
		TrianglesAdjacency,
		Patches
	};

	/// <summary>
	/// Create an empty mesh. Nothing happens if you draw that.
	/// </summary>
	MeshDrawable();

	/// <summary>
	/// Create a mesh drawable from an index buffer and a number of vertex attributes passed vertexAttributeInfo.
	/// </summary>
	/// <param name="indexBuffer">Pointer to the index buffer describing the topology.</param>
	/// <param name="nIndices">Number of indidces in the index buffer.</param>
	/// <param name="primtiveType">What type of primitive shall be used when rendering.</param>
	/// <param name="nVertices">Number of vertices in each vertex buffer.</param>
	/// <param name="vertexAttributeInfo">Array </param>
	MeshDrawable(const uint32* const indexBuffer, size_t nIndices,
		PrimitiveType primtiveType,
		size_t nVertices,
		const std::vector<VertexAttributeTypeInfo>& vertexAttributeInfo);


	/// <summary>
	/// Create a mesh with an index buffer and variadic number of vertex buffers.
	/// 
	/// You have to specify an indexBuffer and its number of indices, the primtive type and the number of vertices. Next you can pass a variadic number of vertex buffers.
	/// 
	/// <param name="indexBuffer">Pointer to the index buffer describing the topology.</param>
	/// <param name="nIndices">Number of indidces in the index buffer.</param>
	/// <param name="primtiveType">What type of primitive shall be used when rendering.</param>
	/// <param name="nVertices">Number of vertices in each vertex buffer.</param>
	/// </summary>
	template<class... Targs>
	MeshDrawable(
		const uint32* const indexBuffer, size_t nIndices,
		PrimitiveType primtiveType,
		size_t nVertices,
		const Targs&... args)
		: m_vertexArrayObjectID(0)
		, m_bufferIDs(0)
		, m_elementArrayBufferCount(nIndices)
		, m_numVertices(nVertices)
		, m_primitiveType(convertToGLenum(primtiveType))
	{
		MeshDrawable_impl(indexBuffer, nIndices, nVertices, false, VertexAttributeTypeInfo(args)...);
	}

	/// <summary>
	/// Create a mesh with an index buffer and variadic number of vertex buffers.
	/// 
	/// You have to specify an indexBuffer and its number of indices, the primtive type and the number of vertices. Next you can pass a variadic number of vertex buffers.
	/// 
	/// <param name="indexBuffer">Pointer to the index buffer describing the topology.</param>
	/// <param name="nIndices">Number of indidces in the index buffer.</param>
	/// <param name="primtiveType">What type of primitive shall be used when rendering.</param>
	/// <param name="nVertices">Number of vertices in each vertex buffer.</param>
	/// </summary>
	template<class... Targs>
	MeshDrawable(
		const uint32* const indexBuffer, size_t nIndices,
		PrimitiveType primtiveType,
		size_t nVertices,
		bool interleaved,
		const Targs&... args)
		: m_vertexArrayObjectID(0)
		, m_bufferIDs(0)
		, m_elementArrayBufferCount(nIndices)
		, m_numVertices(nVertices)
		, m_primitiveType(convertToGLenum(primtiveType))
	{
		MeshDrawable_impl(indexBuffer, nIndices, nVertices, interleaved, VertexAttributeTypeInfo(args)...);
	}


	/// <summary>
	/// Create a mesh with avariadic number of vertex buffers (but without index buffer).
	/// 
	/// You have to specify the primtive type and the number of vertices. Next you can pass a variadic number of vertex buffers.
	/// 
	/// <param name="indexBuffer">Pointer to the index buffer describing the topology.</param>
	/// <param name="nIndices">Number of indidces in the index buffer.</param>
	/// <param name="primtiveType">What type of primitive shall be used when rendering.</param>
	/// <param name="nVertices">Number of vertices in each vertex buffer.</param>
	/// </summary>
	template<class... Targs>
	MeshDrawable(
		PrimitiveType primtiveType,
		size_t nVertices,
		const Targs&... args)
		: m_vertexArrayObjectID(0)
		, m_bufferIDs(0)
		, m_elementArrayBufferCount(0)
		, m_numVertices(nVertices)
		, m_primitiveType(convertToGLenum(primtiveType))
	{
		MeshDrawable_impl(nullptr, 0, nVertices, false, VertexAttributeTypeInfo(args)...);
	}

	virtual ~MeshDrawable();

	//! \brief The number of buffers. This number includes the vertex position buffers, all attribute buffers and the
	//! element array buffer (sometimes called index buffer).
	size_t getNumberOfBuffers() const;

	/// <summary>
	/// Draws the mesh.
	/// </summary>
	void draw() const override;

	/// <summary>
	/// Draws count vertices (no index buffer)/primitive (index buffer) starting from the first vertex/primitive.
	/// </summary>
	/// <param name="first">First vertex or primitive to draw.</param>
	/// <param name="count">Number of vertices or primitves to draw. </param>
	void draw(size_t first, size_t count) const;

	//! \brief Returns the number of primitives.
	size_t getNumPrimitives() const;

	//! \brief Returns the number of vertices.
	size_t getNumVertices() const;

	//! Disallow copy constructor.
	MeshDrawable(const MeshDrawable&) = delete;

	//! Disallow assignment operator.
	MeshDrawable& operator=(const MeshDrawable&) = delete;

	//! Use the default move-copy constructor.
	MeshDrawable(MeshDrawable&& other);

	//! Use the default move-copy assignment operator.
	MeshDrawable& operator=(MeshDrawable&& other);

	//! Sets the primitive type.
	void setPrimitiveType(PrimitiveType primitiveType);

	//! Returns the primtive type.
	PrimitiveType  getPrimitiveType() const;

	//! In case the primitive type is a patch, you can set the number of vertices for that patch.
	void setPatchVertices(int32 nPatchVertices)
	{
		m_nPatchVertices = nPatchVertices;
	}

	//! Replaces attribute buffer at attribute Index aIdx.
	//! 
	//! aIdx is counted as in the constructor 
	//!   template<class... Targs> MeshDrawable(const uint32* const indexBuffer, size_t nIndices, PrimitiveType primtiveType, size_t nVertices, const Targs&... args)
	//! and correspond to the index of variadic argument list const Targs&... args.
	void replaceBuffer(uint32 aIdx, const VertexAttributeTypeInfo& attributeInfo);

	bool hasBuffer(uint32 aIdx);
private:
	//! OpenGL handle to vertex array object.
	GLuint                m_vertexArrayObjectID;

	//! OpenGL handles to element array buffers and vertex buffers.
	std::vector<GLuint>   m_bufferIDs;

	//! Number of elements in the element array buffer.
	size_t                m_elementArrayBufferCount;

	//! Number of vertices
	size_t                m_numVertices;

	//! Primitive type that is to be rendered.
	GLenum                m_primitiveType;

	//! In case the primitive type is a patch
	int32                 m_nPatchVertices;



	template<class... Targs>
	void MeshDrawable_impl(
		const uint32* const indexBuffer, size_t nIndices, size_t nVertices, bool interleaved,
		const Targs&... args)
	{
		std::vector<VertexAttributeTypeInfo> vertexAttributeInfo = { args... };
		MeshDrawable_impl(indexBuffer, nIndices, nVertices, interleaved, vertexAttributeInfo);
	}

	void MeshDrawable_impl(const uint32* const indexBuffer, size_t nIndices, size_t nVertices, bool interleaved, const std::vector<VertexAttributeTypeInfo>& vertexAttributeInfo);

	static GLenum convertToGLenum(PrimitiveType p);

	static PrimitiveType convertFromGLenum(GLenum p);
};
}
}
}
#endif
