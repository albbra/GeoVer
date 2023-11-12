/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/gl/Sampler.h>
#include <cogra/gl/OpenGLRuntimeError.h>

#include "../cograconfig.h"


namespace cogra
{
    namespace gl
    {
        Sampler::Sampler() : m_samplerId(0)
            , m_magFilter(TextureMagFilter::Linear)
            , m_minFilter(TextureMinFilter::NearestMipMapLinear)
            , m_minLOD(-1000)
            , m_maxLOD(1000)
            , m_wrapS(TextureWrap::Repeat)
            , m_wrapR(TextureWrap::Repeat)
            , m_wrapT(TextureWrap::Repeat)
            , m_textureBorderColor(f32vec4(0, 0, 0, 0))
            , m_compareMode(TextureCompareMode::None)
            , m_compareFunc(TextureCompareFunc::LessEqual)
            , m_textureUnit(0)
        {
#ifdef COGRA_OPENGL_45
            GL_SAFE_CALL(glCreateSamplers(1, &m_samplerId));
#else
            GL_SAFE_CALL(glGenSamplers(1, &m_samplerId));
#endif
        }

        Sampler::~Sampler()
        {
            if(m_samplerId != 0)
            {
                GL_SAFE_CALL_NO_THROW(glDeleteSamplers(1, &m_samplerId));
            }
        }

        void Sampler::bind(const Texture& texture)
        {
            bind(texture.getUnit());            
        }

        void Sampler::bind(GLuint textureUnit)
        {
            m_textureUnit = textureUnit;
            GL_SAFE_CALL(glBindSampler(textureUnit, m_samplerId));
        }

        void Sampler::getDataFromContext()
        {
            GLint         magFilter;
            GLint         minFilter;
            GLint         wrapS;
            GLint         wrapT;
            GLint         wrapR;
            GLint         compareMode;
            GLint         compareFunc;

            GL_SAFE_CALL(glGetSamplerParameteriv(m_samplerId, GL_TEXTURE_MAG_FILTER, &magFilter));
            m_magFilter = TextureMagFilter::convert(magFilter);

            GL_SAFE_CALL(glGetSamplerParameteriv(m_samplerId, GL_TEXTURE_MIN_FILTER, &minFilter));
            m_minFilter = TextureMinFilter::convert(minFilter);

            GL_SAFE_CALL(glGetSamplerParameterfv(m_samplerId, GL_TEXTURE_MIN_LOD, &m_minLOD));

            GL_SAFE_CALL(glGetSamplerParameterfv(m_samplerId, GL_TEXTURE_MAX_LOD, &m_maxLOD));

            GL_SAFE_CALL(glGetSamplerParameteriv(m_samplerId, GL_TEXTURE_WRAP_S, &wrapS));
            m_wrapS = TextureWrap::convert(wrapS);

            GL_SAFE_CALL(glGetSamplerParameteriv(m_samplerId, GL_TEXTURE_WRAP_T, &wrapT));
            m_wrapT = TextureWrap::convert(wrapT);

            GL_SAFE_CALL(glGetSamplerParameteriv(m_samplerId, GL_TEXTURE_WRAP_R, &wrapR));
            m_wrapR = TextureWrap::convert(wrapR);

            GL_SAFE_CALL(glGetSamplerParameterfv(m_samplerId, GL_TEXTURE_BORDER_COLOR, &m_textureBorderColor.x));

            GL_SAFE_CALL(glGetSamplerParameteriv(m_samplerId, GL_TEXTURE_COMPARE_MODE, &compareMode));
            m_compareMode = TextureCompareMode::convert(compareMode);

            GL_SAFE_CALL(glGetSamplerParameteriv(m_samplerId, GL_TEXTURE_COMPARE_FUNC, &compareFunc));
            m_compareFunc = TextureCompareFunc::convert(compareFunc);
        }

        TextureMagFilter::Enum Sampler::getMagFilter() const
        {
            return m_magFilter;
        }

        void Sampler::setMagFilter(TextureMagFilter::Enum magFilter)
        {
            m_magFilter = magFilter;
            GL_SAFE_CALL(glSamplerParameteri(m_samplerId, GL_TEXTURE_MAG_FILTER, TextureMagFilter::convert(magFilter)));
        }

        TextureMinFilter::Enum Sampler::GetMinFilter() const
        {
            return m_minFilter;
        }

        void Sampler::setMinFilter(TextureMinFilter::Enum minFilter)
        {
            m_minFilter = minFilter;
            GL_SAFE_CALL(glSamplerParameteri(m_samplerId, GL_TEXTURE_MIN_FILTER, TextureMinFilter::convert(minFilter)));
        }

        GLfloat Sampler::getMaxLOD() const
        {
            return m_maxLOD;
        }

        void Sampler::setMaxLOD(GLfloat maxLOD)
        {
            m_maxLOD = maxLOD;
            GL_SAFE_CALL(glSamplerParameterf(m_samplerId, GL_TEXTURE_MAX_LOD, maxLOD));
        }

        GLfloat Sampler::getMinLOD() const
        {
            return m_minLOD;
        }

        void Sampler::setMinLOD(GLfloat minLOD)
        {
            m_minLOD = minLOD;
            GL_SAFE_CALL(glSamplerParameterf(m_samplerId, GL_TEXTURE_MIN_LOD, minLOD));
        }

        TextureWrap::Enum Sampler::getWrapS() const
        {
            return m_wrapS;
        }

        void Sampler::setWrapS(TextureWrap::Enum wrapS)
        {
            m_wrapS = wrapS;
            GL_SAFE_CALL(glSamplerParameteri(m_samplerId, GL_TEXTURE_WRAP_S, TextureWrap::convert(wrapS)));
        }

        TextureWrap::Enum Sampler::getWrapT() const
        {
            return m_wrapT;
        }

        void Sampler::setWrapT(TextureWrap::Enum wrapT)
        {
            m_wrapT = wrapT;
            GL_SAFE_CALL(glSamplerParameteri(m_samplerId, GL_TEXTURE_WRAP_T, TextureWrap::convert(wrapT)));
        }

        TextureWrap::Enum Sampler::getWrapR() const
        {
            return m_wrapR;
        }

        void Sampler::setWrapR(TextureWrap::Enum wrapR)
        {
            m_wrapR = wrapR;
            GL_SAFE_CALL(glSamplerParameteri(m_samplerId, GL_TEXTURE_WRAP_R, TextureWrap::convert(wrapR)));
        }

        f32vec4 Sampler::getTextureBorderColor() const
        {
            return m_textureBorderColor;
        }

        void Sampler::setTextureBorderColor(f32vec4 textureBorderColor)
        {
            m_textureBorderColor = textureBorderColor;
            GL_SAFE_CALL(glSamplerParameterfv(m_samplerId, GL_TEXTURE_BORDER_COLOR, &textureBorderColor.x));
        }

        TextureCompareMode::Enum Sampler::getCompareMode() const
        {
            return m_compareMode;
        }

        void Sampler::setCompareMode(TextureCompareMode::Enum compareMode)
        {
            m_compareMode = compareMode;
            GL_SAFE_CALL(glSamplerParameteri(m_samplerId, GL_TEXTURE_COMPARE_MODE, TextureCompareMode::convert(compareMode)));
        }

        TextureCompareFunc::Enum Sampler::getCompareFunc() const
        {
            return m_compareFunc;
        }

        void Sampler::setCompareFunc(TextureCompareFunc::Enum compareFunc)
        {
            m_compareFunc = compareFunc;
            GL_SAFE_CALL(glSamplerParameteri(m_samplerId, GL_TEXTURE_COMPARE_FUNC, TextureCompareFunc::convert(compareFunc)));
        }
    }
}
