/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 - 2020 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/ui/GLFWApp.h>
#include <cogra/ui/GLFWWindow.h>
#include <imgui/imgui.h>

using cogra::ui::GLFWWindow;
using cogra::ui::GLFWWindowConfig;
class Helloimgui : public cogra::ui::GLFWApp
{
public:
  explicit Helloimgui(GLFWwindow* window)
    : GLFWApp(window)
  { }

  void onDraw() override
  {
    glViewport(0, 0, getFramebufferWidth(), getFramebufferHeight());
    
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void onDrawUI() override
  {
    static bool show_test_window = true;
    static bool show_another_window = false;
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // 1. Show a simple window
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
    {
      static float f = 0.0f;
      ImGui::Text("Hello, world!");
      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
      ImGui::ColorEdit3("clear color", (float*)&clear_color);
      if(ImGui::Button("Test Window")) show_test_window ^= 1;
      if(ImGui::Button("Another Window")) show_another_window ^= 1;
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    // 2. Show another simple window, this time using an explicit Begin/End pair
    if(show_another_window)
    {
      ImGui::Begin("Another Window", &show_another_window);
      ImGui::Text("Hello from another window!");
      ImGui::End();
    }

    // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
    if(show_test_window)
    {
      ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
      ImGui::ShowDemoWindow(&show_test_window);
    }

    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
  }
};

int main(int /*argc*/, char** /*argv*/)
{
  GLFWWindowConfig config;
  config.glMajorVersion = 4;
  config.glMinorVersion = 0;
  config.loadGLExtensions = false;
  config.width = 1920;
  config.height = 1080;
  GLFWWindow<Helloimgui> app(config);
  app.run();
  return 1;
}
