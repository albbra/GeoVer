#pragma once
#include <glad/glad.h>
#include <imgui/imgui.h>
#include <cogra/types.h>
namespace cogra::ui
{
class ImGUIGL
{
public:
  ImGUIGL();

  ~ImGUIGL();

  void renderDrawData(ImDrawData* draw_data);
private:

  void createDeviceObjects(); 

  void destroyDeviceObjects();

  void createFontsTexture();

  void destroyFontsTexture();

  void setupRenderState(ImDrawData* draw_data, int fb_width, int fb_height, GLuint vertex_array_object);

  bool checkProgram(GLuint handle, const char* desc);

  GLuint       g_GlVersion = 0;                // Extracted at runtime using GL_MAJOR_VERSION, GL_MINOR_VERSION queries.
  char         g_GlslVersionString[32] = "";   // Specified by user or detected based on compile time GL settings.
  GLuint       g_FontTexture = 0;
  GLuint       g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
  int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;                                // Uniforms location
  int          g_AttribLocationVtxPos = 0, g_AttribLocationVtxUV = 0, g_AttribLocationVtxColor = 0; // Vertex attributes location
  unsigned int g_VboHandle = 0, g_ElementsHandle = 0;

};
}