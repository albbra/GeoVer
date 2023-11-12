#pragma once
#include <cogra/types.h>
#include <vector>
namespace cogra::imageprocessing
{
struct ImageCompressionMetrics
{
  static f64vec3 computeEntroy(ui8vec3 const * const a, size_t length)
  {
    const size_t nBins = 256;
    std::vector<uint32> r(nBins);
    std::vector<uint32> g(nBins);
    std::vector<uint32> b(nBins);

    for(size_t i = 0; i < length; i++)
    {
      r[a[i].x]++;
      g[a[i].y]++;
      b[a[i].z]++;
    }
    f64vec3 entropy(0);
    for(size_t i = 0; i < nBins; i++)
    {
      f64vec3 p = f64vec3(static_cast<float64>(r[i]), static_cast<float64>(g[i]), static_cast<float64>(b[i])) / static_cast<float64>(length);
      f64vec3 logp = glm::log2(p);

      if(r[i] != 0)
      {
        entropy.x -= logp.x * p.x;
      }
      if(g[i] != 0)
      {
        entropy.y -= logp.y * p.y;
      }
      if(b[i] != 0)
      {
        entropy.z -= logp.z * p.z;
      }
    }
    return entropy;
  }

  static f64vec3 computeEntroy(ui16vec3 const * const a, size_t length)
  {
    const size_t nBins = 65536;
    std::vector<uint32> r(nBins);
    std::vector<uint32> g(nBins);
    std::vector<uint32> b(nBins);

    for(size_t i = 0; i < length; i++)
    {
      r[a[i].x]++;
      g[a[i].y]++;
      b[a[i].z]++;
    }
    f64vec3 entropy(0);
    for(size_t i = 0; i < nBins; i++)
    {
      f64vec3 p = f64vec3(static_cast<float64>(r[i]), static_cast<float64>(g[i]), static_cast<float64>(b[i])) / static_cast<float64>(length);
      f64vec3 logp = glm::log2(p);

      if(r[i] != 0)
      {
        entropy.x -= logp.x * p.x;
      }
      if(g[i] != 0)
      {
        entropy.y -= logp.y * p.y;
      }
      if(b[i] != 0)
      {
        entropy.z -= logp.z * p.z;
      }
    }
    return entropy;
  }
};
}