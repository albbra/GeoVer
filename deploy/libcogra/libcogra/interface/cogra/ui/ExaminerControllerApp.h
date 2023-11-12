/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_UI_EXAMINERCONTROLLERAPP_H_
#define COGRA_UI_EXAMINERCONTROLLERAPP_H_
#include <cogra/ui/GLFWApp.h>
#include <cogra/ui/ExaminerController.h>
#include <cogra/gl/Screenshot.h>
namespace cogra
{
namespace ui
{
class ExaminerControllerApp : public cogra::ui::GLFWApp
{
public:
  //! \brief Creates a simple app with an examiner control.
  explicit ExaminerControllerApp(GLFWwindow* window);

  void onMouseButton(int32 button, int32 action, int32 mods) override;

  void onCursorPosition(float64 xpos, float64 ypos) override;

  void onKey(int32 key, int32 scancode, int32 action, int32 mod) override;

  void loadCameraState(const std::string& fileName);

  void saveCameraState(const std::string& fileName) const;

  void onPostDraw() override;

protected:
  cogra::ui::ExaminerController m_examinerController;
private:
  cogra::gl::Screenshot m_screenshot;
};
}
}
#endif
