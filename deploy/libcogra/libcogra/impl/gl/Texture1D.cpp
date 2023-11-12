/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/gl/Texture1D.h>
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

#include "../cograconfig.h"

namespace cogra
{
    namespace gl
    {
        Texture1D::Texture1D()
            : Texture(GL_TEXTURE_1D, 0)
        {
        }
        
        Texture1D::Texture1D(Texture1D && other)
            : Texture(std::move(other))
        {
            m_internalFormat = other.m_internalFormat;
            m_format = other.m_format;
            m_type = other.m_type;

        }

        Texture1D& Texture1D::operator=(Texture1D&& other)
        {
            Texture::operator=(std::move(other));
            m_internalFormat = other.m_internalFormat;
            m_format = other.m_format;
            m_type = other.m_type;
            return *this;
        }
        
        Texture1D::Texture1D(GLuint unit)
            : Texture(GL_TEXTURE_1D, unit)
        { 
        }
        
        Texture1D::Texture1D(GLuint unit, uint32 levels, uint32 width,
                             TextureSizedInternalFormats::Enum sizedInternalFormat, 
                             TextureFormat::Enum format,
                             TextureType::Enum type) 
            : Texture(GL_TEXTURE_1D, unit)
            , m_internalFormat(sizedInternalFormat)
            , m_format(format)
            , m_type(type)
        {
#ifdef COGRA_OPENGL_45
            GL_SAFE_CALL(glTextureStorage1D(getTextureHandle(), 
                                            levels, 
                                            TextureSizedInternalFormats::convert(sizedInternalFormat),
                                            width));
#else
            GL_SAFE_CALL(glBindTexture(getTarget(), getTextureHandle()));
            for(uint32 i = 0; i < levels; i++)
            {
                GL_SAFE_CALL(glTexImage1D(getTarget(), i, TextureSizedInternalFormats::convert(m_internalFormat),
                                          width, 0, TextureFormat::convert(m_format), 
                                          TextureType::convert(m_type), nullptr));
                width = std::max(1u, (width / 2));
            }
#endif
        }

        void Texture1D::setImageData(uint32 level, 
                                     uint32 width, 
                                     void* data)
        {
#ifdef COGRA_OPENGL_45
            GL_SAFE_CALL(glTextureSubImage1D(getTextureHandle(), static_cast<GLint>(level),
                                             0, width,
                                             TextureFormat::convert(m_format),
                                             TextureType::convert(m_type),
                                             data));
#else
            GL_SAFE_CALL(glBindTexture(getTarget(), getTextureHandle()));
			GL_SAFE_CALL(glTexSubImage1D(getTarget(), static_cast<GLint>(level),
										 0, width,
										 TextureFormat::convert(m_format),
										 TextureType::convert(m_type), data));


#endif
        }

        Texture1D Texture1D::loadFromFile(GLuint unit, const std::string& fileName)
        {
            const auto extension = fileName.substr(fileName.find_last_of(".") + 1);
            if(extension == "ktx" || extension == "dds")
            {
                gli::gl gl(gli::gl::PROFILE_GL33);
				
                gli::texture1d tex(gli::load(fileName));

                auto format = gl.translate(tex.format(), tex.swizzles());
                Texture1D result(unit, static_cast<GLint>(tex.levels()), 
                                 tex.extent().x,
                                 TextureSizedInternalFormats::convert(format.Internal),
                                 TextureFormat::convert(format.External),
                                 TextureType::convert(format.Type));

                for(std::size_t level = 0; level < tex.levels(); ++level)
                {
                    result.setImageData(static_cast<GLint>(level), tex.extent(level).x,
                                        tex.data(0, 0, level));
                }
                return result;
            }
            else
            {
                int32 width;
                int32 height;
                int32 nChannels;
                auto data = stbi_load(fileName.c_str(), &width, &height, &nChannels, 0);

                if(data == nullptr)
                {
                    throw cogra::exceptions::RuntimeError("Unable to load texture: " + fileName + ".");
                }

                TextureSizedInternalFormats::Enum internalFormat = TextureSizedInternalFormats::R8;
                TextureFormat::Enum format = TextureFormat::Red;
                switch(nChannels)
                {
                    case 1:
                        internalFormat = TextureSizedInternalFormats::R8;
                        format = TextureFormat::Red;
                        break;
                    case 2:
                        internalFormat = TextureSizedInternalFormats::RG8;
                        format = TextureFormat::RG;
                        break;
                    case 3:
                        internalFormat = TextureSizedInternalFormats::RGB8;
                        format = TextureFormat::RGB;
                        break;
                    case 4:
                        internalFormat = TextureSizedInternalFormats::RGBA8;
                        format = TextureFormat::RGBA;
                        break;
                    default:
                        throw cogra::exceptions::RuntimeError("Unexpected number of channels!");
                        break;
                }
                const auto nLevels = static_cast<uint32>(std::log2(std::max(width, height))) + 1;
                Texture1D result(unit, nLevels, width, internalFormat, format, TextureType::UnsignedByte);
                result.setImageData(0, width, data);
                result.generateMipmap();
                stbi_image_free(data);
                return result;
            }
        }
        
        void Texture1D::generateMipmap()
        {
#ifdef COGRA_OPENGL_45
            GL_SAFE_CALL(glGenerateTextureMipmap(getTextureHandle()));
#else
            GL_SAFE_CALL(glBindTexture(getTarget(), getTextureHandle()));
            GL_SAFE_CALL(glGenerateMipmap(getTarget()));
#endif
        }
    }
}
