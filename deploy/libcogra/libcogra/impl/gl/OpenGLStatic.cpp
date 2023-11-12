/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/gl/OpenGLStatic.h>
#include <iostream>
namespace cogra
{
    namespace gl
    {
        OpenGLStatic::FrameBufferStatus::Enum OpenGLStatic::FrameBufferStatus::checkStatus()
        {
            GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            switch(fboStatus)
            {
                case GL_FRAMEBUFFER_COMPLETE:
                    return Complete;
                    
                case GL_FRAMEBUFFER_UNDEFINED:
                    std::cerr << "GL_FRAMEBUFFER_UNDEFINED\n";
                    return Undefined;
                    
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                    std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n";
                    return IncompleteAttachment;
                    
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                    std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n";
                    return IncompleteMissingAttachment;
                    
                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                    std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n";
                    return IncompleteDrawBuffer;
                    
                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                    std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n";
                    return IncompleteReadBuffer;
                    
                case GL_FRAMEBUFFER_UNSUPPORTED:
                    std::cerr << "GL_FRAMEBUFFER_UNSUPPORTED\n";
                    return Unsupported;
                    
                case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                    std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n";
                    return IncompleteMultisample;
                    
                case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                    std::cerr << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS\n";
                    return IncompleteLayerTargets;
                    
                default:
                    return End;
            }
        }
    }
}
