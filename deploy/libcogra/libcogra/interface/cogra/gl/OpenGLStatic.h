/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_OPENGLSTATIC_H_
#define COGRA_GL_OPENGLSTATIC_H_
#include <glad/glad.h>
#include <string>
namespace cogra
{
    namespace exceptions { class RuntimeError; }

    //! \brief Namespace for graphics-system-related classes, functions, and variables.
    namespace gl
    {
        //! \brief Static OpenGL functions and  constants.
        class OpenGLStatic
        {
        public:

            struct FrameBufferStatus
            {
                enum Enum
                {
                    Complete = 0,
                    Undefined,
                    IncompleteAttachment,
                    IncompleteMissingAttachment,
                    IncompleteDrawBuffer,
                    IncompleteReadBuffer,
                    Unsupported,
                    IncompleteMultisample,
                    IncompleteLayerTargets,
                    End
                };

                static Enum checkStatus();
            };

            OpenGLStatic() = delete;
            OpenGLStatic(const OpenGLStatic&) = delete;
        };
    }
}
#endif
