/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_TEXTURE1D_H_
#define COGRA_GL_TEXTURE1D_H_
#include <cogra/types.h>
#include <cogra/gl/Texture.h>
#include <cogra/gl/TextureEnums.h>
#include <string>
namespace cogra
{
namespace gl
{
class Texture1D : public Texture
{
public:
    Texture1D();

    Texture1D(const Texture1D&) = delete;

    Texture1D& operator=(const Texture1D&) = delete;

    Texture1D(Texture1D&& other);

    Texture1D& operator=(Texture1D&& other);

    virtual ~Texture1D() = default;

    explicit Texture1D(GLuint unit);

    Texture1D(GLuint unit, uint32 levels, uint32 width,
              TextureSizedInternalFormats::Enum sizedInternalFormat,
              TextureFormat::Enum format,
              TextureType::Enum type);

    void setImageData(uint32 level, uint32 width, void* data);

    static Texture1D loadFromFile(GLuint unit, const std::string& fileName);

    void generateMipmap();

private:

    TextureSizedInternalFormats::Enum   m_internalFormat;
    TextureFormat::Enum                 m_format;
    TextureType::Enum                   m_type;
};
}
}
#endif
