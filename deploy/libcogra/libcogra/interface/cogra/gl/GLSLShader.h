/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_GLSLSHADER_H_
#define COGRA_GL_GLSLSHADER_H_
#include <glad/glad.h>
#include <string>
#include <cogra/gl/GLSLRuntimeError.h>
#include <cogra/gl/GLSLShader.h>
#include <cogra/gl/OpenGLStatic.h>
#include <cogra/tools/NormalizeFilename.h>
#include <fstream>
#include <vector>
namespace cogra
{
namespace gl
{
//! \brief Class for shader programs, such vertex, geometry, tessellation control,  tessellation evaluation,
//! fragment, and compute shaders.
template<GLenum GL_SHADER_ENUM>
class GLSLShader
{
  static_assert(
    (GL_SHADER_ENUM == GL_FRAGMENT_SHADER) ||
    (GL_SHADER_ENUM == GL_TESS_CONTROL_SHADER) ||
    (GL_SHADER_ENUM == GL_TESS_EVALUATION_SHADER) ||
    (GL_SHADER_ENUM == GL_GEOMETRY_SHADER) ||
    (GL_SHADER_ENUM == GL_VERTEX_SHADER) ||
    (GL_SHADER_ENUM == GL_COMPUTE_SHADER) ||
    (GL_SHADER_ENUM == GL_TASK_SHADER_NV) ||
    (GL_SHADER_ENUM == GL_MESH_SHADER_NV),
    "Wrong Shader Type");
public:
  //! Parameter for constructor.
  enum ShaderSourceType { ShaderSourceCodeFromFile = 0, ShaderSourceCodeFromString = 1, ShaderSourceCodeBinary = 2 };

  //! \brief Constructs a shader object from source or from a file that contains the source.
  //! \param[in]  str Path to filename or source code.
  //! \param[in]  shaderSourceCodeFrom Indicates what is content of str
  //! \throws cogra::gl::GLSLRuntimeError in case the shader could not be compiled.
  //! \throws cogra::gl::OpenGLRuntimeError on any OpenGLError.
  GLSLShader(const std::string& str, const ShaderSourceType shaderSourceCodeFrom)
    : m_shaderHandle(0)
  {
    createShader();
    if(shaderSourceCodeFrom == ShaderSourceCodeFromFile)
    {
      compileShader(readShaderSource(str), str);
    }
    else if(shaderSourceCodeFrom == ShaderSourceCodeBinary)
    {
      compileBinaryShader(readBinaryShader(str), str);
    }
    else
    {
      compileShader(str);
    }
  }

  //! \brief Deletes the shader object.
  virtual ~GLSLShader()
  {
    if(m_shaderHandle != 0)
    {
      glDeleteShader(m_shaderHandle);
    }
  }

  //! Returns the handle of the shader.
  GLuint getHandle() const
  {
    return m_shaderHandle;
  }
private:
  //! \brief Compiles a shader from source.
  //! \param[in]  shaderSourceCode Source code of the shader.
  //! \param[in] fileName path to filename from the the shader source comes. Empty, in case no the shader code does
  //! not come from a file.
  //! \throws cogra::gl::GLSLRuntimeError in case the shader could not be compiled.
  //! \throws cogra::gl::OpenGLRuntimeError on any OpenGLError.
  void compileShader(const std::string& shaderSourceCode, const std::string& fileName = std::string())
  {
    if(shaderSourceCode.empty())
    {
      throw cogra::gl::GLSLRuntimeError("No shader code provided.");
    }

    const GLchar* pCode = shaderSourceCode.c_str();
    const GLchar** ppCode = &pCode;
    GL_SAFE_CALL(glShaderSource(m_shaderHandle, 1, ppCode, NULL));
    GL_SAFE_CALL(glCompileShader(m_shaderHandle));
    GLint compiled;
    GL_SAFE_CALL(glGetShaderiv(m_shaderHandle, GL_COMPILE_STATUS, &compiled));

    if(compiled == GL_FALSE)
    {
      if(fileName.empty())
      {
        throw cogra::gl::GLSLRuntimeError("Error compiling " + shaderTypeString() + ".\n" + getInfoLog());
      }
      else
      {
        throw cogra::gl::GLSLRuntimeError("Error compiling " + shaderTypeString() + " from " + fileName
                                          + ".\n" + getInfoLog());
      }
    }
  }


  //! \brief Compiles a binary shader from source.
  //! \param[in]  shaderSourceCode Source code of the shader.
  //! \param[in] fileName path to filename from the the shader source comes. Empty, in case no the shader code does
  //! not come from a file.
  //! \throws cogra::gl::GLSLRuntimeError in case the shader could not be compiled.
  //! \throws cogra::gl::OpenGLRuntimeError on any OpenGLError.
  void compileBinaryShader(const std::string& shaderSourceCode, const std::string& fileName = std::string())
  {

    if(shaderSourceCode.empty())
    {
      throw cogra::gl::GLSLRuntimeError("No shader code provided.");
    }

    GL_SAFE_CALL(glShaderBinary(1, &m_shaderHandle, GL_SHADER_BINARY_FORMAT_SPIR_V, shaderSourceCode.c_str(), static_cast<GLsizei>(shaderSourceCode.length())));
    GL_SAFE_CALL(glSpecializeShader(m_shaderHandle, "main", 0, nullptr, nullptr));
    GLint compiled;
    GL_SAFE_CALL(glGetShaderiv(m_shaderHandle, GL_COMPILE_STATUS, &compiled));

    if(compiled == GL_FALSE)
    {
      if(fileName.empty())
      {
        throw cogra::gl::GLSLRuntimeError("Error compiling " + shaderTypeString() + ".\n" + getInfoLog());
      }
      else
      {
        throw cogra::gl::GLSLRuntimeError("Error compiling " + shaderTypeString() + " from " + normalizeFilename(fileName)
                                          + ".\n" + getInfoLog());
      }
    }
  }

  //! Returns the info log of the shader.
  //! The info log contains compile errors.
  //! \throws cogra::gl::OpenGLRuntimeError on any OpenGLError.
  std::string getInfoLog() const
  {
    GLsizei infologLength = 0;
    GL_SAFE_CALL(glGetShaderiv(m_shaderHandle, GL_INFO_LOG_LENGTH, &infologLength));
    if(infologLength > 0)
    {
      GLchar *infoLog;
      GLsizei charsWritten = 0;
      infoLog = new GLchar[infologLength];
      GL_SAFE_CALL(glGetShaderInfoLog(m_shaderHandle, infologLength, &charsWritten, infoLog));
      std::string result = infoLog;
      delete[] infoLog;
      return result;
    }
    else
    {
      return std::string("");
    }
  }

  //! \brief Reads all text from a file.
  //! \param fileName Path to file of the shader source code.
  //! \throws cogra::gl::GLSLRuntimeError, in case file could not be opened, or an error occurred while reading the
  //! file.
  //! \return Shader source from a file.
  std::string readShaderSource(const std::string& fileName)
  {
    std::ifstream is;

    is.open(fileName);
    if(is.fail())
    {
      throw cogra::gl::GLSLRuntimeError("Error opening file " + normalizeFilename(fileName) + ".\n");
    }
    try
    {
      std::string shaderSourceCode = std::string((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
      is.close();
      if(shaderSourceCode.empty())
      {
        throw cogra::gl::GLSLRuntimeError("No shader code in " + normalizeFilename(fileName) + ".");
      }
      return shaderSourceCode;
    }
    catch(...)
    {
      is.close();
      throw cogra::gl::GLSLRuntimeError("Error reading source file " + normalizeFilename(fileName) + ".\n");
    }
  }

  std::string readBinaryShader(const std::string& fileName)
  {
    std::ifstream is;

    is.open(fileName, std::ios::binary);

    if(is.fail())
    {
      throw cogra::gl::GLSLRuntimeError("Error opening file " + normalizeFilename(fileName) + ".\n");
    }
    try
    {
      std::string output = std::string((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());;
      is.close();
      if(output.empty())
      {
        throw cogra::gl::GLSLRuntimeError("No shader code in " + normalizeFilename(fileName) + ".");
      }

      return output;
    }
    catch(...)
    {
      is.close();
      throw cogra::gl::GLSLRuntimeError("Error reading source file " + normalizeFilename(fileName) + ".\n");
    }
  }

  //! \brief Reads the shader code that is passed to the OpenGL driver.
  //! \throws cogra::gl::OpenGLRuntimeError
  //! \return Shader code.
  std::string getSourceCodeFromOpenGL() const
  {
    GLsizei maxL;
    GL_SAFE_CALL(glGetProgramiv(m_shaderHandle, GL_SHADER_SOURCE_LENGTH, &maxL));
    GLchar* glShaderCode = new char[maxL];
    GLsizei l;
    GL_SAFE_CALL(glGetShaderSource(m_shaderHandle, maxL, &l, glShaderCode));
    std::string resultString = glShaderCode;
    delete[] glShaderCode;
    return resultString;
  }

  //! \brief Creates an OpenGL shader.
  void createShader()
  {
    GL_SAFE_CALL(m_shaderHandle = glCreateShader(static_cast<GLenum>(GL_SHADER_ENUM)));
  }

  //! \brief Returns the string of the shader type.
  static std::string shaderTypeString()
  {
#ifdef _MSC_VER
    __pragma(warning(push))
    __pragma(warning(disable:4127))
#endif
    if(GL_SHADER_ENUM == GL_VERTEX_SHADER) return "Vertex Shader";
    if(GL_SHADER_ENUM == GL_TESS_CONTROL_SHADER) return "Tessellation Control Shader";
    if(GL_SHADER_ENUM == GL_TESS_EVALUATION_SHADER) return "Tessellation Evaluation Shader";
    if(GL_SHADER_ENUM == GL_GEOMETRY_SHADER) return "Geometry Shader";
    if(GL_SHADER_ENUM == GL_FRAGMENT_SHADER) return "Fragment Shader";
    if(GL_SHADER_ENUM == GL_COMPUTE_SHADER) return "Compute Shader";
    if(GL_SHADER_ENUM == GL_TASK_SHADER_NV) return "Task Shader";
    if(GL_SHADER_ENUM == GL_MESH_SHADER_NV) return "Mesh Shader";
    // Should not be reached due to the static assert.
    return "Unkown Shader Type";
#ifdef _MSC_VER
    __pragma(warning(pop))
#endif
  }

  //! Internet OpenGL handle of the shader.
  GLuint        m_shaderHandle;
};
//! Typedef for vertex shaders.
typedef GLSLShader<GL_VERTEX_SHADER>          GLSLVertexShader;

//! Typedef for tessellation control shaders.
typedef GLSLShader<GL_TESS_CONTROL_SHADER>    GLSLTessellationControlShader;

//! Typedef for tessellation evaluation shaders.
typedef GLSLShader<GL_TESS_EVALUATION_SHADER> GLSLTessellationEvaluationShader;

//! Typedef for geometry shaders.
typedef GLSLShader<GL_GEOMETRY_SHADER>        GLSLGeometryShader;

//! Typedef for fragment shaders.
typedef GLSLShader<GL_FRAGMENT_SHADER>        GLSLFragmentShader;

//! Typedef for compute shaders.
typedef GLSLShader<GL_COMPUTE_SHADER>         GLSLComputerShader;

//! Typedef for task shaders.
typedef GLSLShader<GL_TASK_SHADER_NV>         GLSLTaskShader;

//! Typedef for mesh shaders.
typedef GLSLShader<GL_MESH_SHADER_NV>         GLSLMeshShader;

}
}

#endif
