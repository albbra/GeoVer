#pragma once
#ifndef COGRA_IMAGEPROCESSING_IMAGE_H
#define COGRA_IMAGEPROCESSING_IMAGE
#include <cogra/types.h>
#include <memory>
namespace cogra
{
namespace imageprocessing
{
class Image
{
public:
    Image(uint32 width, uint32 height, uint8 bytesPerPixel);

    const uint8* getData() const;

    uint8* getData();

    uint32 getWidth() const;

    uint32 getHeight() const;

    uint32 getBytesPerPixel() const;

    void flipImage();

private:
    std::unique_ptr<uint8[]> m_data;
    uint32 m_width;
    uint32 m_height;
    uint32 m_bytesPerPixel;

};
}
}
#endif