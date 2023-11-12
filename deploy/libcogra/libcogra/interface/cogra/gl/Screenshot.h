#pragma once
#ifndef COGRA_GL_SCREENSHOT_H
#define COGRA_GL_SCREENSHOT_H
#include <string>

namespace cogra
{
namespace gl
{
class Screenshot
{
public:
  Screenshot();

  void triggerSaveScreenshot(const std::string& filename);

  void triggerSaveToClipboard();

  void saveToFileIfTriggered();

  void saveToClipboardIfTriggered();

private:
  bool            m_screenshotSaveToFileTriggered;

  std::string     m_fileName;

  bool            m_screenshotSaveToClipboardTriggered;
};
}
}
#endif