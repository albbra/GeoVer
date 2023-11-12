/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <glad/glad.h>
#include <cogra/gl/GLDebug.h>
#include <string>
#include <cogra/gl/OpenGLRuntimeError.h>

namespace
{
    const char* dispatchSource(GLenum source)
    {
        switch(source)
        {
            case GL_DEBUG_SOURCE_API:
                return "OpenGL API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                return "Window System";
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                return "Shader Compiler";
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                return "Third Party";
            case GL_DEBUG_SOURCE_APPLICATION:
                return "Application";
            case GL_DEBUG_SOURCE_OTHER:
                return "Other";
            default:
                return "Unknown";
        }
    }

    const char* dispatchType(GLenum type)
    {
        switch(type)
        {
            case GL_DEBUG_TYPE_ERROR:
                return "Error";
                
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                return "Deprecated behavior";
                
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                return "Undefined behavior";
                
            case GL_DEBUG_TYPE_PERFORMANCE:
                return "Performance problem";
                
            case GL_DEBUG_TYPE_PORTABILITY:
                return "Portability problem";
                
            case GL_DEBUG_TYPE_MARKER:
                return "Marker";
                
            case GL_DEBUG_TYPE_PUSH_GROUP:
                return "Push Group";
                
            case GL_DEBUG_TYPE_POP_GROUP:
                return "Pop Group";
                
            case GL_DEBUG_TYPE_OTHER:
                return "Other";
                
            default:
                return "Unknown";
        }
    }

    const char* dispatchSeverityLevel(GLenum severity)
    {
        switch(severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:
                return "High";
                
            case GL_DEBUG_SEVERITY_MEDIUM:
                return "Medium";
                
            case GL_DEBUG_SEVERITY_LOW:
                return "Low";
                
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                return "Notification";
                
            default:
                return "Unknown";
        }
    }

    void debugCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char* message, void* /*userParam*/)
    {
        std::string msg(message, message + length);
        std::cerr << "Source:   " << dispatchSource(source) << "\n"
            << "Type:     " << dispatchType(type) << "\n"
            << "Id:       " << id << "\n"
            << "Severity: " << dispatchSeverityLevel(severity) << "\n"
            << "Message:   " << msg << "\n\n";
    }
}

namespace cogra
{
    namespace gl
    {
        GLDebug::GLDebug()
        {
            GL_SAFE_CALL(glDebugMessageCallback((GLDEBUGPROC)debugCallbackFunction, nullptr));
            GL_SAFE_CALL(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
            GL_SAFE_CALL(glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE));
            GL_SAFE_CALL(glDebugMessageControl(GL_DEBUG_SOURCE_WINDOW_SYSTEM, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE));
            GL_SAFE_CALL(glDebugMessageControl(GL_DEBUG_SOURCE_SHADER_COMPILER, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE));
            GL_SAFE_CALL(glDebugMessageControl(GL_DEBUG_SOURCE_THIRD_PARTY, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE));
            GL_SAFE_CALL(glDebugMessageControl(GL_DEBUG_SOURCE_APPLICATION, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE));
            GL_SAFE_CALL(glDebugMessageControl(GL_DEBUG_SOURCE_OTHER, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE));
        }

        GLDebug::~GLDebug()
        {
            glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        }
    }
}
