/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_UI_GLFWAPP_H_
#define COGRA_UI_GLFWAPP_H_
#include <cogra/types.h>
struct GLFWwindow;

namespace cogra
{
namespace ui
{
class GLFWApp
{
public:
  explicit GLFWApp(GLFWwindow* window);

  virtual ~GLFWApp();

  virtual void onDraw();

  virtual void onPostDraw();

  virtual void onDrawUI();

  virtual void onError(int error, const char* description);

  virtual void onWindowPosition(int32 xpos, int32 ypos);

  virtual void onWindowSize(int32 width, int32 height);

  virtual void onClose();

  virtual void onWindowRefresh();

  virtual void onFocus(bool focused);

  virtual void onIconify(bool iconified);

  virtual void onFramebufferSize(int32 width, int32 height);

  virtual void onKey(int32 key, int32 scancode, int32 action, int32 mod);

  virtual void onChar(uint32 codepoint);

  virtual void onCharMods(uint32 codepoint, int32 mods);

  virtual void onMouseButton(int32 button, int32 action, int32 mods);

  virtual void onCursorPosition(float64 xpos, float64 ypos);

  virtual void onCursorEnter(bool entered);

  virtual void onScroll(float64 xoffset, float64 yoffset);

  i32vec2 getFramebufferDimensions() const;

  i32vec2 getWindowDimension() const;

  int32 getFramebufferWidth() const;

  int32 getFramebufferHeight() const;

  f64vec2 getMousePosition() const;

  f64vec2 getNormalizedMousePosition() const;

  i32vec2 getWindowPosition() const;;

  void setWindowPosition(const i32vec2& windowPosition);

  float32 getAspect() const;

  void setWindowSize(const i32vec2 &windowSize);

  bool isUIEnabled() const
  {
    return m_isUIEnabled;
  }

  void setIsUIEnabled(bool flag)
  {
    m_isUIEnabled = flag;
  }

  void triggerExitAfterNextFrame();

  bool exitAfterNextFrameTriggered() const;

  int32 getKey(int32 key) const;

  GLFWwindow* getGLFWWindow() const;

private:
  GLFWwindow* m_window;

  bool        m_isUIEnabled;

  bool        m_exitAfterNextFrame;
};
}
}
#endif
