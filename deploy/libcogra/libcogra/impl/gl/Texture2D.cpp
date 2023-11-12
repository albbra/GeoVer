/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/gl/Texture2D.h>
#include <cogra/gl/OpenGLRuntimeError.h>
#include <cogra/types.h>
#pragma warning (push)
#pragma warning( disable: 4100)
#pragma warning( disable: 4458)
#include <gli/gli.hpp>
#pragma warning (pop)
#include <utility>
#include <vector>
#include <stb/stb_image.h>
#include <cogra/tools/NormalizeFilename.h>

#include "../cograconfig.h"

namespace
{
GLenum sizeInternalFormat_to_Format(GLenum sizeInternalFormat)
{
  switch(sizeInternalFormat)
  {
    case GL_R8_SNORM: return GL_RED;
    case GL_R8: return GL_RED;
    case GL_R16: return GL_RED;
    case GL_R16_SNORM: return GL_RED;
    case GL_RG8: return GL_RG;
    case GL_RG8_SNORM: return GL_RG;
    case GL_RG16: return GL_RG;
    case GL_RG16_SNORM: return GL_RG;
    case GL_R3_G3_B2: return GL_RGB;
    case GL_RGB4: return GL_RGB;
    case GL_RGB5: return GL_RGB;
    case GL_RGB8: return GL_RGB;
    case GL_RGB8_SNORM: return GL_RGB;
    case GL_RGB10: return GL_RGB;
    case GL_RGB12: return GL_RGB;
    case GL_RGB16_SNORM: return GL_RGB;
    case GL_RGBA2: return GL_RGB;
    case GL_RGBA4: return GL_RGB;
    case GL_RGB5_A1: return GL_RGBA;
    case GL_RGBA8: return GL_RGBA;
    case GL_RGBA8_SNORM: return GL_RGBA;
    case GL_RGB10_A2: return GL_RGBA;
    case GL_RGB10_A2UI: return GL_RGBA;
    case GL_RGBA12: return GL_RGBA;
    case GL_RGBA16: return GL_RGBA;
    case GL_SRGB8: return GL_RGB;
    case GL_SRGB8_ALPHA8: return GL_RGBA;
    case GL_R16F: return GL_RED;
    case GL_RG16F: return GL_RG;
    case GL_RGB16F: return GL_RGB;
    case GL_RGBA16F: return GL_RGBA;
    case GL_R32F: return GL_RED;
    case GL_RG32F: return GL_RG;
    case GL_RGB32F: return GL_RGB;
    case GL_RGBA32F: return GL_RGBA;
    case GL_R11F_G11F_B10F: return GL_RGB;
    case GL_RGB9_E5: return GL_RGB;
    case GL_R8I: return GL_RED;
    case GL_R8UI: return GL_RED;
    case GL_R16I: return GL_RED;
    case GL_R16UI: return GL_RED;
    case GL_R32I: return GL_RED;
    case GL_R32UI: return GL_RED;
    case GL_RG8I: return GL_RG;
    case GL_RG8UI: return GL_RG;
    case GL_RG16I: return GL_RG;
    case GL_RG16UI: return GL_RG;
    case GL_RG32I: return GL_RG;
    case GL_RG32UI: return GL_RG;
    case GL_RGB8I: return GL_RGB;
    case GL_RGB8UI: return GL_RGB;
    case GL_RGB16I: return GL_RGB;
    case GL_RGB16UI: return GL_RGB;
    case GL_RGB32I: return GL_RGB;
    case GL_RGB32UI: return GL_RGB;
    case GL_RGBA8I: return GL_RGBA;
    case GL_RGBA8UI: return GL_RGBA;
    case GL_RGBA16I: return GL_RGBA;
    case GL_RGBA16UI: return GL_RGBA;
    case GL_RGBA32I: return GL_RGBA;
    case GL_RGBA32UI: return GL_RGBA;
    default:
      return GL_NONE;
  }
}

GLenum sizeInternalFormat_to_Type(GLenum sizeInternalFormat)
{
  switch(sizeInternalFormat)
  {
    case GL_R8_SNORM:       return GL_BYTE;
    case GL_R8:             return GL_UNSIGNED_BYTE;
    case GL_R16:            return GL_UNSIGNED_SHORT;
    case GL_R16_SNORM:      return GL_SHORT;
    case GL_RG8:            return GL_UNSIGNED_BYTE;
    case GL_RG8_SNORM:      return GL_BYTE;
    case GL_RG16:           return GL_UNSIGNED_SHORT;
    case GL_RG16_SNORM:     return GL_SHORT;
    case GL_R3_G3_B2:       return GL_NONE;
    case GL_RGB4:           return GL_NONE;
    case GL_RGB5:           return GL_NONE;
    case GL_RGB8:           return GL_UNSIGNED_BYTE;
    case GL_RGB8_SNORM:     return GL_BYTE;
    case GL_RGB10:          return GL_NONE;
    case GL_RGB12:          return GL_NONE;
    case GL_RGB16_SNORM:    return GL_SHORT;
    case GL_RGBA2:          return GL_NONE;
    case GL_RGBA4:          return GL_NONE;
    case GL_RGB5_A1:        return GL_NONE;
    case GL_RGBA8:          return GL_UNSIGNED_BYTE;
    case GL_RGBA8_SNORM:    return GL_BYTE;
    case GL_RGB10_A2:       return GL_NONE;
    case GL_RGB10_A2UI:     return GL_NONE;
    case GL_RGBA12:         return GL_NONE;
    case GL_RGBA16:         return GL_UNSIGNED_SHORT;
    case GL_SRGB8:          return GL_BYTE;
    case GL_SRGB8_ALPHA8:   return GL_BYTE;
    case GL_R16F:           return GL_FLOAT;
    case GL_RG16F:          return GL_FLOAT;
    case GL_RGB16F:         return GL_FLOAT;
    case GL_RGBA16F:        return GL_FLOAT;
    case GL_R32F:           return GL_FLOAT;
    case GL_RG32F:          return GL_FLOAT;
    case GL_RGB32F:         return GL_FLOAT;
    case GL_RGBA32F:        return GL_FLOAT;
    case GL_R11F_G11F_B10F: return GL_FLOAT;
    case GL_RGB9_E5:        return GL_NONE;
    case GL_R8I:            return GL_BYTE;
    case GL_R8UI:           return GL_UNSIGNED_BYTE;
    case GL_R16I:           return GL_SHORT;
    case GL_R16UI:          return GL_UNSIGNED_SHORT;
    case GL_R32I:           return GL_INT;
    case GL_R32UI:          return GL_UNSIGNED_INT;
    case GL_RG8I:           return GL_BYTE;
    case GL_RG8UI:          return GL_UNSIGNED_BYTE;
    case GL_RG16I:          return GL_SHORT;
    case GL_RG16UI:         return GL_UNSIGNED_SHORT;
    case GL_RG32I:          return GL_INT;
    case GL_RG32UI:         return GL_UNSIGNED_INT;
    case GL_RGB8I:          return GL_BYTE;
    case GL_RGB8UI:         return GL_UNSIGNED_BYTE;
    case GL_RGB16I:         return GL_SHORT;
    case GL_RGB16UI:        return GL_UNSIGNED_SHORT;
    case GL_RGB32I:         return GL_INT;
    case GL_RGB32UI:        return GL_UNSIGNED_INT;
    case GL_RGBA8I:         return GL_BYTE;
    case GL_RGBA8UI:        return GL_UNSIGNED_BYTE;
    case GL_RGBA16I:        return GL_SHORT;
    case GL_RGBA16UI:       return GL_UNSIGNED_SHORT;
    case GL_RGBA32I:        return GL_INT;
    case GL_RGBA32UI:       return GL_UNSIGNED_INT;
    default:
      return GL_NONE;
  }
}

}


namespace cogra
{
namespace gl
{
Texture2D::Texture2D()
  : Texture(GL_TEXTURE_2D, 0)
  , m_width(0)
  , m_height(0)
{ }

Texture2D::Texture2D(Texture2D && other)
  : Texture(std::move(other))
{
  m_internalFormat = other.m_internalFormat;
  m_format = other.m_format;
  m_type = other.m_type;
  m_width = other.m_width;
  m_height = other.m_height;

}

Texture2D& Texture2D::operator=(Texture2D&& other)
{
  Texture::operator=(std::move(other));
  m_internalFormat = other.m_internalFormat;
  m_format = other.m_format;
  m_type = other.m_type;
  m_width = other.m_width;
  m_height = other.m_height;
  return *this;
}

Texture2D::Texture2D(GLuint unit)
  : Texture(GL_TEXTURE_2D, unit)
  , m_width(0)
  , m_height(0)
{ }

Texture2D::Texture2D(GLuint unit, uint32 levels, uint32 width, uint32 height,
                     TextureSizedInternalFormats::Enum sizedInternalFormat,
                     TextureFormat::Enum format,
                     TextureType::Enum type)
  : Texture(GL_TEXTURE_2D, unit)
  , m_internalFormat(TextureSizedInternalFormats::convert(sizedInternalFormat))
  , m_format(TextureFormat::convert(format))
  , m_type(TextureType::convert(type))
  , m_width(width)
  , m_height(height)
{
#ifdef COGRA_OPENGL_45
  GL_SAFE_CALL(glTextureStorage2D(getTextureHandle(),
                                  levels,
                                  sizedInternalFormat,
                                  width, height));
#else
  bind();
  GL_SAFE_CALL(glTexParameteri(getTarget(), GL_TEXTURE_BASE_LEVEL, 0));
  GL_SAFE_CALL(glTexParameteri(getTarget(), GL_TEXTURE_MAX_LEVEL, levels - 1));
  GL_SAFE_CALL(glTexStorage2D(getTarget(), levels, m_internalFormat, width, height));
#endif
}

Texture2D::Texture2D(GLuint unit, uint32 levels, uint32 width, uint32 height,
                     GLint sizedInternalFormat,
                     GLenum format,
                     GLenum type)
  : Texture(GL_TEXTURE_2D, unit)
  , m_internalFormat(sizedInternalFormat)
  , m_format(format)
  , m_type(type)
  , m_width(width)
  , m_height(height)
{
#ifdef COGRA_OPENGL_45
  GL_SAFE_CALL(glTextureStorage2D(getTextureHandle(),
                                  levels,
                                  sizedInternalFormat,
                                  width, height));
#else
  bind();
  GL_SAFE_CALL(glTexParameteri(getTarget(), GL_TEXTURE_BASE_LEVEL, 0));
  GL_SAFE_CALL(glTexParameteri(getTarget(), GL_TEXTURE_MAX_LEVEL, levels - 1));
  GL_SAFE_CALL(glTexStorage2D(getTarget(), levels, m_internalFormat, width, height));
#endif
}

Texture2D::Texture2D(GLuint unit, uint32 levels, uint32 width, uint32 height, GLint sizedInternalFormat)
  : Texture(GL_TEXTURE_2D, unit)
  , m_internalFormat(sizedInternalFormat)
  , m_format(sizeInternalFormat_to_Format(sizedInternalFormat))
  , m_type(sizeInternalFormat_to_Type(sizedInternalFormat))
  , m_width(width)
  , m_height(height)
{
  bind();
  GL_SAFE_CALL(glTexParameteri(getTarget(), GL_TEXTURE_BASE_LEVEL, 0));
  GL_SAFE_CALL(glTexParameteri(getTarget(), GL_TEXTURE_MAX_LEVEL, levels - 1));
  GL_SAFE_CALL(glTexStorage2D(getTarget(), levels, m_internalFormat, width, height));
}


void Texture2D::setImageData(uint32 level,
                             uint32 width, uint32 height,
                             void const* const data)

{
#ifdef COGRA_OPENGL_45
  GL_SAFE_CALL(glTextureSubImage2D(getTextureHandle(), static_cast<GLint>(level),
                                   0, 0, width, height,
                                   m_format,
                                   m_type,
                                   data));
#else
  bind();
  GL_SAFE_CALL(glTexSubImage2D(getTarget(), static_cast<GLint>(level), 0, 0, width, height, m_format, m_type, data));
#endif
}

Texture2D Texture2D::loadFromFile(GLuint unit, const std::string& fileName)
{
  auto extension = fileName.substr(fileName.find_last_of(".") + 1);
  std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
  if(extension == "ktx" || extension == "dds")
  {
    gli::gl gl(gli::gl::PROFILE_GL33);
    gli::texture2d tex(gli::load(fileName));

    auto format = gl.translate(tex.format(), tex.swizzles());

    

    Texture2D result(unit, static_cast<GLint>(tex.levels()),
                     tex.extent().x, tex.extent().y,
                     format.Internal,
                     format.External,    
                     format.Type);
    if(!gli::is_compressed(tex.format()))
    {
      for(std::size_t level = 0; level < tex.levels(); ++level)
      {
        result.setImageData(static_cast<GLint>(level), tex.extent(level).x, tex.extent(level).y,
                            tex.data(0, 0, level));
        
      }
    }
    else
    {
      for(std::size_t level = 0; level < tex.levels(); ++level)
      {
        result.setCompressedImageData(static_cast<GLint>(level), tex.extent(level).x, tex.extent(level).y,
                                      tex.data(0, 0, level), static_cast<GLsizei>(tex.size(level)));

      }
    }    
    return result;
  }
  else
  {
    int32 width;
    int32 height;
    int32 nChannels;
    stbi_set_flip_vertically_on_load(1);
    auto data = stbi_load(fileName.c_str(), &width, &height, &nChannels, 0);

    if(data == nullptr)
    {
      throw cogra::exceptions::RuntimeError("Unable to load texture: " + fileName + ".");
    }

    auto internalFormat = TextureSizedInternalFormats::convert(TextureSizedInternalFormats::R8);
    auto format = TextureFormat::convert(TextureFormat::Red);
    switch(nChannels)
    {
      case 1:
        internalFormat = TextureSizedInternalFormats::convert(TextureSizedInternalFormats::R8);
        format = TextureFormat::convert(TextureFormat::Red);
        break;
      case 2:
        internalFormat = TextureSizedInternalFormats::convert(TextureSizedInternalFormats::RG8);
        format = TextureFormat::convert(TextureFormat::RG);
        break;
      case 3:
        internalFormat = TextureSizedInternalFormats::convert(TextureSizedInternalFormats::RGB8);
        format = TextureFormat::convert(TextureFormat::RGB);
        break;
      case 4:
        internalFormat = TextureSizedInternalFormats::convert(TextureSizedInternalFormats::RGBA8);
        format = TextureFormat::convert(TextureFormat::RGBA);
        break;
      default:
        throw cogra::exceptions::RuntimeError("Unexpected number of channels!");
        break;
    }
    const auto nLevels = static_cast<uint32>(std::log2(std::max(width, height))) + 1;
    Texture2D result(unit, nLevels, width, height, internalFormat, format, TextureType::convert(TextureType::UnsignedByte));
    result.setImageData(0, width, height, data);
    result.generateMipmap();
    stbi_image_free(data);
    return result;
  }
}

void Texture2D::generateMipmap()
{
#ifdef COGRA_OPENGL_45
  GL_SAFE_CALL(glGenerateTextureMipmap(getTextureHandle()));
#else
  GL_SAFE_CALL(glBindTexture(getTarget(), getTextureHandle()));
  GL_SAFE_CALL(glGenerateMipmap(getTarget()));
#endif
}

uint32 Texture2D::getWidth() const
{
  return m_width;
}

uint32 Texture2D::getHeight() const
{
  return m_height;
}

void Texture2D::setCompressedImageData(uint32 level, uint32 width, uint32 height, void const * const data, size_t size)
{  
  bind();
  GL_SAFE_CALL(glCompressedTexSubImage2D(getTarget(), level, 0, 0, width, height, m_internalFormat, static_cast<GLsizei>(size), data));
}
}
}
