/// Cogra --- Coburg Graphics Framework 2017 - 2020
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_UI_GLFWWINDOW_H_
#define COGRA_UI_GLFWWINDOW_H_
#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cogra/ui/ImGUIGLFW3Renderer.h>
#include <cogra/exceptions/RuntimeError.h>
#include <cogra/ui/GLFWWindowConfig.h>
#include <memory>
#include <iostream>
namespace cogra
{
namespace ui
{
template<class TApp>
class GLFWWindow
{
private:
  
  struct UserData
  {
    TApp* app;
    ImGUIGLFW3Renderer* imGUIGLFWRenderer;

    UserData(GLFWwindow* window)
    {
      app = new TApp(window);
      imGUIGLFWRenderer = new ImGUIGLFW3Renderer(window);

    }

    ~UserData()
    {
      delete app;
      delete imGUIGLFWRenderer;
    }

  };

public:
  explicit GLFWWindow(const GLFWWindowConfig& windowConfig)
    : m_window(nullptr)
  {
    const auto glfwInitSucess = glfwInit();
    if(glfwInitSucess != GLFW_TRUE)
    {
      Throw(cogra::exceptions::RuntimeError, "Could not init GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowConfig.glMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowConfig.glMinorVersion);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#else
    if(windowConfig.glMajorVersion >= 3 && windowConfig.glMajorVersion >= 2)
    {
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    else
    {
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    }

#endif
    if(windowConfig.disableDeprecatedFunctions)
    {
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }
    else
    {
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
    }

    if(windowConfig.useSRGB)
    {
      glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
    }
    else
    {
      glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_FALSE);
    }

    glfwWindowHint(GLFW_SAMPLES, windowConfig.samples);

    m_window = glfwCreateWindow(windowConfig.width, windowConfig.height, windowConfig.windowTitle.c_str(), nullptr, nullptr);

    if(m_window == nullptr)
    {
      glfwTerminate();
      Throw(cogra::exceptions::RuntimeError, "Error creating GLFW window.");
    }
    glfwMakeContextCurrent(m_window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    UserData* userData = new UserData(m_window);
    glfwSetWindowUserPointer(m_window, static_cast<void*>(userData));
    registerCallbacks();
  }

  ~GLFWWindow()
  {        
    deregisterCallbacks();
    UserData* userData = static_cast<UserData*>(glfwGetWindowUserPointer(m_window));
    delete userData;      
    if(m_window != nullptr)
    {
      glfwDestroyWindow(m_window);
    }
    glfwTerminate();
  }

  void run()
  {
    glfwSwapInterval(0);
    while(!glfwWindowShouldClose(m_window) && 
          !(getInstance(m_window)->exitAfterNextFrameTriggered()))
    {
      glfwPollEvents();
      if(getInstance(m_window)->isUIEnabled())
      {
        getImGUIGLFW3Renderer(m_window)->newFrame();
      }

      getInstance(m_window)->onDraw();

      getInstance(m_window)->onPostDraw();

      if(getInstance(m_window)->isUIEnabled())
      {
        getInstance(m_window)->onDrawUI();
        getImGUIGLFW3Renderer(m_window)->onDraw();        
        
      }
      glfwSwapBuffers(m_window);
    }
  }

  void runOnDrawOnce()
  {
    glfwSwapInterval(0);
    glfwPollEvents();
    getInstance(m_window)->onDraw();    
    glfwSwapBuffers(m_window);
  }

  const TApp& getInstance() const
  {
	  return *getInstance(m_window);
  }

  TApp& getInstance()
  {
	  return *getInstance(m_window);
  }

private:
  static TApp* getInstance(GLFWwindow* window)
  {
    UserData* userData = static_cast<UserData*>(glfwGetWindowUserPointer(window));
    return userData->app;
  }

  static ImGUIGLFW3Renderer* getImGUIGLFW3Renderer(GLFWwindow* window)
  {
    UserData* userData = static_cast<UserData*>(glfwGetWindowUserPointer(window));
    return userData->imGUIGLFWRenderer;
  }

  void registerCallbacks()
  {
    if(m_window == nullptr)
    {
      Throw(cogra::exceptions::RuntimeError, "m_window is nullptr.")
    }

    //glfwSetErrorCallback(onError);
    // glfwSetMonitorCallback();
    glfwSetWindowPosCallback(m_window, onWindowPosition);
    glfwSetWindowSizeCallback(m_window, onWindowSize);
    glfwSetWindowCloseCallback(m_window, onClose);
    glfwSetWindowRefreshCallback(m_window, onWindowRefresh);
    glfwSetWindowFocusCallback(m_window, onFocus);
    glfwSetWindowIconifyCallback(m_window, onIconify);
    glfwSetFramebufferSizeCallback(m_window, onFramebufferSize);
    glfwSetKeyCallback(m_window, onKey);
    glfwSetCharCallback(m_window, onChar);
    glfwSetCharModsCallback(m_window, onCharMods);

    glfwSetMouseButtonCallback(m_window, onMouseButton);

    glfwSetCursorPosCallback(m_window, onCursorPosition);
    glfwSetCursorEnterCallback(m_window, onCursorEnter);
    glfwSetScrollCallback(m_window, onScroll);
    // glfwSetDropCallback();
    // glfwSetJoystickCallback();
  }

  void deregisterCallbacks()
  { }

  static void onWindowPosition(GLFWwindow* window, int xpos, int ypos)
  {
    getInstance(window)->onWindowPosition(xpos, ypos);
  }

  static void onWindowSize(GLFWwindow* window, int width, int height)
  {
    getInstance(window)->onWindowSize(width, height);
  }

  static void onClose(GLFWwindow* window)
  {
    getInstance(window)->onClose();
  }

  static void onWindowRefresh(GLFWwindow* window)
  {
    getInstance(window)->onWindowRefresh();
  }

  static void onFocus(GLFWwindow* window, int focused)
  {
    if(focused == GLFW_TRUE)
    {
      getInstance(window)->onFocus(true);
    }
    else
    {
      getInstance(window)->onFocus(false);
    }
  }

  static void onIconify(GLFWwindow* window, int iconified)
  {
    if(iconified == GLFW_TRUE)
    {
      getInstance(window)->onIconify(true);
    }
    else
    {
      getInstance(window)->onIconify(false);
    }
  }

  static void onFramebufferSize(GLFWwindow* window, int width, int height)
  {
    getInstance(window)->onFramebufferSize(width, height);
  }

  static void onKey(GLFWwindow* window, int key, int scancode, int action, int mod)
  {
    getImGUIGLFW3Renderer(window)->onKey(key, scancode, action, mod);
    if(!getImGUIGLFW3Renderer(window)->isUIActive())
    {
      getInstance(window)->onKey(key, scancode, action, mod);
    }
  }

  static void onChar(GLFWwindow* window, uint32 codepoint)
  {
    getImGUIGLFW3Renderer(window)->onChar(codepoint);
    if(!getImGUIGLFW3Renderer(window)->isUIActive())
    {
      getInstance(window)->onChar(codepoint);
    }
  }

  static void onCharMods(GLFWwindow* window, uint32 codepoints, int mods)
  {
    getInstance(window)->onCharMods(codepoints, mods);
  }

  static void onMouseButton(GLFWwindow* window, int button, int action, int mods)
  {
    getImGUIGLFW3Renderer(window)->onMouseButton(button, action);
    if(!getImGUIGLFW3Renderer(window)->isUIActive())
    {
      getInstance(window)->onMouseButton(button, action, mods);
    }
  }

  static void onCursorPosition(GLFWwindow* window, float64 xpos, float64 ypos)
  {
    if(!getImGUIGLFW3Renderer(window)->isUIActive())
    {
      getInstance(window)->onCursorPosition(xpos, ypos);
    }
  }

  static void onCursorEnter(GLFWwindow* window, int entered)
  {
    if(entered == GLFW_TRUE)
    {
      getInstance(window)->onCursorEnter(true);
    }
    else
    {
      getInstance(window)->onCursorEnter(false);
    }
  }

  static void onScroll(GLFWwindow* window, float64 xoffset, float64 yoffset)
  {
    getImGUIGLFW3Renderer(window)->onMouseScroll(yoffset);
    getInstance(window)->onScroll(xoffset, yoffset);
  }

  GLFWwindow* m_window;
};
}
}
#endif
