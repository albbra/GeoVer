#include <cogra/ui/BlinnPhongWidget.h>
#include <imgui/imgui.h>
namespace cogra
{
namespace ui
{
BlinnPhongWidget::BlinnPhongWidget()
{
}

void BlinnPhongWidget::drawUI()
{

  if(ImGui::CollapsingHeader("Light"))
  {
    ImGui::ColorEdit3("Ambient Light", glm::value_ptr(ambientLightColor));
    ImGui::ColorEdit3("Light Color", glm::value_ptr(lightColor));
    ImGui::Spacing();
    ImGui::SliderAngle("Light Theta", &lightSourceTheta, 0.0, 360.0f);
    ImGui::SliderAngle("Light Phi", &lightSourcePhi, 0.0, 360.0f);
  }
  ImGui::Spacing();
  if(ImGui::CollapsingHeader("Material"))
  {
    ImGui::ColorEdit3("Ambient Material", glm::value_ptr(ambientMaterialColor));
    ImGui::ColorEdit3("Diffuse Material", glm::value_ptr(diffuseMaterialColor));
    ImGui::ColorEdit3("Specular Material", glm::value_ptr(specularMaterialColor));
    ImGui::SliderFloat("Specular Exponent", &specularExponent, 0.0f, 1024.0f);
  }
}

f32vec3 BlinnPhongWidget::getLightDirection() const
{
  const auto sinPhi = glm::sin(lightSourcePhi);
  const auto cosPhi = glm::cos(lightSourcePhi);
  const auto sinTheta = glm::sin(lightSourceTheta);
  const auto cosTheta = glm::cos(lightSourceTheta);
  return f32vec3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta);
}

f32vec3 BlinnPhongWidget::getAmbientColor() const
{
  return ambientLightColor * ambientMaterialColor;
}

f32vec3 BlinnPhongWidget::getDiffuseColor() const
{
  return diffuseMaterialColor * lightColor;
}

f32vec3 BlinnPhongWidget::getSpecularColor() const
{
  return specularMaterialColor * lightColor;
}

float32 BlinnPhongWidget::getSpecularExponent() const
{
  return specularExponent;
}

void BlinnPhongWidget::setAmbientColor(f32vec3 ambientColor)
{
  ambientMaterialColor = ambientColor;
}

void BlinnPhongWidget::setDiffuseColor(f32vec3 diffuseColor)
{
  diffuseMaterialColor = diffuseColor;
}

void BlinnPhongWidget::setSpecularColor(f32vec3 specularColor)
{
  specularMaterialColor = specularColor;
}

void BlinnPhongWidget::setSpecularExponent(float32 specularExponent)
{
  this->specularExponent = specularExponent;
}

}
}