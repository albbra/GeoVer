#include <cogra/gl/TextureBuffer.h>

namespace cogra
{
namespace gl
{
TextureBuffer::TextureBuffer()
  : Texture(GL_TEXTURE_BUFFER, 0)
{
  GL_SAFE_CALL(glGenBuffers(1, &m_bufferId));
}

TextureBuffer::TextureBuffer(TextureSizedInternalFormats::Enum format, void const * const data, uint32 size)
  : Texture(GL_TEXTURE_BUFFER, 0)
{
  // create buffer
  GL_SAFE_CALL(glGenBuffers(1, &m_bufferId));
  setData(format, data, size);
}

TextureBuffer::~TextureBuffer()
{
  if(m_bufferId != 0)
  {
    GL_SAFE_CALL_NO_THROW(glDeleteBuffers(1, &m_bufferId));
  }
}

TextureBuffer::TextureBuffer(TextureBuffer&& other)
  : Texture(std::move(other))
{
  m_bufferId = other.m_bufferId;
  other.m_bufferId = 0;
}

TextureBuffer& TextureBuffer::operator=(TextureBuffer&& other)
{
  Texture::operator=(std::move(other));
  m_bufferId = other.m_bufferId;
  other.m_bufferId = 0;
  return *this;
}

void TextureBuffer::setData(TextureSizedInternalFormats::Enum format, void const * const data, uint32 size)
{
  bindBuffer();
  GL_SAFE_CALL(glBufferData(GL_TEXTURE_BUFFER, size, data, GL_STATIC_DRAW));
  unbindBuffer();
  bind();
  GL_SAFE_CALL(glTexBuffer(GL_TEXTURE_BUFFER, TextureSizedInternalFormats::convert(format), m_bufferId));
}

void TextureBuffer::bindBuffer()
{
  GL_SAFE_CALL(glBindBuffer(GL_TEXTURE_BUFFER, m_bufferId));
}

void TextureBuffer::unbindBuffer()
{
  GL_SAFE_CALL(glBindBuffer(GL_TEXTURE_BUFFER, 0));
}
}
}
