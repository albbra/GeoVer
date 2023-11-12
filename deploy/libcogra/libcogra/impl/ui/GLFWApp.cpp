/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/ui/GLFWApp.h>
#include <cogra/exceptions/RuntimeError.h>
#include <GLFW/glfw3.h>
using cogra::exceptions::RuntimeError;

namespace cogra
{
namespace ui
{
GLFWApp::GLFWApp(GLFWwindow* window)
  : m_window(window)
  , m_isUIEnabled(true)
  , m_exitAfterNextFrame(false)
{ }

GLFWApp::~GLFWApp() = default;

void GLFWApp::onDraw()
{ }

void GLFWApp::onPostDraw()
{ }

void GLFWApp::onDrawUI()
{ }

void GLFWApp::onError(int error, const char * /*description*/)
{
  switch(error)
  {
    case GLFW_NOT_INITIALIZED:
      Throw(RuntimeError, "GLFW has not been initialized. ");
      break;
    case GLFW_NO_CURRENT_CONTEXT:
      Throw(RuntimeError, "No context is current for this thread.");
      break;
    case GLFW_INVALID_ENUM:
      Throw(RuntimeError, "One of the arguments to the function was an invalid enum value.");
      break;
    case GLFW_INVALID_VALUE:
      Throw(RuntimeError, "One of the arguments to the function was an invalid value.");
      break;
    case GLFW_OUT_OF_MEMORY:
      Throw(RuntimeError, "A memory allocation failed.");
      break;
    case GLFW_API_UNAVAILABLE:
      Throw(RuntimeError, "GLFW could not find support for the requested API on the system.");
      break;
    case GLFW_VERSION_UNAVAILABLE:
      Throw(RuntimeError, "The requested OpenGL or OpenGL ES version is not available.");
      break;
    case GLFW_PLATFORM_ERROR:
      Throw(RuntimeError, "A platform - specific error occurred that does not match any of the more specific categories.");
      break;
    case GLFW_FORMAT_UNAVAILABLE:
      Throw(RuntimeError, "The requested format is not supported or available.");
      break;
    case GLFW_NO_WINDOW_CONTEXT:
      Throw(RuntimeError, "The specified window does not have an OpenGL or OpenGL ES context.");
      break;
    default:
      Throw(RuntimeError, "Unkown GLFW Error.");
  }
}

void GLFWApp::onWindowPosition(int32 /*xpos*/, int32 /*ypos*/)
{ }

void GLFWApp::onWindowSize(int32 /*width*/, int32 /*height*/)
{ }

void GLFWApp::onClose()
{ }

void GLFWApp::onWindowRefresh()
{ }

void GLFWApp::onFocus(bool /*focused*/)
{ }

void GLFWApp::onIconify(bool /*iconified*/)
{ }

void GLFWApp::onFramebufferSize(int32 /*width*/, int32 /*height*/)
{ }

void GLFWApp::onKey(int32 /*key*/, int32 /*scancode*/, int32 /*action*/, int32 /*mod*/)
{ }

void GLFWApp::onChar(uint32 /*codepoint*/)
{ }

void GLFWApp::onCharMods(uint32 /*codepoint*/, int32 /*mods*/)
{ }

void GLFWApp::onMouseButton(int32 /*button*/, int32 /*action*/, int32 /*mods*/)
{ }

void GLFWApp::onCursorPosition(float64 /*xpos*/, float64 /*ypos*/)
{ }

void GLFWApp::onCursorEnter(bool /*entered*/)
{ }

void GLFWApp::onScroll(float64 /*xoffset*/, float64 /*yoffset*/)
{ }

i32vec2 GLFWApp::getFramebufferDimensions() const
{
  int32 width, height;
  glfwGetFramebufferSize(m_window, &width, &height);
  return i32vec2(width, height);
}

i32vec2 GLFWApp::getWindowDimension() const
{
  int32 width, height;
  glfwGetWindowSize(m_window, &width, &height);
  return i32vec2(width, height);
}

int32 GLFWApp::getFramebufferWidth() const
{
  int32 width, height;
  glfwGetFramebufferSize(m_window, &width, &height);
  return width;
}

int32 GLFWApp::getFramebufferHeight() const
{
  int32 width, height;
  glfwGetFramebufferSize(m_window, &width, &height);
  return height;
}

f64vec2 GLFWApp::getMousePosition() const
{
  float64 x;
  float64 y;
  glfwGetCursorPos(m_window, &x, &y);
  return glm::dvec2(x, y);
}

f64vec2 GLFWApp::getNormalizedMousePosition() const
{
  glm::dvec2 normalizedPosition;
  const auto pos = getMousePosition();
  const auto dim = getWindowDimension();
  normalizedPosition.x = pos.x / static_cast<float64>(dim.x);
  normalizedPosition.y = 1.0 - pos.y / static_cast<float64>(dim.y);

  normalizedPosition.x *= 2.0;
  normalizedPosition.y *= 2.0;
  normalizedPosition.x -= 1.0;
  normalizedPosition.y -= 1.0;
  return normalizedPosition;
}

i32vec2 GLFWApp::getWindowPosition() const
{
  i32vec2 result;
  glfwGetWindowPos(m_window, &result.x, &result.y);
  return result;
}

void GLFWApp::setWindowPosition(const i32vec2 & windowPosition)
{
  glfwSetWindowPos(m_window, windowPosition.x, windowPosition.y);
}

float32 GLFWApp::getAspect() const
{
  const auto d = getFramebufferDimensions();
  return static_cast<float32>(d.x) / static_cast<float32>(d.y);
}

void GLFWApp::setWindowSize(const i32vec2 &windowSize)
{
  glfwSetWindowSize(m_window, windowSize.x, windowSize.y);
}

void GLFWApp::triggerExitAfterNextFrame()
{ 
  m_exitAfterNextFrame = true;
}

bool GLFWApp::exitAfterNextFrameTriggered() const
{
  return m_exitAfterNextFrame;

}

int32 GLFWApp::getKey(int32 key) const
{
  return glfwGetKey(m_window, key);
}

GLFWwindow* GLFWApp::getGLFWWindow() const
{
    return m_window;
}
}
}
