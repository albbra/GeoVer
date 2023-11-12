/// Cogra --- Coburg Graphics Framework 2017 - 2020
/// (C) 2017 - 2020 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/ui/ImGUIGLFW3Renderer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#else
#include <cstdio>
#include <cstdlib>
#include <string>
#endif

#include <cogra/types.h>
using namespace cogra;


namespace cogra
{
namespace ui
{
ImGUIGLFW3Renderer::ImGUIGLFW3Renderer(GLFWwindow* window)
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  m_imGuiGL = std::make_unique<cogra::ui::ImGUIGL>();
  m_imGuiGLFW = std::make_unique<cogra::ui::ImGUIGLFW>(window);
}

void ImGUIGLFW3Renderer::onMouseButton(int32_t button, int32_t action)
{
  m_imGuiGLFW->onMouseButton(button, action, 0);
}

void ImGUIGLFW3Renderer::onMouseScroll(double yoffset)
{
  m_imGuiGLFW->onMouseScroll(yoffset);
 
}

void ImGUIGLFW3Renderer::onKey(int32_t key, int32_t scanCode, int32_t action, int32_t mods)
{
  m_imGuiGLFW->onKey(key, scanCode, action, mods);
}

void ImGUIGLFW3Renderer::onChar(uint32_t c)
{
  m_imGuiGLFW->onChar(c);
}

void ImGUIGLFW3Renderer::newFrame()
{ 
  ImGuiIO& io = ImGui::GetIO();

  m_imGuiGLFW->newFrame();
  ImGui::NewFrame();
  
  m_isUIActive = io.WantCaptureMouse;
}

void ImGUIGLFW3Renderer::onDraw()
{
  ImGui::Render();
  m_imGuiGL->renderDrawData(ImGui::GetDrawData());
}


}
}
