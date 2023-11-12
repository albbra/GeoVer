#pragma once
#include <imgui/imgui.h>
#include <cogra/types.h>
struct GLFWwindow;
struct GLFWcursor;
namespace cogra::ui
{

class ImGUIGLFW
{
public:

  ImGUIGLFW(GLFWwindow* window);

  ~ImGUIGLFW();

  void onMouseButton(int32 button, int32 action, int32 mods);

  void onMouseScroll(float64 yoffset);

  void onKey(int32 key, int32 scanCode, int32 action, int32 mods);

  void onChar(uint32 c);

  void newFrame();

private:

  static void setClipboardTextCallback(void* user_data, const char* text);

  static const char* getClipboardTextCallback(void* user_data);

  void setClipboardText(const char * text);

  const char * getClipboardText();

  void updateMousePosAndButtons();

  void updateMouseCursor();

  void updateGamepads();

  float getMonitorScaleFactor();


  GLFWwindow*       m_window = nullptr;

  float64           m_time = 0.0;

  bool              m_mouseJustPressed[5] = { false, false, false, false, false };

  GLFWcursor*       m_MouseCursors[ImGuiMouseCursor_COUNT] = {};

};

}
