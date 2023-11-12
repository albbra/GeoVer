/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/gl/OpenGLRuntimeError.h>

namespace cogra
{
    namespace gl
    {
        OpenGLRuntimeError::OpenGLRuntimeError(const std::string& message, const char* fileName, int line,
                                               const char* functionName)
            : RuntimeError(message, fileName, line, functionName)
        { }

        void OpenGLRuntimeError::checkGLCoreError(const char *file, int line, const char *func)
        {
            GLenum err;
            while((err = glGetError()) != GL_NO_ERROR)
            {
                std::cerr
                    << std::dec << file << "(" << line << "): " << func << ". glGetError()="
                    << std::hex << "0x" << err << ".\n";
            }
        }

        void OpenGLRuntimeError::throwOnGLError(const char *file, int line, const char *func)
        {
            GLenum err = glGetError();
            if(err != GL_NO_ERROR)
            {
                throw cogra::gl::OpenGLRuntimeError(openGLErrorCodeToMessage(err), file, line, func);
            }
        }

        std::string OpenGLRuntimeError::openGLErrorCodeToMessage(const GLenum error)
        {
            switch(error)
            {
                case GL_NO_ERROR:
                    return "GL_NO_ERROR";
                case GL_INVALID_ENUM:
                    return "GL_INVALID_ENUM";
                case GL_INVALID_VALUE:
                    return "GL_INVALID_VALUE";
                case GL_INVALID_OPERATION:
                    return "GL_INVALID_OPERATION";
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    return "GL_INVALID_FRAMEBUFFER_OPERATION";
                case GL_OUT_OF_MEMORY:
                    return "GL_OUT_OF_MEMORY";
                case GL_STACK_UNDERFLOW:
                    return "GL_STACK_UNDERFLOW";
                case GL_STACK_OVERFLOW:
                    return "GL_STACK_OVERFLOW";
                default:
                    return "Unknown OpenGL error message\n";
            }
        }
    }
}
