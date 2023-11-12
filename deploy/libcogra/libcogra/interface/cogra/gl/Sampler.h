/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_SAMPLER_H_
#define COGRA_GL_SAMPLER_H_
#include <cogra/types.h>
#include <cogra/gl/TextureEnums.h>
#include <cogra/gl/Texture.h>
namespace cogra
{
    namespace gl
    {
        class Sampler
        {
        public:

            Sampler();

            ~Sampler();

            GLuint getSamplerId() const
            {
                return m_samplerId;
            }

            void bind(const Texture& texture);

            void bind(GLuint textureUnit);

            void getDataFromContext();

            //! \brief
            //! \return
            TextureMagFilter::Enum getMagFilter() const;

            //! \brief
            //! \param magFilter
            void setMagFilter(TextureMagFilter::Enum magFilter);

            //! \brief
            //! \return
            TextureMinFilter::Enum GetMinFilter() const;

            //! \brief
            //! \param minFilter
            void setMinFilter(TextureMinFilter::Enum minFilter);

            //! \brief
            //! \return
            GLfloat getMaxLOD() const;

            //! \brief
            //! \param maxLOD
            void setMaxLOD(GLfloat maxLOD);

            //! \brief
            //! \return
            GLfloat getMinLOD() const;

            //! \brief
            //! \param minLOD
            void setMinLOD(GLfloat minLOD);

            //! \brief
            //! \return
            TextureWrap::Enum getWrapS() const;

            //! \brief
            //! \param wrapS
            void setWrapS(TextureWrap::Enum wrapS);

            //! \brief
            //! \return
            TextureWrap::Enum getWrapT() const;

            //! \brief
            //! \param wrapT
            void setWrapT(TextureWrap::Enum wrapT);

            //! \brief
            //! \return
            TextureWrap::Enum getWrapR() const;

            //! \brief
            //! \param wrapR
            void setWrapR(TextureWrap::Enum wrapR);

            //! \brief
            //! \return
            f32vec4 getTextureBorderColor() const;

            //! \brief
            //! \param textureBorderColor
            void setTextureBorderColor(f32vec4 textureBorderColor);

            //! \brief
            //! \return
            TextureCompareMode::Enum getCompareMode() const;

            //! \brief
            //! \param compareMode
            void setCompareMode(TextureCompareMode::Enum compareMode);

            //! \brief
            //! \return
            TextureCompareFunc::Enum getCompareFunc() const;

            //! \brief
            //! \param compareFunc
            void setCompareFunc(TextureCompareFunc::Enum compareFunc);

            //!\ brief Returns the texture unit.
            GLuint getUnit() const
            {
                return m_textureUnit;
            }

        private:
            GLuint                          m_samplerId;
            TextureMagFilter::Enum          m_magFilter;
            TextureMinFilter::Enum          m_minFilter;
            GLfloat                         m_minLOD;
            GLfloat                         m_maxLOD;

            TextureWrap::Enum               m_wrapS;
            TextureWrap::Enum               m_wrapR;
            TextureWrap::Enum               m_wrapT;
            f32vec4                       m_textureBorderColor;
            TextureCompareMode::Enum        m_compareMode;
            TextureCompareFunc::Enum        m_compareFunc;

            GLuint                          m_textureUnit;
        };
    }
}
#endif
