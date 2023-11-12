#include <cogra/types.h>
#include <cogra/gl/Screenshot.h>
#include <glad/glad.h>
#include <cogra/gl/OpenGLRuntimeError.h>
#include <cstring>
#include <clip/clip.h>
#include <cogra/imageprocessing/Image.h>
#include <stb/stb_image_write.h>

namespace
{
cogra::imageprocessing::Image getScreenshot()
{
  struct ViewportInformation
  {
    GLint x;
    GLint y;
    GLint width;
    GLint height;
  };

  ViewportInformation viewportInfo;
  GL_SAFE_CALL(glGetIntegerv(GL_VIEWPORT, reinterpret_cast<GLint*>(&viewportInfo)));
  cogra::imageprocessing::Image image(viewportInfo.width, viewportInfo.height, 4);

  GLint packAlignment;
  GL_SAFE_CALL(glGetIntegerv(GL_PACK_ALIGNMENT, &packAlignment));
  GL_SAFE_CALL(glPixelStorei(GL_PACK_ALIGNMENT, 1));
  GL_SAFE_CALL(glReadPixels(0, 0, viewportInfo.width, viewportInfo.height, GL_RGBA, GL_UNSIGNED_BYTE, image.getData()));
  image.flipImage();
  GL_SAFE_CALL(glPixelStorei(GL_PACK_ALIGNMENT, packAlignment));
  return image;
}

void saveImageToFile(const std::string& filename)
{
  const auto image = getScreenshot();
  //stbi_write_bmp(filename.c_str(), image.getWidth(), image.getHeight(), image.getBytesPerPixel(), image.getData());
  stbi_write_png(filename.c_str(), image.getWidth(), image.getHeight(), image.getBytesPerPixel(), image.getData(), 0);
}

void saveImageToClipboard()
{
  const auto image = getScreenshot();

  clip::image_spec spec;
  spec.width = image.getWidth();
  spec.height = image.getHeight();
  spec.bits_per_pixel = image.getBytesPerPixel() * 8;
  spec.bytes_per_row = spec.width*image.getBytesPerPixel();
  spec.red_mask = 0xff;
  spec.green_mask = 0xff00;
  spec.blue_mask = 0xff0000;
  spec.alpha_mask = 0xff000000;
  spec.red_shift = 0;
  spec.green_shift = 8;
  spec.blue_shift = 16;
  spec.alpha_shift = 24;
  clip::image img(image.getData(), spec);
  clip::set_image(img);
}
}

namespace cogra
{
namespace gl
{
Screenshot::Screenshot()
  : m_screenshotSaveToFileTriggered(false)
  , m_fileName("")
  , m_screenshotSaveToClipboardTriggered(false)
{
}

void Screenshot::triggerSaveScreenshot(const std::string & filename)
{
  m_screenshotSaveToFileTriggered = true;
  m_fileName = filename;
}

void Screenshot::triggerSaveToClipboard()
{
  m_screenshotSaveToClipboardTriggered = true;
}

void Screenshot::saveToFileIfTriggered()
{
  if(m_screenshotSaveToFileTriggered)
  {
    saveImageToFile(m_fileName);
    m_screenshotSaveToFileTriggered = false;
  }
}

void Screenshot::saveToClipboardIfTriggered()
{
  if(m_screenshotSaveToClipboardTriggered)
  {
    saveImageToClipboard();
    m_screenshotSaveToClipboardTriggered = false;
  }
}

}
}

