/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 - 2020 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#pragma once
#include <cstdint>
#include <cogra/ui/ImGUIGL.h>
#include <cogra/ui/ImGUIGLFW.h>
#include <memory>
struct GLFWwindow;
struct ImDrawData;
namespace cogra
{
namespace ui
{

class ImGUIGLFW3Renderer
{
public:    

  ImGUIGLFW3Renderer(GLFWwindow* window);

  void onMouseButton(int32_t button, int32_t action);

  void onMouseScroll(double yoffset);

  void onKey(int32_t key, int32_t, int32_t action, int32_t mods);

  void onChar(uint32_t c);

  void newFrame();

  void onDraw();

  /// <summary>
  /// Checks, whether the user wants to interact with gui or not.
  /// </summary>
  /// <returns>Return true if the user interacts with the graphics user interface.</returns>
  bool isUIActive() const
  {
    return m_isUIActive;
  }

private:

  std::unique_ptr<cogra::ui::ImGUIGL> m_imGuiGL;

  std::unique_ptr<cogra::ui::ImGUIGLFW> m_imGuiGLFW;

  /// <summary>
  /// True in case the ui request user interaction.
  /// </summary>
  bool m_isUIActive;
};
}
}
