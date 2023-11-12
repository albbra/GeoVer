/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/ui/FirstPersonCamera.h>
namespace cogra
{
namespace ui
{
FirstPersonCamera::FirstPersonCamera()
  : m_position(0)
  , m_normalizedMouseCoordinates(0, 0)
  , m_updateRotation(false)
  , m_updatePositionUpDown(false)
{
  reset();
}

void FirstPersonCamera::setPosition(f32vec3 position)
{
  m_position = position;
}

void FirstPersonCamera::reset()
{

  m_position = f32vec4(0, 0, 0, 1);
  m_pitchRotation = glm::quatLookAt(f32vec3(0, 0, -1), f32vec3(0, 1, 0));
  m_yawRotation = glm::quatLookAt(f32vec3(0, 0, -1), f32vec3(0, 1, 0));
}

f32mat4 FirstPersonCamera::getTransformationMatrix() const
{
  return getRotationMatrix() * glm::translate(m_position);// glm::eulerAngleYXZ(m_yaw, m_pitch, 0.0f);
}

void FirstPersonCamera::mouseClick(bool pressed, int button, bool keyboardModifier, const f32vec2 & normalizedMouseCoordinates)
{
  if(button == 1 && pressed)
  {
    beginRotation(normalizedMouseCoordinates);
  }
  else
  {
    endRotation();
  }

  if(button == 2 && pressed)
  {
    beginMoveUpDown(normalizedMouseCoordinates);
  }
  else
  {
    endMoveUpDown();
  }
}

void FirstPersonCamera::mouseMove(const f32vec2 & normalizedMouseCoordinates)
{
  if(m_updateRotation)
  {
    updateRotation(normalizedMouseCoordinates);
  }
  if(m_updatePositionUpDown)
  {
    updatePositionUpDown(normalizedMouseCoordinates);
  }
  m_normalizedMouseCoordinates = normalizedMouseCoordinates;
}

void FirstPersonCamera::checkKey(bool upKey, bool downKey, bool leftKey, bool rightKey)
{
  const float deltaPos = 0.001f;
  if(leftKey)
  {
    moveLeftRight(deltaPos);
  }
  if(rightKey)
  {
    moveLeftRight(-deltaPos);
  }

  if(upKey)
  {
    moveForwardBackward(deltaPos);
  }
  if(downKey)
  {
    moveForwardBackward(-deltaPos);
  }
}

f32mat4 FirstPersonCamera::getRotationMatrix() const
{
  return glm::toMat4(m_pitchRotation * m_yawRotation);
}

void FirstPersonCamera::moveLeftRight(float32 deltaX)
{
  auto delta = glm::inverse(getRotationMatrix()) * f32vec4(deltaX, 0, 0, 1);
  m_position += f32vec3(delta.x, delta.y, delta.z);
}

void FirstPersonCamera::moveUpDown(float32 deltaY)
{
  auto delta = glm::inverse(getRotationMatrix()) * f32vec4(0, deltaY, 0, 1);
  m_position += f32vec3(delta.x, delta.y, delta.z);
}

void FirstPersonCamera::moveForwardBackward(float32 deltaZ)
{
  auto delta = glm::inverse(getRotationMatrix()) * f32vec4(0, 0, deltaZ, 1);
  m_position += f32vec3(delta.x, delta.y, delta.z);
}

void FirstPersonCamera::beginRotation(const f32vec2 & normalizedMouseCoordinates)
{
  m_normalizedMouseCoordinates = normalizedMouseCoordinates;
  m_updateRotation = true;
}

void FirstPersonCamera::endRotation()
{
  m_updateRotation = false;
}

void FirstPersonCamera::beginMoveUpDown(const f32vec2 & normalizedMouseCoordinates)
{
  m_updatePositionUpDown = true;
}

void FirstPersonCamera::endMoveUpDown()
{
  m_updatePositionUpDown = false;
}

void FirstPersonCamera::updateRotation(const f32vec2 & normalizedMouseCoordinates)
{
  if(normalizedMouseCoordinates.x == m_normalizedMouseCoordinates.x && normalizedMouseCoordinates.y == m_normalizedMouseCoordinates.y)
  {
    return;
  }

  auto delta = normalizedMouseCoordinates - m_normalizedMouseCoordinates;

  turnLeftRight(delta.x);
  turnUpDown(delta.y);
}

void FirstPersonCamera::updatePositionUpDown(const f32vec2 & normalizedMouseCoordinates)
{
  if(normalizedMouseCoordinates.x == m_normalizedMouseCoordinates.x && normalizedMouseCoordinates.y == m_normalizedMouseCoordinates.y)
  {
    return;
  }

  auto delta = normalizedMouseCoordinates - m_normalizedMouseCoordinates;

  moveUpDown(-delta.y);
}

void FirstPersonCamera::turnUpDown(float32 deltaPitchDegrees)
{
  m_pitchRotation = glm::angleAxis(deltaPitchDegrees, f32vec3(1, 0, 0)) * m_pitchRotation;
}

void FirstPersonCamera::turnLeftRight(float32 deltaYawDegrees)
{
  m_yawRotation = glm::angleAxis(deltaYawDegrees, f32vec3(0, 1, 0)) * m_yawRotation;
}
}
}