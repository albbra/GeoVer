#include <cogra/imageprocessing/Image.h>
namespace cogra
{
namespace imageprocessing
{

Image::Image(uint32 width, uint32 height, uint8 bytesPerPixel)
    : m_data(std::make_unique<uint8[]>(width * height * bytesPerPixel))
    , m_width(width)
    , m_height(height)
    , m_bytesPerPixel(bytesPerPixel)
{

}

const uint8* Image::getData() const
{
    return m_data.get();
}

uint8* Image::getData()
{
    return m_data.get();
}

uint32 Image::getWidth() const
{
    return m_width;
}

uint32 Image::getHeight() const
{
    return m_height;
}

uint32 Image::getBytesPerPixel() const
{
    return m_bytesPerPixel;
}

void Image::flipImage()
{
    
    for(uint32 y = 0; y < m_height/2; y++)
    {
        for(uint32 x = 0; x < m_width; x++)
        {
            for(uint32 c = 0; c < m_bytesPerPixel; c++)
            {
                std::swap(m_data[(y * m_width + x) * m_bytesPerPixel + c], m_data[((m_height - 1 - y) * m_width + x) * m_bytesPerPixel + c]);
            }

        }
    }
}

}
}
