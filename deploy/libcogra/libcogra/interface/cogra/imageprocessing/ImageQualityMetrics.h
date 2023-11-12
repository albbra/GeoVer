#pragma once
#include <cogra/types.h>
#include <limits>
namespace cogra::imageprocessing
{
struct ImageQualityMetrics
{
public:

  ImageQualityMetrics(ui8vec3 const * const a, ui8vec3 const * const b, size_t length)
  {
    float64 accu(0);
    m_maxError = ui8vec3(std::numeric_limits<uint8>::min());
    for(size_t i = 0; i < length; i++)
    {
      const auto diff = f64vec3(a[i]) - f64vec3(b[i]);
      accu += glm::dot(diff, diff);
      m_maxError = glm::max(ui8vec3(glm::abs(diff)), m_maxError);
    }
    m_meanSquaredError = accu / (length * 3);
  }

  ImageQualityMetrics(ui8vec3 const * const a, ui8vec3 const * const b, uint8 const * const mask, size_t length)
  {
    float64 accu(0);
    m_maxError = ui8vec3(std::numeric_limits<uint8>::min());
    for(size_t i = 0; i < length; i++)
    {
      if(mask[i] != 0)
      {
        const auto diff = f64vec3(a[i]) - f64vec3(b[i]);
        accu += glm::dot(diff, diff);
        m_maxError = glm::max(ui8vec3(glm::abs(diff)), m_maxError);
      }
    }
    m_meanSquaredError = accu / (length * 3);
  }

  float64 getMeanSquaredError() const
  {
    return m_meanSquaredError;
  }

  float64 getRootMeanSquareError() const
  {
    return sqrt(m_meanSquaredError);
  }

  float64 getPSNR() const
  {
    return 20.0 * log10(255.0) - 10.0 * log10(m_meanSquaredError);
  }

  ui8vec3 getMaxError() const
  {
    return m_maxError;
  }

  static float64 meanSquaredError(ui8vec3 const * const a, ui8vec3 const * const b, size_t length)
  {
    float64 accu(0);
    for(size_t i = 0; i < length; i++)
    {
      const auto diff = f64vec3(a[i]) - f64vec3(b[i]);
      accu += glm::dot(diff, diff);
    }
    return (accu / (length * 3));
  }

  static ui8vec3 maxError(ui8vec3 const * const a, ui8vec3 const * const b, size_t length)
  {
    ui8vec3 m(std::numeric_limits<uint8>::min());
    for(size_t i = 0; i < length; i++)
    {
      const auto diff = ui8vec3(a[i].x > b[i].x ? a[i].x - b[i].x : b[i].x - a[i].x,
                                a[i].y > b[i].y ? a[i].y - b[i].y : b[i].y - a[i].y,
                                a[i].z > b[i].z ? a[i].z - b[i].z : b[i].z - a[i].z);
      m = glm::max(diff, m);
    }
    return m;
  }

  static float64 peakSignalToNoiseRatio(ui8vec3 const * const a, ui8vec3 const * const b, size_t length)
  {
    return 20.0 * log10(255.0) - 10.0 * log10(meanSquaredError(a, b, length));
  }

private:
  float64 m_meanSquaredError;
  ui8vec3 m_maxError;
};



}