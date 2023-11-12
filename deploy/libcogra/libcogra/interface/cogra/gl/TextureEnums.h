/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_TEXTUREENUM_H_
#define COGRA_GL_TEXTUREENUM_H_
#include <glad/glad.h>

namespace cogra
{
namespace gl
{
struct TextureBaseInternalFormat
{
  enum Enum
  {
    DepthComponent,
    DepthStencil,
    Red,
    RG,
    RGB,
    RGBA,
    End
  };

  static GLint convert(const TextureBaseInternalFormat::Enum x)
  {
    switch(x)
    {
      case DepthComponent:
        return GL_DEPTH_COMPONENT;
      case DepthStencil:
        return GL_DEPTH_STENCIL;
      case Red:
        return GL_RED;
      case RG:
        return GL_RG;
      case RGB:
        return GL_RGB;
      case RGBA:
        return GL_RGBA;
      default:
        return GL_NONE;
    }
  }

  static Enum convert(const GLint x)
  {
    switch(x)
    {
      case GL_DEPTH_COMPONENT:
        return DepthComponent;
      case GL_DEPTH_STENCIL:
        return DepthStencil;
      case GL_RED:
        return Red;
      case GL_RG:
        return RG;
      case GL_RGB:
        return RGB;
      case GL_RGBA:
        return RGBA;
      default:
        return End;
    }
  }
};

struct TextureSizedInternalFormats
{
  enum Enum
  {
    DepthComponent = 0,
    DepthStencil,
    DepthComponent32f,
    DepthComponent24,
    DepthComponent16,
    Depth32fStehcil8,
    Depth24Stencil8,
    StencilIndex8,
    Red,
    RG,
    RGB,
    RGBA,
    R8,
    R8_SNORM,
    R16,
    R16_SNORM,
    RG8,
    RG8_SNORM,
    RG16,
    RG16_SNORM,
    R3_G3_B2,
    RGB4,
    RGB5,
    RGB8,
    RGB8_SNORM,
    RGB10,
    RGB12,
    RGB16_SNORM,
    RGBA2,
    RGBA4,
    RGB5_A1,
    RGBA8,
    RGBA8_SNORM,
    RGB10_A2,
    RGB10_A2UI,
    RGBA12,
    RGBA16,
    SRGB8,
    SRGB8_ALPHA8,
    R16F,
    RG16F,
    RGB16F,
    RGBA16F,
    R32F,
    RG32F,
    RGB32F,
    RGBA32F,
    R11F_G11F_B10F,
    RGB9_E5,
    R8I,
    R8UI,
    R16I,
    R16UI,
    R32I,
    R32UI,
    RG8I,
    RG8UI,
    RG16I,
    RG16UI,
    RG32I,
    RG32UI,
    RGB8I,
    RGB8UI,
    RGB16I,
    RGB16UI,
    RGB32I,
    RGB32UI,
    RGBA8I,
    RGBA8UI,
    RGBA16I,
    RGBA16UI,
    RGBA32I,
    RGBA32UI,
    End
  };

  static Enum convert(const GLint x)
  {
    switch(x)
    {
      case GL_DEPTH_COMPONENT:
        return DepthComponent;
      case GL_DEPTH_STENCIL:
        return DepthStencil;
      case GL_DEPTH_COMPONENT32F:
        return DepthComponent32f;
      case GL_DEPTH_COMPONENT24:
        return DepthComponent24;
      case GL_DEPTH_COMPONENT16:
        return DepthComponent16;
      case GL_DEPTH32F_STENCIL8:
        return Depth32fStehcil8;
      case GL_DEPTH24_STENCIL8:
        return Depth24Stencil8;
      case GL_STENCIL_INDEX8:
        return StencilIndex8;
      case GL_RED:
        return Red;
      case GL_RG:
        return RG;
      case GL_RGB:
        return RGB;
      case GL_RGBA:
        return RGBA;
      case GL_R8:
        return R8;
      case GL_R8_SNORM:
        return R8_SNORM;
      case GL_R16:
        return R16;
      case GL_R16_SNORM:
        return R16_SNORM;
      case GL_RG8:
        return RG8;
      case GL_RG8_SNORM:
        return RG8_SNORM;
      case GL_RG16:
        return RG16;
      case GL_RG16_SNORM:
        return RG16_SNORM;
      case GL_R3_G3_B2:
        return R3_G3_B2;
      case GL_RGB4:
        return RGB4;
      case GL_RGB5:
        return RGB5;
      case GL_RGB8:
        return RGB8;
      case GL_RGB8_SNORM:
        return RGB8_SNORM;
      case GL_RGB10:
        return RGB10;
      case GL_RGB12:
        return RGB12;
      case GL_RGB16_SNORM:
        return RGB16_SNORM;
      case GL_RGBA2:
        return RGBA2;
      case GL_RGBA4:
        return RGBA4;
      case GL_RGB5_A1:
        return RGB5_A1;
      case GL_RGBA8:
        return RGBA8;
      case GL_RGBA8_SNORM:
        return RGBA8_SNORM;
      case GL_RGB10_A2:
        return RGB10_A2;
      case GL_RGB10_A2UI:
        return RGB10_A2UI;
      case GL_RGBA12:
        return RGBA12;
      case GL_RGBA16:
        return RGBA16;
      case GL_SRGB8:
        return SRGB8;
      case GL_SRGB8_ALPHA8:
        return SRGB8_ALPHA8;
      case GL_R16F:
        return R16F;
      case GL_RG16F:
        return RG16F;
      case GL_RGB16F:
        return RGB16F;
      case GL_RGBA16F:
        return RGBA16F;
      case GL_R32F:
        return R32F;
      case GL_RG32F:
        return RG32F;
      case GL_RGB32F:
        return RGB32F;
      case GL_RGBA32F:
        return RGBA32F;
      case GL_R11F_G11F_B10F:
        return R11F_G11F_B10F;
      case GL_RGB9_E5:
        return RGB9_E5;
      case GL_R8I:
        return R8I;
      case GL_R8UI:
        return R8UI;
      case GL_R16I:
        return R16I;
      case GL_R16UI:
        return R16UI;
      case GL_R32I:
        return R32I;
      case GL_R32UI:
        return R32UI;
      case GL_RG8I:
        return RG8I;
      case GL_RG8UI:
        return RG8UI;
      case GL_RG16I:
        return RG16I;
      case GL_RG16UI:
        return RG16UI;
      case GL_RG32I:
        return RG32I;
      case GL_RG32UI:
        return RG32UI;
      case GL_RGB8I:
        return RGB8I;
      case GL_RGB8UI:
        return RGB8UI;
      case GL_RGB16I:
        return RGB16I;
      case GL_RGB16UI:
        return RGB16UI;
      case GL_RGB32I:
        return RGB32I;
      case GL_RGB32UI:
        return RGB32UI;
      case GL_RGBA8I:
        return RGBA8I;
      case GL_RGBA8UI:
        return RGBA8UI;
      case GL_RGBA16I:
        return RGBA16I;
      case GL_RGBA16UI:
        return RGBA16UI;
      case GL_RGBA32I:
        return RGBA32I;
      case GL_RGBA32UI:
        return RGBA32UI;
      default:
        return End;
    }
  }

  static GLint convert(const Enum x)
  {
    switch(x)
    {
      case DepthComponent:
        return GL_DEPTH_COMPONENT;
      case DepthStencil:      
        return GL_DEPTH_STENCIL;
      case DepthComponent32f:
        return GL_DEPTH_COMPONENT32F;
      case DepthComponent24:
        return GL_DEPTH_COMPONENT24;
      case DepthComponent16:
        return GL_DEPTH_COMPONENT16;
      case Depth32fStehcil8:
        return GL_DEPTH32F_STENCIL8;
      case Depth24Stencil8:
        return GL_DEPTH24_STENCIL8;
      case StencilIndex8:
        return GL_STENCIL_INDEX8;
      case Red:
        return GL_RED;
      case RG:
        return GL_RG;
      case RGB:
        return GL_RGB;
      case RGBA:
        return GL_RGBA;
      case R8:
        return GL_R8;
      case R8_SNORM:
        return GL_R8_SNORM;
      case R16:
        return GL_R16;
      case R16_SNORM:
        return GL_R16_SNORM;
      case RG8:
        return GL_RG8;
      case RG8_SNORM:
        return GL_RG8_SNORM;
      case RG16:
        return GL_RG16;
      case RG16_SNORM:
        return GL_RG16_SNORM;
      case R3_G3_B2:
        return GL_R3_G3_B2;
      case RGB4:
        return GL_RGB4;
      case RGB5:
        return GL_RGB5;
      case RGB8:
        return GL_RGB8;
      case RGB8_SNORM:
        return GL_RGB8_SNORM;
      case RGB10:
        return GL_RGB10;
      case RGB12:
        return GL_RGB12;
      case RGB16_SNORM:
        return GL_RGB16_SNORM;
      case RGBA2:
        return GL_RGBA2;
      case RGBA4:
        return GL_RGBA4;
      case RGB5_A1:
        return GL_RGB5_A1;
      case RGBA8:
        return GL_RGBA8;
      case RGBA8_SNORM:
        return GL_RGBA8_SNORM;
      case RGB10_A2:
        return GL_RGB10_A2;
      case RGB10_A2UI:
        return GL_RGB10_A2UI;
      case RGBA12:
        return GL_RGBA12;
      case RGBA16:
        return GL_RGBA16;
      case SRGB8:
        return GL_SRGB8;
      case SRGB8_ALPHA8:
        return GL_SRGB8_ALPHA8;
      case R16F:
        return GL_R16F;
      case RG16F:
        return GL_RG16F;
      case RGB16F:
        return GL_RGB16F;
      case RGBA16F:
        return GL_RGBA16F;
      case R32F:
        return GL_R32F;
      case RG32F:
        return GL_RG32F;
      case RGB32F:
        return GL_RGB32F;
      case RGBA32F:
        return GL_RGBA32F;
      case R11F_G11F_B10F:
        return GL_R11F_G11F_B10F;
      case RGB9_E5:
        return GL_RGB9_E5;
      case R8I:
        return GL_R8I;
      case R8UI:
        return GL_R8UI;
      case R16I:
        return GL_R16I;
      case R16UI:
        return GL_R16UI;
      case R32I:
        return GL_R32I;
      case R32UI:
        return GL_R32UI;
      case RG8I:
        return GL_RG8I;
      case RG8UI:
        return GL_RG8UI;
      case RG16I:
        return GL_RG16I;
      case RG16UI:
        return GL_RG16UI;
      case RG32I:
        return GL_RG32I;
      case RG32UI:
        return GL_RG32UI;
      case RGB8I:
        return GL_RGB8I;
      case RGB8UI:
        return GL_RGB8UI;
      case RGB16I:
        return GL_RGB16I;
      case RGB16UI:
        return GL_RGB16UI;
      case RGB32I:
        return GL_RGB32I;
      case RGB32UI:
        return GL_RGB32UI;
      case RGBA8I:
        return GL_RGBA8I;
      case RGBA8UI:
        return GL_RGBA8UI;
      case RGBA16I:
        return GL_RGBA16I;
      case RGBA16UI:
        return GL_RGBA16UI;
      case RGBA32I:
        return GL_RGBA32I;
      case RGBA32UI:
        return GL_RGBA32UI;
      default:
        return GL_NONE;
    }
  }

  static GLint sizeInBytes(const Enum x)
  {
    switch(x)
    {
      case DepthComponent:
        return 4;
      case DepthStencil:
        return 4;
      case Red:
        return 1;
      case RG:
        return 2;
      case RGB:
        return 3;
      case RGBA:
        return 4;
      case R8:
        return 1;
      case R8_SNORM:
        return 1;
      case R16:
        return 2;
      case R16_SNORM:
        return 2;
      case RG8:
        return 2;
      case RG8_SNORM:
        return 2;
      case RG16:
        return 4;
      case RG16_SNORM:
        return 4;
      case R3_G3_B2:
        return 8;
      case RGB4:
        return 2;
      case RGB5:
        return 2;
      case RGB8:
        return 3;
      case RGB8_SNORM:
        return 3;
      case RGB10:
        return 4;
      case RGB12:
        return 4;
      case RGB16_SNORM:
        return 6;
      case RGBA2:
        return 8;
      case RGBA4:
        return 2;
      case RGB5_A1:
        return 2;
      case RGBA8:
        return 4;
      case RGBA8_SNORM:
        return 4;
      case RGB10_A2:
        return 4;
      case RGB10_A2UI:
        return 4;
      case RGBA12:
        return 6;
      case RGBA16:
        return 8;
      case SRGB8:
        return 3;
      case SRGB8_ALPHA8:
        return 4;
      case R16F:
        return 2;
      case RG16F:
        return 4;
      case RGB16F:
        return 6;
      case RGBA16F:
        return 8;
      case R32F:
        return 4;
      case RG32F:
        return 8;
      case RGB32F:
        return 12;
      case RGBA32F:
        return 16;
      case R11F_G11F_B10F:
        return 4;
      case RGB9_E5:
        return 4;
      case R8I:
        return 1;
      case R8UI:
        return 1;
      case R16I:
        return 2;
      case R16UI:
        return 2;
      case R32I:
        return 4;
      case R32UI:
        return 4;
      case RG8I:
        return 2;
      case RG8UI:
        return 2;
      case RG16I:
        return 4;
      case RG16UI:
        return 4;
      case RG32I:
        return 8;
      case RG32UI:
        return 8;
      case RGB8I:
        return 3;
      case RGB8UI:
        return 3;
      case RGB16I:
        return 6;
      case RGB16UI:
        return 6;
      case RGB32I:
        return 12;
      case RGB32UI:
        return 12;
      case RGBA8I:
        return 4;
      case RGBA8UI:
        return 4;
      case RGBA16I:
        return 8;
      case RGBA16UI:
        return 8;
      case RGBA32I:
        return 16;
      case RGBA32UI:
        return 16;
      default:
        return GL_NONE;
    }
  }


};

struct TextureType
{
  enum Enum
  {
    UnsignedByte = 0,
    Byte,
    UnsignedShort,
    Short,
    UnsignedInt,
    Int,
    Float,
    UnsignedByte_3_3_2,
    UnsignedByte_2_3_3_Rev,
    UnsignedShort_5_6_5,
    UnsignedShort_5_6_5_Rev,
    UnsignedShort_4_4_4_4,
    UnsignedShort_4_4_4_4_Rev,
    UnsignedShort_5_5_5_1,
    UnsignedShort_1_5_5_5_Rev,
    UnsignedInt_8_8_8_8,
    UnsignedInt_8_8_8_8_Rev,
    UnsignedInt_10_10_10_2,
    UnsignedInt_2_10_10_10_Rev,
    End
  };

  static GLenum convert(const TextureType::Enum x)
  {
    switch(x)
    {
      case UnsignedByte:
        return GL_UNSIGNED_BYTE;
      case Byte:
        return GL_BYTE;
      case UnsignedShort:
        return GL_UNSIGNED_SHORT;
      case Short:
        return GL_SHORT;
      case UnsignedInt:
        return GL_UNSIGNED_INT;
      case Int:
        return GL_INT;
      case Float:
        return GL_FLOAT;
      case UnsignedByte_3_3_2:
        return GL_UNSIGNED_BYTE_3_3_2;
      case UnsignedByte_2_3_3_Rev:
        return GL_UNSIGNED_BYTE_2_3_3_REV;
      case UnsignedShort_5_6_5:
        return GL_UNSIGNED_SHORT_5_6_5;
      case UnsignedShort_5_6_5_Rev:
        return GL_UNSIGNED_SHORT_5_6_5_REV;
      case UnsignedShort_4_4_4_4:
        return GL_UNSIGNED_SHORT_4_4_4_4;
      case UnsignedShort_4_4_4_4_Rev:
        return GL_UNSIGNED_SHORT_4_4_4_4_REV;
      case UnsignedShort_5_5_5_1:
        return GL_UNSIGNED_SHORT_5_5_5_1;
      case UnsignedShort_1_5_5_5_Rev:
        return GL_UNSIGNED_SHORT_1_5_5_5_REV;
      case UnsignedInt_8_8_8_8:
        return GL_UNSIGNED_INT_8_8_8_8;
      case UnsignedInt_8_8_8_8_Rev:
        return GL_UNSIGNED_INT_8_8_8_8_REV;
      case UnsignedInt_10_10_10_2:
        return GL_UNSIGNED_INT_10_10_10_2;
      case UnsignedInt_2_10_10_10_Rev:
        return GL_UNSIGNED_INT_2_10_10_10_REV;
      default:
        return GL_NONE;
    }
  }

  static TextureType::Enum convert(const GLenum x)
  {
    switch(x)
    {
      case GL_UNSIGNED_BYTE:
        return UnsignedByte;
      case GL_BYTE:
        return Byte;
      case GL_UNSIGNED_SHORT:
        return UnsignedShort;
      case GL_SHORT:
        return Short;
      case GL_UNSIGNED_INT:
        return UnsignedInt;
      case GL_INT:
        return Int;
      case GL_FLOAT:
        return Float;
      case GL_UNSIGNED_BYTE_3_3_2:
        return UnsignedByte_3_3_2;
      case GL_UNSIGNED_BYTE_2_3_3_REV:
        return UnsignedByte_2_3_3_Rev;
      case GL_UNSIGNED_SHORT_5_6_5:
        return UnsignedShort_5_6_5;
      case GL_UNSIGNED_SHORT_5_6_5_REV:
        return UnsignedShort_5_6_5_Rev;
      case GL_UNSIGNED_SHORT_4_4_4_4:
        return UnsignedShort_4_4_4_4;
      case GL_UNSIGNED_SHORT_4_4_4_4_REV:
        return UnsignedShort_4_4_4_4_Rev;
      case GL_UNSIGNED_SHORT_5_5_5_1:
        return UnsignedShort_5_5_5_1;
      case GL_UNSIGNED_SHORT_1_5_5_5_REV:
        return UnsignedShort_1_5_5_5_Rev;
      case GL_UNSIGNED_INT_8_8_8_8:
        return UnsignedInt_8_8_8_8;
      case GL_UNSIGNED_INT_8_8_8_8_REV:
        return UnsignedInt_8_8_8_8_Rev;
      case GL_UNSIGNED_INT_10_10_10_2:
        return UnsignedInt_10_10_10_2;
      case GL_UNSIGNED_INT_2_10_10_10_REV:
        return UnsignedInt_2_10_10_10_Rev;
      default:
        return End;
    }
  }
};

struct TextureFormat
{
  enum Enum
  {
    Red = 0,
    RG,
    RGB,
    BGR,
    RGBA,
    BGRA,
    RedInteger,
    RGInteger,
    RGBInteger,
    BGRInteger,
    RGBAInteger,
    BGRAInteger,
    StencilIndex,
    DepthComponent,
    DepthStencil,
    End
  };

  static GLenum convert(const TextureFormat::Enum x)
  {
    switch(x)
    {
      case Red:
        return GL_RED;
      case RG:
        return GL_RG;
      case RGB:
        return GL_RGB;
      case BGR:
        return GL_BGR;
      case RGBA:
        return GL_RGBA;
      case BGRA:
        return GL_BGRA;
      case RedInteger:
        return GL_RED_INTEGER;
      case RGInteger:
        return GL_RG_INTEGER;
      case RGBInteger:
        return GL_RGB_INTEGER;
      case BGRInteger:
        return GL_BGR_INTEGER;
      case RGBAInteger:
        return GL_RGBA_INTEGER;
      case BGRAInteger:
        return GL_BGRA_INTEGER;
      case StencilIndex:
        return GL_STENCIL_INDEX;
      case DepthComponent:
        return GL_DEPTH_COMPONENT;
      case DepthStencil:
        return GL_DEPTH_STENCIL;
      default:
        return GL_NONE;
    }
  }

  static TextureFormat::Enum convert(const GLenum x)
  {
    switch(x)
    {
      case GL_RED:
        return Red;
      case GL_RG:
        return RG;
      case GL_RGB:
        return RGB;
      case GL_BGR:
        return BGR;
      case GL_RGBA:
        return RGBA;
      case GL_BGRA:
        return BGRA;
      case GL_RED_INTEGER:
        return RedInteger;
      case GL_RG_INTEGER:
        return RGInteger;
      case GL_RGB_INTEGER:
        return RGBInteger;
      case GL_BGR_INTEGER:
        return BGRInteger;
      case GL_RGBA_INTEGER:
        return RGBAInteger;
      case GL_BGRA_INTEGER:
        return BGRAInteger;
      case GL_STENCIL_INDEX:
        return StencilIndex;
      case GL_DEPTH_COMPONENT:
        return DepthComponent;
      case GL_DEPTH_STENCIL:
        return DepthStencil;
      default:
        return End;
    }
  }
};

struct TexelSize
{
  static size_t inBytes(const TextureType::Enum textureType, const TextureFormat::Enum format)
  {

    size_t baseSize;
    switch(textureType)
    {
      case TextureType::UnsignedByte:
        baseSize = 1; break;
      case TextureType::Byte:
        baseSize = 1; break;
      case TextureType::UnsignedShort:
        baseSize = 2; break;
      case TextureType::Short:
        baseSize = 2; break;
      case TextureType::UnsignedInt:
        baseSize = 4; break;
      case TextureType::Int:
        baseSize = 4; break;
      case TextureType::Float:
        baseSize = 4; break;
      case TextureType::UnsignedByte_2_3_3_Rev:
        return 1;
      case TextureType::UnsignedShort_5_6_5:
        return 2;
      case TextureType::UnsignedShort_5_6_5_Rev:
        return 2;
      case TextureType::UnsignedShort_4_4_4_4:
        return 2;
      case TextureType::UnsignedShort_4_4_4_4_Rev:
        return 2;
      case TextureType::UnsignedShort_5_5_5_1:
        return 2;
      case TextureType::UnsignedShort_1_5_5_5_Rev:
        return 2;
      case TextureType::UnsignedInt_8_8_8_8:
        return 4;
      case TextureType::UnsignedInt_8_8_8_8_Rev:
        return 4;
      case TextureType::UnsignedInt_10_10_10_2:
        return 4;
      case TextureType::UnsignedInt_2_10_10_10_Rev:
        return 4;
      default:
        return 0;
    }

    switch(format)
    {
      case TextureFormat::Red:
        return baseSize * 1;
      case TextureFormat::RG:
        return baseSize * 2;
      case TextureFormat::RGB:
        return baseSize * 3;
      case TextureFormat::BGR:
        return baseSize * 3;
      case TextureFormat::RGBA:
        return baseSize * 4;
      case TextureFormat::BGRA:
        return baseSize * 4;
      case TextureFormat::RedInteger:
        return baseSize * 1;
      case TextureFormat::RGInteger:
        return baseSize * 2;
      case TextureFormat::RGBInteger:
        return baseSize * 3;
      case TextureFormat::BGRInteger:
        return baseSize * 3;
      case TextureFormat::RGBAInteger:
        return baseSize * 4;
      case TextureFormat::BGRAInteger:
        return baseSize * 4;
      case TextureFormat::StencilIndex:
        return baseSize;
      case TextureFormat::DepthComponent:
        return baseSize;
      case TextureFormat::DepthStencil:
        return baseSize;
      default:
        return 0;
    }
  }
};


struct TextureTarget
{
  enum Enum
  {
    Texture1D = 0,
    Texture2D,
    Texture3D,
    Texture1DArray,
    Texture2DArray,
    TextureRectangle,
    TextureCubeMap,
    End
  };

  static TextureTarget::Enum convert(const GLenum x)
  {
    switch(x)
    {
      case GL_TEXTURE_1D:
        return Texture1D;
      case GL_TEXTURE_2D:
        return Texture2D;
      case GL_TEXTURE_3D:
        return Texture3D;
      case GL_TEXTURE_1D_ARRAY:
        return Texture1DArray;
      case GL_TEXTURE_2D_ARRAY:
        return Texture2DArray;
      case GL_TEXTURE_RECTANGLE:
        return TextureRectangle;
      case GL_TEXTURE_CUBE_MAP:
        return TextureCubeMap;
      default:
        return End;
    }
  }

  static GLenum convert(const TextureTarget::Enum x)
  {
    switch(x)
    {
      case Texture1D:
        return GL_TEXTURE_1D;
      case Texture2D:
        return GL_TEXTURE_2D;
      case Texture3D:
        return GL_TEXTURE_3D;
      case Texture1DArray:
        return GL_TEXTURE_1D_ARRAY;
      case Texture2DArray:
        return GL_TEXTURE_2D_ARRAY;
      case TextureRectangle:
        return GL_TEXTURE_RECTANGLE;
      case TextureCubeMap:
        return GL_TEXTURE_CUBE_MAP;
      default:
        return GL_NONE;
    }
  }
};

struct TextureMinFilter
{
  enum Enum
  {
    Nearest = 0,
    Linear,
    NearestMipMapNearest,
    LinearMipMapNearest,
    NearestMipMapLinear,
    LinearMipMapLinear,
    End
  };

  static GLint convert(const TextureMinFilter::Enum x)
  {
    switch(x)
    {
      case Nearest:
        return GL_NEAREST;
      case Linear:
        return GL_LINEAR;
      case NearestMipMapNearest:
        return GL_NEAREST_MIPMAP_NEAREST;
      case LinearMipMapNearest:
        return GL_LINEAR_MIPMAP_NEAREST;
      case NearestMipMapLinear:
        return GL_NEAREST_MIPMAP_LINEAR;
      case LinearMipMapLinear:
        return GL_LINEAR_MIPMAP_LINEAR;
      default:
        return GL_NONE;
    }
  }

  static TextureMinFilter::Enum convert(const GLint x)
  {
    switch(x)
    {
      case GL_NEAREST:
        return Nearest;
        break;
      case GL_LINEAR:
        return Linear;
        break;
      case GL_NEAREST_MIPMAP_NEAREST:
        return NearestMipMapNearest;
        break;
      case GL_LINEAR_MIPMAP_NEAREST:
        return LinearMipMapNearest;
        break;
      case GL_NEAREST_MIPMAP_LINEAR:
        return NearestMipMapLinear;
        break;
      case GL_LINEAR_MIPMAP_LINEAR:
        return LinearMipMapLinear;
        break;
      default:
        return End;
    }
  }
};

struct TextureMagFilter
{
  enum Enum
  {
    Nearest = 0,
    Linear,
    End
  };

  static TextureMagFilter::Enum convert(const GLint x)
  {
    switch(x)
    {
      case GL_NEAREST:
        return Nearest;
      case GL_LINEAR:
        return Nearest;
      default:
        return End;
    }
  }

  static GLint convert(const TextureMagFilter::Enum x)
  {
    switch(x)
    {
      case Nearest:
        return GL_NEAREST;
      case Linear:
        return GL_LINEAR;
      default:
        return End;
    }
  }
};

struct TextureWrap
{
  enum Enum
  {
    ClampToEdge = 0,
    MirroredRepeat,
    Repeat,
    MirrorClampToEdge,
    ClampToBorder,
    End
  };

  static TextureWrap::Enum convert(GLint x)
  {
    switch(x)
    {
      case GL_CLAMP_TO_EDGE:
        return ClampToEdge;
      case GL_MIRRORED_REPEAT:
        return MirroredRepeat;
      case GL_REPEAT:
        return Repeat;
        //case GL_MIRROR_CLAMP_TO_EDGE:
        //  return MirrorClampToEdge;
      case GL_CLAMP_TO_BORDER:
        return ClampToBorder;
      default:
        return End;
    }
  }

  static GLint convert(const TextureWrap::Enum x)
  {
    switch(x)
    {
      case ClampToEdge:
        return GL_CLAMP_TO_EDGE;
      case MirroredRepeat:
        return GL_MIRRORED_REPEAT;
      case Repeat:
        return GL_REPEAT;
      case MirrorClampToEdge:
        return GL_NONE;
      case ClampToBorder:
        return GL_CLAMP_TO_BORDER;
      default:
        return GL_NONE;
    }
  }
};

struct TextureCompareMode
{
  enum Enum
  {
    CompareRefToTexture = 0,
    None,
    End
  };

  static TextureCompareMode::Enum convert(const GLint x)
  {
    switch(x)
    {
      case GL_COMPARE_REF_TO_TEXTURE:
        return CompareRefToTexture;
      case None:
        return None;
      default:
        return End;
    }
  }

  static GLint convert(const TextureCompareMode::Enum x)
  {
    switch(x)
    {
      case CompareRefToTexture:
        return GL_COMPARE_REF_TO_TEXTURE;
      case None:
        return GL_NONE;
      default:
        return GL_NONE;
    }
  }
};

struct TextureCompareFunc
{
  enum Enum
  {
    LessEqual = 0,
    GreaterEqual,
    Less,
    Greater,
    Equal,
    NotEqual,
    Always,
    Never,
    End
  };

  static TextureCompareFunc::Enum convert(const GLint x)
  {
    switch(x)
    {
      case GL_LEQUAL:
        return LessEqual;
      case GL_GEQUAL:
        return GreaterEqual;
      case GL_LESS:
        return Less;
      case GL_GREATER:
        return Greater;
      case GL_EQUAL:
        return Equal;
      case GL_NOTEQUAL:
        return NotEqual;
      case GL_ALWAYS:
        return Always;
      case GL_NEVER:
        return Never;
      default:
        return End;
    }
  }

  static GLint convert(const TextureCompareFunc::Enum x)
  {
    switch(x)
    {
      case LessEqual:
        return GL_LEQUAL;
      case GreaterEqual:
        return GL_GEQUAL;
      case Less:
        return GL_LESS;
      case Greater:
        return GL_GREATER;
      case Equal:
        return GL_EQUAL;
      case NotEqual:
        return GL_NOTEQUAL;
      case Always:
        return GL_ALWAYS;
      case Never:
        return GL_NEVER;
      default:
        return GL_NONE;
    }
  }
};

struct DepthStencilTextureMode
{
  enum Enum
  {
    DepthComponent = 0,
    StencilComponent,
    End
  };

  static GLint convert(const DepthStencilTextureMode::Enum x)
  {
    switch(x)
    {
      case DepthComponent:
        return GL_DEPTH_COMPONENT;
      case StencilComponent:
        return GL_STENCIL_COMPONENTS;
      default:
        return GL_NONE;
    }
  }

  static DepthStencilTextureMode::Enum convert(const GLint x)
  {
    switch(x)
    {
      case GL_DEPTH_COMPONENT:
        return DepthComponent;
      case GL_STENCIL_COMPONENTS:
        return StencilComponent;
      default:
        return End;
    }
  }
};

struct TextureSwizzle
{
  enum Enum
  {
    Red = 0,
    Green,
    Blue,
    Alpha,
    Zero,
    One,
    End
  };

  static TextureSwizzle::Enum convert(const GLint x)
  {
    switch(x)
    {
      case GL_RED:
        return Red;
      case GL_GREEN:
        return Green;
      case GL_BLUE:
        return Blue;
      case GL_ALPHA:
        return Alpha;
      case GL_ZERO:
        return Zero;
      case GL_ONE:
        return One;
      default:
        return End;
    }
  }

  static GLint convert(const Enum x)
  {
    switch(x)
    {
      case Red:
        return GL_RED;
      case Green:
        return GL_GREEN;
      case Blue:
        return GL_BLUE;
      case Alpha:
        return GL_ALPHA;
      case Zero:
        return GL_ZERO;
      case One:
        return GL_ONE;
      default:
        return GL_NONE;
    }
  }
};
}
}

#endif
