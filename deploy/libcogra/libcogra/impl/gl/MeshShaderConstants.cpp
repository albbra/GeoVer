#include <cogra/gl/MeshShaderConstants.h>
#include <cogra/gl/OpenGLRuntimeError.h>
namespace cogra
{
namespace gl
{
MeshShaderConstants::MeshShaderConstants()
{
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_UNIFORM_BLOCKS_NV, &maxUniformBlocks));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_TEXTURE_IMAGE_UNITS_NV, &maxTextureImageUnits));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_IMAGE_UNIFORMS_NV, &maxImageUniforms));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_UNIFORM_COMPONENTS_NV, &maxUniformComponents));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_ATOMIC_COUNTER_BUFFERS_NV, &maxAtomicCounterBuffers));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_ATOMIC_COUNTERS_NV, &maxAtomicCounters));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_SHADER_STORAGE_BLOCKS_NV, &maxShaderStorageBlocks));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_WORK_GROUP_INVOCATIONS_NV, &maxWorkGroupInvocations));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_TOTAL_MEMORY_SIZE_NV, &maxTotalMemorySize));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_OUTPUT_VERTICES_NV, &maxOutputVertices));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_OUTPUT_PRIMITIVES_NV, &maxOutputPrimitives));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_DRAW_MESH_TASKS_COUNT_NV, &maxDrawTasksCount));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_MESH_VIEWS_NV, &maxViews));
  GL_SAFE_CALL(glGetIntegerv(GL_MESH_OUTPUT_PER_VERTEX_GRANULARITY_NV, &outputPerVertexGranularity));
  GL_SAFE_CALL(glGetIntegerv(GL_MESH_OUTPUT_PER_PRIMITIVE_GRANULARITY_NV, &outputPerPrimitiveGranularity));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_COMBINED_MESH_UNIFORM_COMPONENTS_NV, &combinedUniformComponents));

  GL_SAFE_CALL(glGetIntegeri_v(GL_MAX_MESH_WORK_GROUP_SIZE_NV, 0, &maxWorkGroupSize[0]));
  GL_SAFE_CALL(glGetIntegeri_v(GL_MAX_MESH_WORK_GROUP_SIZE_NV, 1, &maxWorkGroupSize[1]));
  GL_SAFE_CALL(glGetIntegeri_v(GL_MAX_MESH_WORK_GROUP_SIZE_NV, 2, &maxWorkGroupSize[2]));
}
}
}