/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_TEXTURE2D_H_
#define COGRA_GL_TEXTURE2D_H_
#include <cogra/types.h>
#include <cogra/gl/Texture.h>
#include <cogra/gl/TextureEnums.h>
#include <vector>
#include <string>
namespace cogra
{
namespace gl
{
class Texture2D : public Texture
{
public:
  Texture2D();

  Texture2D(const Texture2D&) = delete;

  Texture2D& operator=(const Texture2D&) = delete;

  Texture2D(Texture2D&& other);

  Texture2D& operator=(Texture2D&& other);

  virtual ~Texture2D() = default;

  explicit Texture2D(GLuint unit);

  Texture2D(GLuint unit, uint32 levels, uint32 width, uint32 height,
            TextureSizedInternalFormats::Enum sizedInternalFormat,
            TextureFormat::Enum format,
            TextureType::Enum type);

  Texture2D(GLuint unit, uint32 levels, uint32 width, uint32 height,
            GLint sizedInternalFormat,
            GLenum format,
            GLenum type);

  Texture2D(GLuint unit, uint32 levels, uint32 width, uint32 height,
            GLint sizedInternalFormat);

  void setImageData(uint32 level, uint32 width, uint32 height, void const* const data);

  template<class T>
  std::vector<T> getImageData(uint32 level) const
  {
    std::vector<T> result(TexelSize::inBytes(TextureType::convert(m_type), TextureFormat::convert(m_format)) * m_width * m_height / sizeof(T));
    bind();
    GL_SAFE_CALL(glGetTexImage(getTarget(), level, m_format, m_type, result.data()));
    return result;
  }

  static Texture2D loadFromFile(GLuint unit, const std::string& fileName);

  void generateMipmap();

  uint32 getWidth() const;

  uint32 getHeight() const;

  void setCompressedImageData(uint32 level, uint32 width, uint32 height, void const * const data, size_t size);

private:

  GLint                               m_internalFormat;
  GLenum                              m_format;
  GLenum                              m_type;

  uint32                              m_width;
  uint32                              m_height;

};
}
}
#endif
