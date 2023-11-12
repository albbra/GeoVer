
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable:4100)
#define STBI_MSC_SECURE_CRT
#endif
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>
#ifdef _MSC_VER
#pragma warning( pop )
#endif
