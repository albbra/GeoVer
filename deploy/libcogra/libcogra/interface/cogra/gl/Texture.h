/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017-2018 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_TEXTURE_H_
#define COGRA_GL_TEXTURE_H_
#include <cogra/types.h>
#include <cogra/gl/OpenGLRuntimeError.h>
namespace cogra
{
    namespace gl
    {
        class Texture
        {
        protected:
            Texture(GLenum target, GLuint unit);

        public:
            Texture() = delete;

            Texture(const Texture&) = delete;

            Texture& operator=(const Texture&) = delete;

            Texture(Texture&& other);

            Texture& operator=(Texture&& other);

            virtual ~Texture();

            //! Binds the texture to the unit.
            void bind() const;

            //! \return Returns unit at which the texture is bound.
            GLuint getUnit() const;

            //! \brief Sets the texture unit.
            void setUnit(GLuint unit);

            //! \brief Returns the OpenGL texture handle.
            GLuint getTextureHandle() const;

            //! \brief returns the OpenGL target type.
            GLenum getTarget() const;
        private:
            GLenum                              m_target;

            GLuint                              m_textureId;

            GLuint		                        m_unit;
        };
    }
}
#endif
