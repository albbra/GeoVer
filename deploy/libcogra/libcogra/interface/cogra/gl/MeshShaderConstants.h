#pragma once
#ifndef COGRA_GLMESHSHADERCONSTANTS_H
#define COGRA_GLMESHSHADERCONSTANTS_H
#include <cogra/types.h>
namespace cogra
{
namespace gl
{
/// <summary>
/// Reads the constant information related to Mesh-Shaders from the GL state and stores in member variables.
/// </summary>
struct MeshShaderConstants
{
  MeshShaderConstants();

  int32 maxUniformBlocks;
  int32 maxTextureImageUnits;
  int32 maxImageUniforms;
  int32 maxUniformComponents;
  int32 maxAtomicCounterBuffers;
  int32 maxAtomicCounters;
  int32 maxShaderStorageBlocks;
  int32 maxWorkGroupInvocations;
  int32 maxTotalMemorySize;
  int32 maxOutputVertices;
  int32 maxOutputPrimitives;
  int32 maxDrawTasksCount;
  int32 maxViews;
  int32 outputPerVertexGranularity;
  int32 outputPerPrimitiveGranularity;
  int32 combinedUniformComponents;
  int32 maxWorkGroupSize[3];
};
}
}
#endif