#include <cogra/io/CubicBezierPatchLoader.h>
#include <string>
#include <fstream>
#include <sstream>
namespace
{

static bool equal(std::string a, std::string b)
{
  return (!a.compare(b));
}

}

namespace cogra
{
namespace io
{
namespace CubicBezierPatchLoader
{
std::vector<f32vec4> fromRib4(const char * fileName)
{
  std::vector<f32vec4> patches;

  std::ifstream ribFile(fileName);
  if(ribFile.fail())
  {
    return patches;
  }

  std::string line;

  while(ribFile.good() && getline(ribFile, line))
  {
    if(line.size() >= 1 && line[0] == '#')
    {
      // cout << "  ignoring comment: " << line << endl;
    }
    else
    {
      std::istringstream ss(line);
      std::string token;
      while(ss >> token)
      {
        if(equal("Patch", token) && (ss >> token))
        {
          if(equal("\"bicubic\"", token))
          {
            for(int cp_v = 0; cp_v < 4; cp_v++)
            {
              for(int cp_u = 0; cp_u < 4; cp_u++)
              {
                f32vec4 v;

                ribFile >> v.x >> v.y >> v.z;
                v.w = 1.0;
                patches.push_back(v);
              }
            }
          }
        }
      }
    }
  }
  return patches;
}

std::vector<f32vec4> fromText(const char * fileName)
{
  std::vector<f32vec4> patches;

  FILE* fp = NULL;
  fp = fopen(fileName, "r");
  if(fp == NULL)
  {
    return patches;
  }
  int32 nPatches;
  fscanf(fp, "%d", &nPatches);
  for(int32 i = 0; i < nPatches; i++)
  {
    for(int32 cp_v = 0; cp_v < 4; cp_v++)
    {
      for(int32 cp_u = 0; cp_u < 4; cp_u++)
      {
        f32vec4 v;
        fscanf(fp, "%f %f %f %f\n", &v.x, &v.y, &v.z, &v.w);
        patches.emplace_back(v);
      }
    }
  }
  fclose(fp);
  return patches;
}
}
}
}
