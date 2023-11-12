/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017-2018 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <iostream>
#include <glad/glad.h>

#include <cogra/gl/GLSLProgram.h>
#include <glm/gtc/type_ptr.hpp>
#include <cogra/gl/Texture.h>
#include <cogra/gl/Sampler.h>
namespace cogra
{
namespace gl
{
GLSLProgram::GLSLProgram()
  :m_programHandle(0)
{
  createProgram();
}


GLSLProgram::GLSLProgram(GLSLProgram&& other)
{
  m_programHandle = other.m_programHandle;
  m_uniform = std::move(other.m_uniform);
  other.m_programHandle = 0;
}

GLSLProgram& GLSLProgram::operator=(GLSLProgram&& other)
{
  m_programHandle = other.m_programHandle;
  m_uniform = std::move(other.m_uniform);
  other.m_programHandle = 0;
  return *this;
}

GLSLProgram::~GLSLProgram()
{
  if(m_programHandle != 0)
  {
    glDeleteProgram(m_programHandle);
  }
}

GLSLProgram::GLSLProgram(const std::string & pathComputeShader)
  : m_programHandle(0)
{
  createProgram();
  prepareShader<GL_COMPUTE_SHADER>(pathComputeShader);
  linkProgram();
}


GLSLProgram::GLSLProgram(const std::string& pathVertexShader, const std::string& pathFragmentShader)
  : m_programHandle(0)
{
  createProgram();
  prepareShader<GL_VERTEX_SHADER>(pathVertexShader);
  prepareShader<GL_FRAGMENT_SHADER>(pathFragmentShader);
  linkProgram();
}

GLSLProgram::GLSLProgram(const std::string& pathVertexShader, const std::string& pathGeometryShader,
                         const std::string& pathFragmentShader)
  : m_programHandle(0)
{
  createProgram();
  prepareShader<GL_VERTEX_SHADER>(pathVertexShader);
  prepareShader<GL_GEOMETRY_SHADER>(pathGeometryShader);
  prepareShader<GL_FRAGMENT_SHADER>(pathFragmentShader);
  linkProgram();
}

GLSLProgram::GLSLProgram(const std::string& pathVertexShader, const std::string& pathControlShader,
                         const std::string& pathEvaluationShader, const std::string& pathFragmentShader)
  : m_programHandle(0)
{
  createProgram();
  prepareShader<GL_VERTEX_SHADER>(pathVertexShader);
  prepareShader<GL_TESS_CONTROL_SHADER>(pathControlShader);
  prepareShader<GL_TESS_EVALUATION_SHADER>(pathEvaluationShader);
  prepareShader<GL_FRAGMENT_SHADER>(pathFragmentShader);
  linkProgram();
}

GLSLProgram::GLSLProgram(const std::string& pathVertexShader, const std::string& pathControlShader,
                         const std::string& pathEvaluationShader, const std::string& pathGeometryShader,
                         const std::string& pathFragmentShader)
  : m_programHandle(0)
{
  createProgram();
  prepareShader<GL_VERTEX_SHADER>(pathVertexShader);
  prepareShader<GL_TESS_CONTROL_SHADER>(pathControlShader);
  prepareShader<GL_TESS_EVALUATION_SHADER>(pathEvaluationShader);
  prepareShader<GL_GEOMETRY_SHADER>(pathGeometryShader);
  prepareShader<GL_FRAGMENT_SHADER>(pathFragmentShader);
  linkProgram();
}

GLSLProgram::GLSLProgram(const std::string& pathVertexShader, std::vector<const GLchar*>& varyings,
                         GLenum bufferMode)
  : m_programHandle(0)
{
  createProgram();
  prepareShader<GL_VERTEX_SHADER>(pathVertexShader);
  linkProgram(varyings, bufferMode);
}

GLSLProgram::GLSLProgram(const std::string& pathVertexShader, const std::string& pathFragmentShader,
                         std::vector<const GLchar*>& varyings, GLenum bufferMode)
  : m_programHandle(0)
{
  createProgram();
  prepareShader<GL_VERTEX_SHADER>(pathVertexShader);
  prepareShader<GL_FRAGMENT_SHADER>(pathFragmentShader);
  linkProgram(varyings, bufferMode);
}

GLSLProgram::GLSLProgram(const std::string& pathVertexShader, const std::string& pathGeometryShader, const std::string& pathFragmentShader, std::vector<const GLchar*>& varyings, GLenum bufferMode)
  : m_programHandle(0)
{
  createProgram();
  prepareShader<GL_VERTEX_SHADER>(pathVertexShader);
  prepareShader<GL_GEOMETRY_SHADER>(pathGeometryShader);
  prepareShader<GL_FRAGMENT_SHADER>(pathFragmentShader);
  linkProgram(varyings, bufferMode);
}

GLSLProgram::GLSLProgram(const std::string& pathVertexShader, const std::string& pathControlShader, const std::string& pathEvaluationShader, const std::string& pathFragmentShader, std::vector<const GLchar*>& varyings, GLenum bufferMode)
  : m_programHandle(0)
{
  createProgram();
  prepareShader<GL_VERTEX_SHADER>(pathVertexShader);
  prepareShader<GL_TESS_CONTROL_SHADER>(pathControlShader);
  prepareShader<GL_TESS_EVALUATION_SHADER>(pathEvaluationShader);
  prepareShader<GL_FRAGMENT_SHADER>(pathFragmentShader);
  linkProgram(varyings, bufferMode);
}

GLSLProgram::GLSLProgram(const std::string& pathVertexShader, const std::string& pathControlShader, const std::string& pathEvaluationShader, const std::string& pathGeometryShader, const std::string& pathFragmentShader, std::vector<const GLchar*>& varyings, GLenum bufferMode)
  : m_programHandle(0)
{
  createProgram();
  prepareShader<GL_VERTEX_SHADER>(pathVertexShader);
  prepareShader<GL_TESS_CONTROL_SHADER>(pathControlShader);
  prepareShader<GL_TESS_EVALUATION_SHADER>(pathEvaluationShader);
  prepareShader<GL_GEOMETRY_SHADER>(pathGeometryShader);
  prepareShader<GL_FRAGMENT_SHADER>(pathFragmentShader);
  linkProgram(varyings, bufferMode);
}

GLSLProgram GLSLProgram::createComputeFromSource(const std::string& computeShaderSource) {
	GLSLProgram program;
	if (!computeShaderSource.empty())
	{
		GLSLComputerShader vs(computeShaderSource, GLSLComputerShader::ShaderSourceCodeFromString);
		program.attachShader(vs.getHandle());
	}
	program.linkProgram();
	return program;
}

GLSLProgram GLSLProgram::createFromSource(const std::string& vertexShaderSource,
                                          const std::string& controlShaderSource, const std::string& evaluationShaderSource,
                                          const std::string& geometryShaderSource, const std::string& fragmentShaderSource)
{
  GLSLProgram program;
  if(!vertexShaderSource.empty())
  {
    GLSLVertexShader vs(vertexShaderSource, GLSLVertexShader::ShaderSourceCodeFromString);
    program.attachShader(vs.getHandle());
  }

  if(!controlShaderSource.empty())
  {
    GLSLTessellationControlShader cs(controlShaderSource, GLSLTessellationControlShader::ShaderSourceCodeFromString);
    program.attachShader(cs.getHandle());
  }

  if(!evaluationShaderSource.empty())
  {
    GLSLTessellationEvaluationShader es(evaluationShaderSource, GLSLTessellationEvaluationShader::ShaderSourceCodeFromString);
    program.attachShader(es.getHandle());
  }

  if(!geometryShaderSource.empty())
  {
    GLSLGeometryShader gs(geometryShaderSource, GLSLGeometryShader::ShaderSourceCodeFromString);
    program.attachShader(gs.getHandle());
  }

  if(!fragmentShaderSource.empty())
  {
    GLSLFragmentShader fs(fragmentShaderSource, GLSLFragmentShader::ShaderSourceCodeFromString);
    program.attachShader(fs.getHandle());
  }

  program.linkProgram();
  return program;
}

GLSLProgram GLSLProgram::createFromSource(const std::string& computeShaderSource)
{
    GLSLProgram program;

    if (!computeShaderSource.empty()) {
        GLSLComputerShader cs(computeShaderSource, GLSLComputerShader::ShaderSourceCodeFromString);
        program.attachShader(cs.getHandle());
    }
    program.linkProgram();
    return program;
}

GLSLProgram GLSLProgram::createFromBinary(const std::string& vertexShaderSource,
                                          const std::string& controlShaderSource, const std::string& evaluationShaderSource,
                                          const std::string& geometryShaderSource, const std::string& fragmentShaderSource)
{
  GLSLProgram program;
  if(!vertexShaderSource.empty())
  {
    GLSLVertexShader vs(vertexShaderSource, GLSLVertexShader::ShaderSourceCodeBinary);
    program.attachShader(vs.getHandle());
  }

  if(!controlShaderSource.empty())
  {
    GLSLTessellationControlShader cs(controlShaderSource, GLSLTessellationControlShader::ShaderSourceCodeBinary);
    program.attachShader(cs.getHandle());
  }

  if(!evaluationShaderSource.empty())
  {
    GLSLTessellationEvaluationShader es(evaluationShaderSource, GLSLTessellationEvaluationShader::ShaderSourceCodeBinary);
    program.attachShader(es.getHandle());
  }

  if(!geometryShaderSource.empty())
  {
    GLSLGeometryShader gs(geometryShaderSource, GLSLGeometryShader::ShaderSourceCodeBinary);
    program.attachShader(gs.getHandle());
  }

  if(!fragmentShaderSource.empty())
  {
    GLSLFragmentShader fs(fragmentShaderSource, GLSLFragmentShader::ShaderSourceCodeBinary);
    program.attachShader(fs.getHandle());
  }

  program.linkProgram();
  return program;
}

GLSLProgram GLSLProgram::createMeshFragmentFromSourceFile(const std::string & pathToMeshShader, const std::string & pathToFragmentShader)
{
  GLSLProgram program;

  if(!pathToMeshShader.empty())
  {
    GLSLMeshShader ts(pathToMeshShader, GLSLMeshShader::ShaderSourceCodeFromFile);
    program.attachShader(ts.getHandle());
  }
  if(!pathToFragmentShader.empty())
  {
    GLSLFragmentShader ts(pathToFragmentShader, GLSLFragmentShader::ShaderSourceCodeFromFile);
    program.attachShader(ts.getHandle());
  }
  program.linkProgram();
  return program;

}


GLSLProgram GLSLProgram::createTaskMeshFragmentFromSourceFile(const std::string & pathToTaskShader, const std::string & pathToMeshShader, const std::string & pathToFragmentShader)
{
  GLSLProgram program;
  if(!pathToTaskShader.empty())
  {
    GLSLTaskShader ts(pathToTaskShader, GLSLTaskShader::ShaderSourceCodeFromFile);
    program.attachShader(ts.getHandle());
  }
  if(!pathToMeshShader.empty())
  {
    GLSLMeshShader ts(pathToMeshShader, GLSLMeshShader::ShaderSourceCodeFromFile);
    program.attachShader(ts.getHandle());
  }
  if(!pathToFragmentShader.empty())
  {
    GLSLFragmentShader ts(pathToFragmentShader, GLSLFragmentShader::ShaderSourceCodeFromFile);
    program.attachShader(ts.getHandle());
  }
  program.linkProgram();
  return program;

}

GLint GLSLProgram::getAttributeLocation(const char * name) const
{
  GLint result;
  GL_SAFE_CALL(result = glGetAttribLocation(m_programHandle, name));
  return result;
}

//! \brief Returns a vector of all uniforms used in the program.
void GLSLProgram::createUniformMap()
{
  std::vector<std::string> result;
  GLint numberOfUniforms;
  GL_SAFE_CALL(glGetProgramiv(m_programHandle, GL_ACTIVE_UNIFORMS, &numberOfUniforms));
  if(numberOfUniforms == 0)
  {
    return;
  }
  GLint uniformMaxLength;
  GL_SAFE_CALL(glGetProgramiv(m_programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxLength));
  if(uniformMaxLength == 0)
  {
    return;
  }
  uniformMaxLength *= 2;


  auto name = new GLchar[uniformMaxLength];
  for(GLint aIdx = 0; aIdx < numberOfUniforms; aIdx++)
  {
    GLsizei length;
    GLint size;
    GLenum type;

    GL_SAFE_CALL(glGetActiveUniform(m_programHandle, static_cast<GLuint>(aIdx), uniformMaxLength, &length, &size, &type, name));

    UniformInfo ui;
    GL_SAFE_CALL(ui.location = glGetUniformLocation(m_programHandle, name));
    ui.size = size;
    ui.type = type;
    m_uniform.insert(std::make_pair(name, ui));
    result.emplace_back(name);
  }
  delete[] name;
}

void GLSLProgram::linkProgram()
{
  GLint linked;
  GL_SAFE_CALL(glLinkProgram(m_programHandle));
  GL_SAFE_CALL(glGetProgramiv(m_programHandle, GL_LINK_STATUS, &linked));
  if(linked == GL_FALSE)
  {
    throw GLSLRuntimeError("Error linking shaders\n" + getInfoLog());
  }
  createUniformMap();
}

void GLSLProgram::linkProgram(std::vector<const GLchar*>& varyings, const GLenum bufferMode)
{
  GL_SAFE_CALL(glTransformFeedbackVaryings(m_programHandle, static_cast<GLsizei>(varyings.size()), &(varyings[0]), bufferMode));
  linkProgram();
}




std::string GLSLProgram::getInfoLog() const
{
  GLint infologLength = 0;
  glGetProgramiv(m_programHandle, GL_INFO_LOG_LENGTH, &infologLength);
  if(infologLength > 0)
  {
    auto * infoLog = new GLchar[infologLength];
    GLsizei charsWritten = 0;
    glGetProgramInfoLog(m_programHandle, infologLength, &charsWritten, infoLog);
    std::string result(infoLog);
    delete[] infoLog;
    return result;
  }
  else
  {
    return std::string("");
  }
}

void GLSLProgram::use() const
{
  GL_SAFE_CALL(glUseProgram(m_programHandle));
}

GLint GLSLProgram::getUniformLocation(const GLchar *name) const
{
  std::unordered_map<std::string, UniformInfo>::const_iterator i = m_uniform.find(name);
  if(i != m_uniform.end())
  {
    return i->second.location;
  }
  else
  {
    GLint loc;
    UniformInfo ui;

    GL_SAFE_CALL(loc = glGetUniformLocation(m_programHandle, name));
    ui.location = loc;
    if(loc != -1)
    {
      GLsizei length;
      GLchar n[32768];
      GL_SAFE_CALL(glGetActiveUniform(m_programHandle, static_cast<GLuint>(loc), 32768, &length, &ui.size, &ui.type, n));
    }
    else
    {
      ui.size = 0;
      ui.type = 0;
    }
    m_uniform.insert(std::make_pair(name, ui));
    return loc;
  }
}

GLuint GLSLProgram::getUniformBlockIndex(const GLchar* name) const
{
  GLuint index;
  GL_SAFE_CALL(index = glGetUniformBlockIndex(m_programHandle, name));
  return index;
}

bool GLSLProgram::bindUniformBlock(const GLchar* name, GLuint bufferObject, GLuint bindingPoint)
{
  GLuint index = getUniformBlockIndex(name);
  if(index != GL_INVALID_INDEX)
  {
    GL_SAFE_CALL(glBindBuffer(GL_UNIFORM_BUFFER, bufferObject));
    GL_SAFE_CALL(glUniformBlockBinding(m_programHandle, index, bindingPoint));
    GL_SAFE_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, bufferObject));
    return true;
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::doesUniformExist(const GLchar* name) const
{
  return getUniformLocation(name) != -1;
}

bool GLSLProgram::setUniform(const char* name, const glm::mat2& a, bool transposed/*=false*/) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_FLOAT_MAT2)
    {
      GL_SAFE_CALL(glUniformMatrix2fv(loc, 1, static_cast<GLboolean>(transposed), glm::value_ptr(a)));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " +
                             glslTypeToString(GL_FLOAT_MAT3) + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const glm::mat3& a, bool transposed/*=false*/) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_FLOAT_MAT3)
    {
      GL_SAFE_CALL(glUniformMatrix3fv(loc, 1, static_cast<GLboolean>(transposed), glm::value_ptr(a)));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " +
                             glslTypeToString(GL_FLOAT_MAT3) + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const glm::mat4& a, bool transposed/*=false*/) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_FLOAT_MAT4)
    {
      GL_SAFE_CALL(glUniformMatrix4fv(loc, 1, static_cast<GLboolean>(transposed), glm::value_ptr(a)));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " +
                             glslTypeToString(GL_FLOAT_MAT4) + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const GLfloat a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_FLOAT)
    {
      GL_SAFE_CALL(glUniform1f(loc, a));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " + glslTypeToString(GL_FLOAT)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const f32vec2& a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_FLOAT_VEC2)
    {
      GL_SAFE_CALL(glUniform2f(loc, a.x, a.y));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " + glslTypeToString(GL_FLOAT_VEC2)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const f32vec3& a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_FLOAT_VEC3)
    {
      GL_SAFE_CALL(glUniform3f(loc, a.x, a.y, a.z));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " + glslTypeToString(GL_FLOAT_VEC3)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const f32vec4& a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_FLOAT_VEC4)
    {
      GL_SAFE_CALL(glUniform4f(loc, a.x, a.y, a.z, a.w));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " + glslTypeToString(GL_FLOAT_VEC4)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const GLint a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_INT ||
       m_uniform[name].type == GL_SAMPLER_2D ||
       m_uniform[name].type == GL_SAMPLER_CUBE ||
       m_uniform[name].type == GL_UNSIGNED_INT_SAMPLER_2D ||
       m_uniform[name].type == GL_INT_SAMPLER_2D ||
       m_uniform[name].type == GL_UNSIGNED_INT_SAMPLER_BUFFER ||
       m_uniform[name].type == GL_SAMPLER_BUFFER)
    {
      GL_SAFE_CALL(glUniform1i(loc, a));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " + glslTypeToString(GL_INT)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const GLuint a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_UNSIGNED_INT ||
       m_uniform[name].type == GL_SAMPLER_2D ||
       m_uniform[name].type == GL_SAMPLER_CUBE ||
       m_uniform[name].type == GL_UNSIGNED_INT_SAMPLER_2D ||
       m_uniform[name].type == GL_INT_SAMPLER_2D ||
       m_uniform[name].type == GL_UNSIGNED_INT_SAMPLER_BUFFER ||
       m_uniform[name].type == GL_SAMPLER_BUFFER)
    {
      GL_SAFE_CALL(glUniform1ui(loc, a));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " + glslTypeToString(GL_UNSIGNED_INT)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const glm::uvec2& a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_UNSIGNED_INT_VEC2)
    {
      GL_SAFE_CALL(glUniform2ui(loc, a.x, a.y));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " + glslTypeToString(GL_UNSIGNED_INT_VEC2)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const bool a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_BOOL)
    {
      GL_SAFE_CALL(glUniform1i(loc, a == true ? 1 : 0));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " + glslTypeToString(GL_UNSIGNED_INT_VEC2)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const Texture& texture) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(
      m_uniform[name].type == GL_UNSIGNED_INT_SAMPLER_1D ||
      m_uniform[name].type == GL_INT_SAMPLER_1D ||
      m_uniform[name].type == GL_SAMPLER_1D ||
      m_uniform[name].type == GL_SAMPLER_2D ||
      m_uniform[name].type == GL_SAMPLER_3D ||
      m_uniform[name].type == GL_SAMPLER_CUBE ||
      m_uniform[name].type == GL_UNSIGNED_INT_SAMPLER_2D ||
      m_uniform[name].type == GL_INT_SAMPLER_2D ||
      m_uniform[name].type == GL_UNSIGNED_INT_SAMPLER_BUFFER ||
      m_uniform[name].type == GL_INT_SAMPLER_BUFFER ||
      m_uniform[name].type == GL_SAMPLER_BUFFER)
    {
      GL_SAFE_CALL(glUniform1i(loc, texture.getUnit()));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " + glslTypeToString(GL_INT)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char* name, const Sampler& sampler) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(
      m_uniform[name].type == GL_SAMPLER_2D ||
      m_uniform[name].type == GL_SAMPLER_3D ||
      m_uniform[name].type == GL_SAMPLER_CUBE ||
      m_uniform[name].type == GL_UNSIGNED_INT_SAMPLER_2D ||
      m_uniform[name].type == GL_INT_SAMPLER_2D ||
      m_uniform[name].type == GL_UNSIGNED_INT_SAMPLER_BUFFER ||
      m_uniform[name].type == GL_SAMPLER_BUFFER)
    {
      GL_SAFE_CALL(glUniform1i(loc, sampler.getUnit()));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + ", but retrieved " + glslTypeToString(GL_INT)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char * name, const std::vector<float32>& a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_FLOAT)
    {
      GL_SAFE_CALL(glUniform1fv(loc, static_cast<GLsizei>(a.size()), a.data()));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + "[], but retrieved " + glslTypeToString(GL_FLOAT)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char * name, const std::vector<uint32>& a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_UNSIGNED_INT)
    {
      GL_SAFE_CALL(glUniform1uiv(loc, static_cast<GLsizei>(a.size()), a.data()));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + "[], but retrieved " + glslTypeToString(GL_FLOAT)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}

bool GLSLProgram::setUniform(const char * name, const std::vector<f32vec2>& a) const
{
  GLint loc = getUniformLocation(name);
  if(loc != -1)
  {
    if(m_uniform[name].type == GL_FLOAT_VEC2)
    {
      GL_SAFE_CALL(glUniform2fv(loc, static_cast<GLsizei>(a.size()), reinterpret_cast<GLfloat const* const>(a.data())));
      return true;
    }
    else
    {
      throw GLSLRuntimeError("Passing wrong type to uniform variable \"" + std::string(name) +
                             "\". Expected " + glslTypeToString(m_uniform[name].type) + "[], but retrieved " + glslTypeToString(GL_FLOAT)
                             + ".");
    }
  }
  else
  {
    return false;
  }
}



const char* GLSLProgram::glslTypeToString(GLenum type)
{
  switch(type)
  {
    case GL_FLOAT: return "float";
    case GL_FLOAT_VEC2: return "vec2";
    case GL_FLOAT_VEC3: return "vec3";
    case GL_FLOAT_VEC4: return "vec4";
    case GL_DOUBLE: return "double";
    case GL_DOUBLE_VEC2: return "dvec2";
    case GL_DOUBLE_VEC3: return "dvec3";
    case GL_DOUBLE_VEC4: return "dvec4";
    case GL_INT: return "int";
    case GL_INT_VEC2: return "ivec2";
    case GL_INT_VEC3: return "ivec3";
    case GL_INT_VEC4: return "ivec4";
    case GL_UNSIGNED_INT: return "unsigned int";
    case GL_UNSIGNED_INT_VEC2: return "uvec2";
    case GL_UNSIGNED_INT_VEC3: return "uvec3";
    case GL_UNSIGNED_INT_VEC4: return "uvec4";
    case GL_BOOL: return "bool";
    case GL_BOOL_VEC2: return "bvec2";
    case GL_BOOL_VEC3: return "bvec3";
    case GL_BOOL_VEC4: return "bvec4";
    case GL_FLOAT_MAT2: return "mat2";
    case GL_FLOAT_MAT3: return "mat3";
    case GL_FLOAT_MAT4: return "mat4";
    case GL_FLOAT_MAT2x3: return "mat2x3";
    case GL_FLOAT_MAT2x4: return "mat2x4";
    case GL_FLOAT_MAT3x2: return "mat3x2";
    case GL_FLOAT_MAT3x4: return "mat3x4";
    case GL_FLOAT_MAT4x2: return "mat4x2";
    case GL_FLOAT_MAT4x3: return "mat4x3";
    case GL_DOUBLE_MAT2: return "dmat2";
    case GL_DOUBLE_MAT3: return "dmat3";
    case GL_DOUBLE_MAT4: return "dmat4";
    case GL_DOUBLE_MAT2x3: return "dmat2x3";
    case GL_DOUBLE_MAT2x4: return "dmat2x4";
    case GL_DOUBLE_MAT3x2: return "dmat3x2";
    case GL_DOUBLE_MAT3x4: return "dmat3x4";
    case GL_DOUBLE_MAT4x2: return "dmat4x2";
    case GL_DOUBLE_MAT4x3: return "dmat4x3";
    case GL_SAMPLER_1D: return "sampler1D";
    case GL_SAMPLER_2D: return "sampler2D";
    case GL_SAMPLER_3D: return "sampler3D";
    case GL_SAMPLER_CUBE: return "samplerCube";
    case GL_SAMPLER_1D_SHADOW: return "sampler1DShadow";
    case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
    case GL_SAMPLER_1D_ARRAY: return "sampler1DArray";
    case GL_SAMPLER_2D_ARRAY: return "sampler2DArray";
    case GL_SAMPLER_1D_ARRAY_SHADOW: return "sampler1DArrayShadow";
    case GL_SAMPLER_2D_ARRAY_SHADOW: return "sampler2DArrayShadow";
    case GL_SAMPLER_2D_MULTISAMPLE: return "sampler2DMS";
    case GL_SAMPLER_2D_MULTISAMPLE_ARRAY: return "sampler2DMSArray";
    case GL_SAMPLER_CUBE_SHADOW: return "samplerCubeShadow";
    case GL_SAMPLER_BUFFER: return "samplerBuffer";
    case GL_SAMPLER_2D_RECT: return "sampler2DRect";
    case GL_SAMPLER_2D_RECT_SHADOW: return "sampler2DRectShadow";
    case GL_INT_SAMPLER_1D: return "isampler1D";
    case GL_INT_SAMPLER_2D: return "isampler2D";
    case GL_INT_SAMPLER_3D: return "isampler3D";
    case GL_INT_SAMPLER_CUBE: return "isamplerCube";
    case GL_INT_SAMPLER_1D_ARRAY: return "isampler1DArray";;
    case GL_INT_SAMPLER_2D_ARRAY: return "isampler2DArray";
    case GL_INT_SAMPLER_2D_MULTISAMPLE: return "isampler2DMS";
    case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY: return "isampler2DMSArray";
    case GL_INT_SAMPLER_BUFFER: return "isamplerBuffer";
    case GL_INT_SAMPLER_2D_RECT: return "isampler2DRect";
    case GL_UNSIGNED_INT_SAMPLER_1D: return "usampler1D";
    case GL_UNSIGNED_INT_SAMPLER_2D: return "usampler2D";
    case GL_UNSIGNED_INT_SAMPLER_3D: return "usampler3D";
    case GL_UNSIGNED_INT_SAMPLER_CUBE: return "usamplerCube";
    case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY: return "usampler2DArray";
    case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY: return "usampler2DArray";
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE: return "usampler2DMS";
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY: return "usampler2DMSArray";
    case GL_UNSIGNED_INT_SAMPLER_BUFFER: return "usamplerBuffer";
    case GL_UNSIGNED_INT_SAMPLER_2D_RECT: return "usampler2DRect";
    case GL_IMAGE_1D: return "image1D";
    case GL_IMAGE_2D: return "image2D";
    case GL_IMAGE_3D: return "image3D";
    case GL_IMAGE_2D_RECT: return "image2DRect";
    case GL_IMAGE_CUBE: return "imageCube";
    case GL_IMAGE_BUFFER: return "imageBuffer";
    case GL_IMAGE_1D_ARRAY: return "image1DArray";
    case GL_IMAGE_2D_ARRAY: return "image2DArray";
    case GL_IMAGE_2D_MULTISAMPLE: return "image2DMS";
    case GL_IMAGE_2D_MULTISAMPLE_ARRAY: return "image2DMSArray";
    case GL_INT_IMAGE_1D: return "iimage1D";
    case GL_INT_IMAGE_2D: return "iimage2D";
    case GL_INT_IMAGE_3D: return "iimage3D";
    case GL_INT_IMAGE_2D_RECT: return "iimage2DRect";
    case GL_INT_IMAGE_CUBE: return "iimageCube";
    case GL_INT_IMAGE_BUFFER: return "iimageBuffer";
    case GL_INT_IMAGE_1D_ARRAY: return "iimage1DArray";
    case GL_INT_IMAGE_2D_ARRAY: return "iimage2DArray";
    case GL_INT_IMAGE_2D_MULTISAMPLE: return "iimage2DMS";
    case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY: return "iimage2DMSArray";
    case GL_UNSIGNED_INT_IMAGE_1D: return "uimage1D";
    case GL_UNSIGNED_INT_IMAGE_2D: return "uimage2D";
    case GL_UNSIGNED_INT_IMAGE_3D: return "uimage3D";
    case GL_UNSIGNED_INT_IMAGE_2D_RECT: return "uimage2DRect";
    case GL_UNSIGNED_INT_IMAGE_CUBE: return "uimageCube";
    case GL_UNSIGNED_INT_IMAGE_BUFFER: return "uimageBuffer";
    case GL_UNSIGNED_INT_IMAGE_1D_ARRAY: return "uimage1DArray";
    case GL_UNSIGNED_INT_IMAGE_2D_ARRAY: return "uimage2DArray";
    case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE: return "uimage2DMS";
    case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY: return "uimage2DMSArray";
    case GL_UNSIGNED_INT_ATOMIC_COUNTER: return "atomic_uint";
    default: return "unknown";
  }
}

void GLSLProgram::attachShader(GLuint shaderHandle) const
{
  GL_SAFE_CALL(glAttachShader(m_programHandle, shaderHandle));
}

void GLSLProgram::createProgram()
{
  GL_SAFE_CALL(m_programHandle = glCreateProgram());
}
}
}
