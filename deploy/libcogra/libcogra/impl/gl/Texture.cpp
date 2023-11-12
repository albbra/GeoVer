/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017-2018 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/gl/Texture.h>
#include <cogra/gl/OpenGLRuntimeError.h>

#include "../cograconfig.h"

namespace cogra
{
    namespace gl
    {
        Texture::Texture(const GLenum target, const GLuint unit) 
            : m_target(target)
            , m_textureId(0)
            , m_unit(unit)
        {
#ifdef COGRA_OPENGL_45
            GL_SAFE_CALL(glCreateTextures(target, 1, &m_textureId));
#else
            GL_SAFE_CALL(glGenTextures(1, &m_textureId));
#endif
        }

        Texture::Texture(Texture&& other)            
        {
            m_textureId = other.m_textureId;
            m_target = other.m_target;
            m_unit = other.m_unit;
            other.m_textureId = 0;
        }

        Texture& Texture::operator=(Texture&& other)
        {
            m_textureId = other.m_textureId;
            m_target = other.m_target;
            m_unit = other.m_unit;
            other.m_textureId = 0;
            return *this;
        }

        Texture::~Texture()
        {
            if(m_textureId != 0)
            {
                GL_SAFE_CALL_NO_THROW(glDeleteTextures(1, &m_textureId));
			}
		}

        void Texture::bind() const
        {
#ifdef COGRA_OPENGL_45
            GL_SAFE_CALL(glBindTextureUnit(m_unit, getTextureHandle()));
#else
            GL_SAFE_CALL(glActiveTexture(GL_TEXTURE0 + m_unit));
            GL_SAFE_CALL(glBindTexture(getTarget(), getTextureHandle()));
#endif
        }

        GLuint Texture::getUnit() const
        {
            return m_unit;
        }

        void Texture::setUnit(GLuint unit)
        {
            m_unit = unit;
        }

        GLuint Texture::getTextureHandle() const
        {
            return m_textureId;
        }

        GLenum Texture::getTarget() const
        {
            return m_target;
        }


    }
}
