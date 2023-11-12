#pragma once
#ifndef COGRA_UI_BLINNPHONGWIDGET
#define COGRA_UI_BLINNPHONGWIDGET
#include <cogra/types.h>
namespace cogra
{
namespace ui
{
class BlinnPhongWidget
{
public:
  BlinnPhongWidget();

  void drawUI();

  f32vec3 getLightDirection() const;

  f32vec3 getAmbientColor() const;

  f32vec3 getDiffuseColor() const;

  f32vec3 getSpecularColor() const;

  float32 getSpecularExponent() const;

  void setAmbientColor(f32vec3 ambientColor);

  void setDiffuseColor(f32vec3 diffuseColor);

  void setSpecularColor(f32vec3 specularColor);

  void setSpecularExponent(float32 specularExponent);

private:
  f32vec3  ambientLightColor = { 0.0f, 0.0f, 0.0f };
  f32vec3  lightColor = { 1.0f, 1.0f, 1.0f };

  f32vec3  ambientMaterialColor = { 0.0f, 0.0f, 0.0f };
  f32vec3  diffuseMaterialColor = { 1.0f, 0.0f, 0.0f };
  f32vec3  specularMaterialColor = { 1.0f, 1.0f, 1.0f };
  float32  specularExponent = 256.0f;


  float32  lightSourceTheta = 0.0f;
  float32  lightSourcePhi = 0.0f;

};
}
}
#endif