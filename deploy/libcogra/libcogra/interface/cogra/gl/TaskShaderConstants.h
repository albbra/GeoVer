#pragma once
#ifndef COGRA_GLTASKSHADERCONSTANTS_H
#define COGRA_GLTASKSHADERCONSTANTS_H
#include <cogra/types.h>
namespace cogra
{
namespace gl
{
struct TaskShaderConstants
{
  TaskShaderConstants();
  int32 maxUniformBlocks;
  int32 maxTextureImageUnits;
  int32 maxImageUniforms;
  int32 maxUniformComponents;
  int32 maxAtomicCounterBuffers;
  int32 maxAtomicCounters;
  int32 maxShaderStorageBlocks;
  int32 maxWorkGroupInvocations;
  int32 maxTotalMemorySize;
  int32 maxOutputCount;
  int32 combinedUniformComponents;
  int32 maxWorkGroupSize[3];
};
}
}
#endif