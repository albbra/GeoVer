#include <cogra/gl/TaskShaderConstants.h>
#include <cogra/gl/OpenGLRuntimeError.h>
namespace cogra
{
namespace gl
{
TaskShaderConstants::TaskShaderConstants()
{
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_TASK_UNIFORM_BLOCKS_NV, &maxUniformBlocks));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_TASK_TEXTURE_IMAGE_UNITS_NV, &maxTextureImageUnits));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_TASK_IMAGE_UNIFORMS_NV, &maxImageUniforms));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_TASK_UNIFORM_COMPONENTS_NV, &maxUniformComponents));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_TASK_ATOMIC_COUNTER_BUFFERS_NV, &maxAtomicCounterBuffers));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_TASK_ATOMIC_COUNTERS_NV, &maxAtomicCounters));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_TASK_SHADER_STORAGE_BLOCKS_NV, &maxShaderStorageBlocks));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_TASK_WORK_GROUP_INVOCATIONS_NV, &maxWorkGroupInvocations));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_TASK_TOTAL_MEMORY_SIZE_NV, &maxTotalMemorySize));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_TASK_OUTPUT_COUNT_NV, &maxOutputCount));
  GL_SAFE_CALL(glGetIntegerv(GL_MAX_COMBINED_TASK_UNIFORM_COMPONENTS_NV, &combinedUniformComponents));

  GL_SAFE_CALL(glGetIntegeri_v(GL_MAX_TASK_WORK_GROUP_SIZE_NV, 0, &maxWorkGroupSize[0]));
  GL_SAFE_CALL(glGetIntegeri_v(GL_MAX_TASK_WORK_GROUP_SIZE_NV, 1, &maxWorkGroupSize[1]));
  GL_SAFE_CALL(glGetIntegeri_v(GL_MAX_TASK_WORK_GROUP_SIZE_NV, 2, &maxWorkGroupSize[2]));
}
}
}