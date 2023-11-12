/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/ui/ExaminerControllerApp.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <cogra/exceptions/RuntimeError.h>
#include <cogra/types.h>
#include <cogra/gl/Screenshot.h>
#include <cogra/ui/FileDialog.h>
namespace cogra
{
namespace ui
{
ExaminerControllerApp::ExaminerControllerApp(GLFWwindow* window)
  : GLFWApp(window)
{ }

void ExaminerControllerApp::onMouseButton(int32 button, int32 action, int32 mods)
{
  m_examinerController.click(action == GLFW_PRESS, 1u << button, mods == GLFW_MOD_CONTROL, getNormalizedMousePosition());
}

void ExaminerControllerApp::onCursorPosition(float64, float64)
{
  m_examinerController.move(getNormalizedMousePosition());
}

void ExaminerControllerApp::onKey(int32 key, int32 scancode, int32 action, int32 mod)
{
  if(key == GLFW_KEY_L && action == GLFW_PRESS)
  {
    const auto cameraStateFileName = cogra::ui::FileDialog::openFile("All\0*.*\0State File\0*.STA\0");
    if(cameraStateFileName != "")
    {
      loadCameraState(cameraStateFileName);
    }
  }
  if(key == GLFW_KEY_S && action == GLFW_PRESS)
  {
    const auto cameraStateFileName = cogra::ui::FileDialog::saveFile("All\0*.*\0State File\0*.STA\0");
    if(cameraStateFileName != "")
    {
      saveCameraState(cameraStateFileName);
    }
  }

  if(key == GLFW_KEY_F5 && action == GLFW_PRESS)
  {
    m_screenshot.triggerSaveToClipboard();
  }

  if(key == GLFW_KEY_F1 && action == GLFW_PRESS)
  {
    setIsUIEnabled(!isUIEnabled());
  }
}

void ExaminerControllerApp::loadCameraState(const std::string & fileName)
{
  std::ifstream inFile;
  inFile.open(fileName, std::ios::in | std::ios::binary);
  if(!inFile.is_open())
  {
    throw cogra::exceptions::RuntimeError("Error reading cam file: " + fileName + ".");
  }
  f32quat rotation;
  f32vec3 translation;
  i32vec2 windowPosition;
  i32vec2 windowDimensions;
  inFile.read(reinterpret_cast<char*>(&rotation.x), sizeof(rotation));
  inFile.read(reinterpret_cast<char*>(&translation.x), sizeof(translation));
  inFile.read(reinterpret_cast<char*>(&windowPosition.x), sizeof(windowPosition));
  inFile.read(reinterpret_cast<char*>(&windowDimensions.x), sizeof(windowDimensions));
  inFile.close();

  m_examinerController.setRotationQuaterion(rotation);
  m_examinerController.setTranslationVector(translation);
  setWindowPosition(windowPosition);
  setWindowSize(windowDimensions);
}

void ExaminerControllerApp::saveCameraState(const std::string & fileName) const
{
  std::ofstream outFile;
  outFile.open(fileName, std::ios::out | std::ios::binary);
  if(!outFile.is_open())
  {
    throw cogra::exceptions::RuntimeError("Error writing cam file: " + fileName + ".");
  }
  const f32quat rotation = m_examinerController.getRotationQuaterion();
  const f32vec3 translation = m_examinerController.getTranslationVector();
  const i32vec2 windowPosition = getWindowPosition();
  const i32vec2 windowDimensions = getFramebufferDimensions();


  outFile.write(reinterpret_cast<const char*>(&rotation.x), sizeof(rotation));
  outFile.write(reinterpret_cast<const char*>(&translation.x), sizeof(translation));
  outFile.write(reinterpret_cast<const char*>(&windowPosition.x), sizeof(windowPosition));
  outFile.write(reinterpret_cast<const char*>(&windowDimensions.x), sizeof(windowDimensions));

  outFile.close();
}

void ExaminerControllerApp::onPostDraw()
{
  m_screenshot.saveToClipboardIfTriggered();
}

}
}
