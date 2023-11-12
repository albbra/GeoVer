#pragma once
#include <cogra/types.h>
#include <cogra/gl/Texture.h>
#include <cogra/gl/OpenGLRuntimeError.h>
#include <cogra/gl/TextureEnums.h>
#include <vector>
#include <cogra/graphics/drawable/VertexAttributeTypeInfo.h>

namespace cogra
{
namespace gl
{
class TextureBuffer : public Texture
{
public:
  TextureBuffer();
  
  TextureBuffer(TextureSizedInternalFormats::Enum format, void const* const data, uint32 size);
  
  template<class  T>
  TextureBuffer(const std::vector<T>& inputData)
    : Texture(GL_TEXTURE_BUFFER, 0)
  {
    cogra::graphics::drawable::VertexAttributeTypeInfo vati(inputData.data());
    GL_SAFE_CALL(glGenBuffers(1, &m_bufferId));
    setData(TextureSizedInternalFormats::convert(vati.sizedInternalFormat), 
            reinterpret_cast<void const * const>(inputData.data()), uint32(inputData.size() * vati.sizeInBytes));
  }

  virtual ~TextureBuffer();

  TextureBuffer(TextureBuffer&& other);
  TextureBuffer& operator=(TextureBuffer&& other);

  void setData(TextureSizedInternalFormats::Enum format, void const * const data, uint32 size);
private:
  void bindBuffer();
  void unbindBuffer();
  GLuint m_bufferId;
};
}
}

