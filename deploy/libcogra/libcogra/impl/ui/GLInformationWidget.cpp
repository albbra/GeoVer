#include <cogra/ui/GLInformationWidget.h>
#include <cogra/gl/OpenGLRuntimeError.h>
#include <imgui/imgui.h>
#include <glad/glad.h>

namespace cogra
{
namespace ui
{

GLInformationWidget::GLInformationWidget()
{ }

void GLInformationWidget::drawUI()
{
  if(ImGui::CollapsingHeader("OpenGL Information"))
  {
    cogra::uint8 const* vendor;
    cogra::uint8 const* renderer;
    cogra::uint8 const* version;
    cogra::uint8 const* shadingLanguageVersion;

    GL_SAFE_CALL(vendor = (glGetString(GL_VENDOR)));
    GL_SAFE_CALL(renderer = (glGetString(GL_RENDERER)));
    GL_SAFE_CALL(version = (glGetString(GL_VERSION)));
    GL_SAFE_CALL(shadingLanguageVersion = (glGetString(GL_SHADING_LANGUAGE_VERSION)));

    ImGui::Text("Vender: %s", vendor);
    ImGui::Text("Renderer: %s", renderer);
    ImGui::Text("Version: %s", version);
    ImGui::Text("Shading Language Version: %s", shadingLanguageVersion);
  }

}
}
}