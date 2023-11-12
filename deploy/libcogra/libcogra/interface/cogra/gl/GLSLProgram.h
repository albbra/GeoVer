/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 - 2018 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_GLSLPROGRAM_H_
#define COGRA_GL_GLSLPROGRAM_H_
#include <cogra/types.h>
#include <glad/glad.h>
#include <vector>
#include <memory>

#include <cogra/gl/OpenGLRuntimeError.h>
#include <cogra/gl/GLSLShader.h>
#include <unordered_map>

using std::unique_ptr;
namespace cogra
{
namespace gl
{
class Texture;
class Sampler;

//! Class for shader programs.
class GLSLProgram
{
public:

  GLSLProgram();

  //! \brief Creates a GLSL program consisting of vertex and fragment shaders.
//! \param[in]  pathVertexShader Path to vertex shader.
//! \param[in]  pathFragmentShader Path to pixel shader.
  explicit GLSLProgram(const std::string& pathComputeShader);


  //! \brief Creates a GLSL program consisting of vertex and fragment shaders.
  //! \param[in]  pathVertexShader Path to vertex shader.
  //! \param[in]  pathFragmentShader Path to pixel shader.
  GLSLProgram(const std::string& pathVertexShader, const std::string& pathFragmentShader);

  //! \brief Creates a shader consisting of vertex, geometry, and fragment shaders.
  //!
  //! \param[in]  pathVertexShader Path to vertex shader.
  //! \param[in]  pathGeometryShader Path to geometry shader.
  //! \param[in]  pathFragmentShader Path to fragment shader.
  GLSLProgram(const std::string& pathVertexShader, const std::string& pathGeometryShader,
              const std::string& pathFragmentShader);

  //! \brief Creates a GLSL program consisting of vertex, tessellation, and fragment shaders.
  //! \param[in]  pathVertexShader Path to vertex shader.
  //! \param[in]  pathControlShader Path to tessellation control shader.
  //! \param[in]  pathEvaluationShader Path to tessellation evaluation shader.
  //! \param[in]  pathFragmentShader Path to fragment shader.
  GLSLProgram(const std::string& pathVertexShader, const std::string& pathControlShader,
              const std::string& pathEvaluationShader, const std::string& pathFragmentShader);

  //! \brief Creates a GLSL program consisting of vertex, tessellation, and fragment shaders.
  //! \param[in]  pathVertexShader Path to vertex shader.
  //! \param[in]  pathControlShader Path to tessellation control shader.
  //! \param[in]  pathEvaluationShader Path to tessellation evaluation shader.
  //! \param[in]  pathGeometryShader Path to geometry shader.
  //! \param[in]  pathFragmentShader Path to fragment shader.
  GLSLProgram(const std::string& pathVertexShader, const std::string& pathControlShader,
              const std::string& pathEvaluationShader, const std::string& pathGeometryShader,
              const std::string& pathFragmentShader);

  //! \brief Creates a transform-feedback shader.
  //! \param[in]  pathVertexShader Path to vertex shader.
  //! \param[in]  varyings An array of zero-terminated strings specifying the names of the varying variables to use
  //!             for transform feedback.
  //! \param[in]  bufferMode Identifies the mode used to capture the varying variables when transform feedback is
  //!             active. Must be GL_INTERLEAVED_ATTRIBS or GL_SEPARATE_ATTRIBS.
  GLSLProgram(const std::string& pathVertexShader, std::vector<const GLchar*>& varyings, GLenum bufferMode);

  //! \brief Creates a transform-feedback shader.
  //! \param[in]  pathVertexShader Path to vertex shader.
  //! \param[in]  pathFragmentShader Path to fragment shader.
  //! \param[in]  varyings An array of zero-terminated strings specifying the names of the varying variables to use
  //!             for transform feedback.
  //! \param[in]  bufferMode Identifies the mode used to capture the varying variables when transform feedback is
  //!             active. Must be GL_INTERLEAVED_ATTRIBS or GL_SEPARATE_ATTRIBS.
  GLSLProgram(const std::string& pathVertexShader, const std::string& pathFragmentShader,
              std::vector<const GLchar*>& varyings, GLenum bufferMode);

  //! \brief Creates a transform-feedback shader.
  //! \param[in]  pathVertexShader Path to vertex shader.
  //! \param[in]  pathGeometryShader Path to geometry shader.
  //! \param[in]  pathFragmentShader Path to fragment shader.
  //! \param[in]  varyings An array of zero-terminated strings specifying the names of the varying variables to use
  //!             for transform feedback.
  //! \param[in]  bufferMode Identifies the mode used to capture the varying variables when transform feedback is
  //!             active. Must be GL_INTERLEAVED_ATTRIBS or GL_SEPARATE_ATTRIBS.
  GLSLProgram(const std::string& pathVertexShader, const std::string& pathGeometryShader,
              const std::string& pathFragmentShader, std::vector<const GLchar*>& varyings, GLenum bufferMode);

  //! \brief Creates a transform-feedback shader.
  //! \param[in]  pathVertexShader Path to vertex shader.
  //! \param[in]  pathControlShader Path to tessellation control shader.
  //! \param[in]  pathEvaluationShader Path to tessellation evaluation shader.
  //! \param[in]  pathFragmentShader Path to fragment shader.
  //! \param[in]  varyings An array of zero-terminated strings specifying the names of the varying variables to use
  //!             for transform feedback.
  //! \param[in]  bufferMode Identifies the mode used to capture the varying variables when transform feedback is
  //!             active. Must be GL_INTERLEAVED_ATTRIBS or GL_SEPARATE_ATTRIBS.
  GLSLProgram(const std::string& pathVertexShader, const std::string& pathControlShader,
              const std::string& pathEvaluationShader, const std::string& pathFragmentShader,
              std::vector<const GLchar*>& varyings, GLenum bufferMode);

  //! \brief Creates a transform-feedback shader.
  //! \param[in]  pathVertexShader Path to vertex shader.
  //! \param[in]  pathControlShader Path to tessellation control shader.
  //! \param[in]  pathEvaluationShader Path to tessellation evaluation shader.
  //! \param[in]  pathGeometryShader Path to geometry shader.
  //! \param[in]  pathFragmentShader Path to fragment shader.
  //! \param[in]  varyings An array of zero-terminated strings specifying the names of the varying variables to use
  //!             for transform feedback.
  //! \param[in]  bufferMode Identifies the mode used to capture the varying variables when transform feedback is
  //!             active. Must be GL_INTERLEAVED_ATTRIBS or GL_SEPARATE_ATTRIBS.
  GLSLProgram(const std::string& pathVertexShader, const std::string& pathControlShader,
              const std::string& pathEvaluationShader, const std::string& pathGeometryShader,
              const std::string& pathFragmentShader, std::vector<const GLchar*>& varyings, GLenum bufferMode);

  GLSLProgram(const GLSLProgram&) = delete;
  GLSLProgram& operator=(const GLSLProgram&) = delete;

  GLSLProgram(GLSLProgram&& other);
  GLSLProgram& operator=(GLSLProgram&& other);

  //! \brief Default destructor.
  ~GLSLProgram();

  //! \brief Uses the program for subsequent draw calls.
  void use() const;

  static GLSLProgram createComputeFromSource(const std::string& computeShaderSource);

  //! \brief Creates a shader from source code (as opposed to loading the source code from a file).
  //! \param[in,out]  vertexShaderSource Source code of the vertex shader.
  //! \param[in,out]  controlShaderSource Source code of  the control shader.
  //! \param[in,out]  evaluationShaderSource Source code of the evaluation shader.
  //! \param[in,out]  geometryShaderSource Source code of the geometry shader.
  //! \param[in,out]  fragmentShaderSource source code of the fragment shader.
  //! \return Unique pointer to a GLSL shader program.
  static GLSLProgram createFromSource(const std::string& vertexShaderSource,
                                      const std::string& controlShaderSource, const std::string& evaluationShaderSource,
                                      const std::string& geometryShaderSource, const std::string& fragmentShaderSource);

  //! \brief Creates a shader from source code (as opposed to loading the source code from a file).
  //! \param[in,out]  computeShaderSource Source code of the compute shader.
  //! \return Unique pointer to a GLSL shader program.
  static GLSLProgram createFromSource(const std::string& computeShaderSource);

  //! \brief Creates a shader from binary files (as opposed to loading the source code from a file).
  //! \param[in]  vertexShaderSource binary of the vertex shader.
  //! \param[in]  controlShaderSource binary of  the control shader.
  //! \param[in]  evaluationShaderSource binary of the evaluation shader.
  //! \param[in]  geometryShaderSource binary of the geometry shader.
  //! \param[in]  fragmentShaderSource binary of the fragment shader.
  //! \return Object of GLSL shader program.
  static GLSLProgram createFromBinary(const std::string& vertexShaderSource,
                                      const std::string& controlShaderSource, const std::string& evaluationShaderSource,
                                      const std::string& geometryShaderSource, const std::string& fragmentShaderSource);

  //!\ brief Creates a shader from with  a mesh- and a fragment shader.  
  //! \param[in] pathToMeshShader Path to the mesh shader source code.
  //! \param[in] pathToFragmentShader Path to the fragment shader source code.
  //! \return Object of the GLSL shader program.
  static GLSLProgram createMeshFragmentFromSourceFile(const std::string& pathToMeshShader,
                                                      const std::string& pathToFragmentShader);


  //!\ brief Creates a shader from with a task-, a mesh-, and a fragment shader.
  //! \param[in] pathToTaskShader Path to the task shader source code.
  //! \param[in] pathToMeshShader Path to the mesh shader source code.
  //! \param[in] pathToFragmentShader Path to the fragment shader source code.
  //! \return Object of the GLSL shader program.
  static GLSLProgram createTaskMeshFragmentFromSourceFile(const std::string& pathToTaskShader,
                                                          const std::string& pathToMeshShader,
                                                          const std::string& pathToFragmentShader);

  //! \brief Returns the info log of the program.
  std::string getInfoLog() const;
public:
  //! \brief Gets the location of a uniform variable
  //! \param[in]  name Name of the uniform variable.
  //! \return -1 if there is no such uniform variable, otherwise the index of the uniform variable is returned.
  GLint getUniformLocation(const GLchar *name) const;

  //! \brief Returns true if the uniform exists.
  //!
  //! \param  name name of the uniform variable
  GLuint getUniformBlockIndex(const GLchar* name) const;

  bool bindUniformBlock(const GLchar* name, GLuint bufferObject, GLuint bindingPoint);

  //! \brief Returns true if the uniform exists.
  //!
  //! \param  name name of the uniform variable
  //! return
  bool doesUniformExist(const GLchar* name) const;

  //! Converts the type of GLSL uniform variables, attributes, and varyings into a string.
  static const char* glslTypeToString(GLenum type);

  //! \brief Sets the value of 2x2 matrix uniform variable.
  //! \throw cogra::gl::GLSLRuntimeError if the type of the unform variable is not a 3x3 matrix.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \param[in]  transposed True, if that matrix shall be transposed or not.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const glm::mat2& a, bool transposed = false) const;

  //! \brief Sets the value of 3x3 matrix uniform variable.
  //! \throw cogra::gl::GLSLRuntimeError if the type of the unform variable is not a 3x3 matrix.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \param[in]  transposed True, if that matrix shall be transposed or not.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const glm::mat3& a, bool transposed = false) const;

  //! \brief Sets the value of 4x4 matrix uniform variable.
  //! \throw cogra::gl::GLSLRuntimeError if the type of the unform variable is not a 4x4 matrix.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \param[in]  transposed True, if that matrix shall be transposed or not.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const glm::mat4& a, bool transposed = false) const;

  //! \brief Sets the value scalar uniform variable.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, GLfloat a) const;

  //! \brief Sets the value 2D vector-valued uniform variable.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const f32vec2& a) const;

  //! \brief Sets the value 3D vector-valued uniform variable.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const f32vec3& a) const;

  //! \brief Sets the value 4D vector-valued uniform variable.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const f32vec4& a) const;

  //! \brief Sets the value scalar unsigned uniform variable.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, GLint a) const;

  //! \brief Sets the value scalar unsigned uniform variable.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, GLuint a) const;

  //! \brief Sets the value 2D vector-valued uniform variable.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const glm::uvec2& a) const;

  //! \brief Sets the value of a boolean uniform variable.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  a The value of "name"  that should be set.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, bool a) const;

  //! \brief Sets the value of a texture uniform variable.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  texture A reference to the texture.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const Texture& texture) const;

  //! \brief Sets the value of a texture uniform variable.
  //! \param[in]  name Name of the uniform.
  //! \param[in]  texture A reference to the sampler.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const Sampler& sampler) const;

  //! \brief Sets the value of a float32 array.
  //! \param[in]  name Name of the float32 array.
  //! \param[in]  a A reference to the array stored in a vector.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const std::vector<float32>& a) const;

  //! \brief Sets the value of a uint32 array.
  //! \param[in]  name Name of the uint32 array.
  //! \param[in]  a A reference to the array stored in a vector.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const std::vector<uint32>& a) const;

  //! \brief Sets the value of a f32vec2 array.
  //! \param[in]  name Name of the f32vec2 array.
  //! \param[in]  a A reference to the array stored in a vector.
  //! \return True, if the uniform variable exits, false otherwise.
  bool setUniform(const char* name, const std::vector<f32vec2>& a) const;

  //! \brief Returns a zero-based index of the attribute.
  //! \param[in]  name Name of the uniform.
  //! \return -1 in case the attribute does not exist, >= 0 the location of the attribute.
  GLint getAttributeLocation(const char* name) const;


private:
  void linkProgram();

  void linkProgram(std::vector<const GLchar*>& varyings, GLenum bufferMode);

  void attachShader(GLuint shaderHandle) const;

  template<int SHADER_TYPE>
  void prepareShader(const std::string& pathToShader) const
  {
    if(!pathToShader.empty())
    {
      GLSLShader<SHADER_TYPE> shader(pathToShader, GLSLShader<SHADER_TYPE>::ShaderSourceCodeFromFile);
      attachShader(shader.getHandle());
    }
  }

  void createProgram();

  //! Handle to OpenGL program.
  GLuint m_programHandle;

  struct UniformInfo
  {
    GLint location = -1;
    GLsizei size = 0;
    GLenum type = 0;
  };

  mutable std::unordered_map<std::string, UniformInfo> m_uniform;

  //! \brief Returns a vector of all uniforms used in the program.
  void createUniformMap();

};
}
}
#endif
