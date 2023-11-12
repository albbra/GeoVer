/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#pragma once
#ifndef COGRA_UI_FIRSTPERSONCAMERA_H
#define COGRA_UI_FIRSTPERSONCAMERA_H
#include <cogra/types.h>
namespace cogra
{
namespace ui
{
class FirstPersonCamera
{
public:
  FirstPersonCamera();

  void setPosition(f32vec3 position);

  void reset();

  f32mat4 getTransformationMatrix() const;

  //! \brief Controller Processing when the mouse button is pressed or released.
  //! \param  pressed	True, if a mouse button has just been clicked, false if it has just been released.
  //! \param  button	Which button is affected by the event. 1 for left, 2 for middle, 4 for right.
  //! \param  keyboardModifier True of a keyoard modifier key was pressed.
  //! \param  normalizedMouseCoordinates Mouse coordinates in the range [-1;1]^2            
  void mouseClick(bool pressed, int button, bool keyboardModifier, const f32vec2& normalizedMouseCoordinates);

  //! \brief Controller processing when the mouse button is moved.
  //!
  //! \param  normalizedMouseCoordinates Mouse coordinates in the range [-1;1]^2            
  void mouseMove(const f32vec2& normalizedMouseCoordinates);

  void checkKey(bool upKey, bool downKey, bool leftKey, bool rightKey);


private:

  f32mat4 getRotationMatrix() const;


  void moveLeftRight(float32 deltaX);

  void moveUpDown(float32 deltaY);

  void moveForwardBackward(float32 deltaZ);

  void beginRotation(const f32vec2& normalizedMouseCoordinates);

  void endRotation();

  void beginMoveUpDown(const f32vec2& normalizedMouseCoordinates);

  void endMoveUpDown();

  void updateRotation(const f32vec2& normalizedMouseCoordinates);

  void updatePositionUpDown(const f32vec2& normalizedMouseCoordinates);

  void turnUpDown(float32 deltaPitchDegrees);

  void turnLeftRight(float32 deltaYawDegrees);

private:

  glm::quat       m_pitchRotation;

  glm::quat       m_yawRotation;

  f32vec3         m_position;

  f32vec2         m_normalizedMouseCoordinates;

  bool            m_updateRotation;

  bool            m_updatePositionUpDown;

};
}
}

#endif