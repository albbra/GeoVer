/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#pragma once
#ifndef COGRA_GL_OPENGLRUNTIMEERROR_H_
#define COGRA_GL_OPENGLRUNTIMEERROR_H_
#include <iostream>
#include <glad/glad.h>
#include <cogra/exceptions/RuntimeError.h>

namespace cogra
{
    namespace gl
    {
        //! Exception class for OpenGL runtime errors.
        class OpenGLRuntimeError : public cogra::exceptions::RuntimeError
        {
        public:
            //! \brief An exception that should be thrown whenever an OpenGL error occurs.
            //! \param[in]  message			Error message.
            //! \param[in]  fileName		File name of the file where the exception was thrown.
            //! \param[in]  line			Line number from where the exception was thrown.
            //! \param[in]  functionName	Function name from which the exception was thrown.
            OpenGLRuntimeError(const std::string& message, const char* fileName, int line, const char* functionName);

            //! \brief Checks for an OpenGL error.
            //! \param[in,out]  file Filename from which CheckGLCoreError was called.
            //! \param[in,out]  line Source-code line from which CheckGLCoreError was called.
            //! \param[in,out]  func Name of the function from which CheckGLCoreError was called.
            static void checkGLCoreError(const char *file, int line, const char *func);

            //! \brief Checks for an OpenGL error.
            //! \param[in,out]  file Filename from which CheckGLCoreError was called.
            //! \param[in,out]  line Source-code line from which CheckGLCoreError was called.
            //! \param[in,out]  func Name of the function from which CheckGLCoreError was called.
            static void throwOnGLError(const char *file, int line, const char *func);

            //! \brief Translates an OpenGL error code to more readable error message.
            //! \param[in]  error OpenGL error code retrieved from glGetError.
            //! \return An string containing the name of the pre-processor define of GLenum.
            static std::string openGLErrorCodeToMessage(GLenum error);
        };
    }
}

#ifdef __FUNCTION__
#    define THROW_ON_GL_ERROR ::cogra::gl::OpenGLRuntimeError::throwOnGLError(__FILE__, __LINE__, __FUNCTION__)
#else
#    define THROW_ON_GL_ERROR ::cogra::gl::OpenGLRuntimeError::throwOnGLError(__FILE__, __LINE__, "")
#endif

#ifdef _DEBUG
#define GL_SAFE_CALL(call)\
call;\
{ \
  GLenum glErr = glGetError(); \
  if (glErr != GL_NO_ERROR)\
  { \
    throw cogra::gl::OpenGLRuntimeError("OpenGL Error: " + std::string(#call) + " returned: "\
          + ::cogra::gl::OpenGLRuntimeError::openGLErrorCodeToMessage(glErr) + ".",  __FILE__, __LINE__,\
          + __FUNCTION__);\
  }\
}
#else
#   define GL_SAFE_CALL(call) call;
#endif

#ifdef _DEBUG
#define GL_SAFE_CALL_NO_THROW(call)\
call;\
{ \
  GLenum glErr = glGetError(); \
  if (glErr != GL_NO_ERROR)\
  { \
    std::cerr << "Unhandled exception "\
    << ::cogra::gl::OpenGLRuntimeError::openGLErrorCodeToMessage(glErr) << "." << __FILE__ << __LINE__ << __FUNCTION__ << "\n";\
  }\
}
#else
#   define GL_SAFE_CALL_NO_THROW(call) call;
#endif

#ifdef _DEBUG
#   ifdef __FUNCTION__
#       define CHECK_GL_ERROR ::cogra::gl::OpenGLRuntimeError::checkGLCoreError(__FILE__, __LINE__, __FUNCTION__)
#   else
#       define CHECK_GL_ERROR ::cogra::gl::OpenGLRuntimeError::checkGLCoreError(__FILE__, __LINE__, "")
#   endif
#else
#   define CHECK_GL_ERROR ((void)(0))
#endif

#endif
