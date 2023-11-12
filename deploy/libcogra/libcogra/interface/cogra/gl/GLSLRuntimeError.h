/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_GL_GLSLRUNTIMEERROR_H_
#define COGRA_GL_GLSLRUNTIMEERROR_H_
#include <cogra/exceptions/RuntimeError.h>

namespace cogra
{
    namespace gl
    {
        //! \brief Exception class for runtime errors that occur with OpenGLSL shaders and programs.
        class GLSLRuntimeError : public  cogra::exceptions::RuntimeError
        {
        public:
            //! Create an exception for GLSL errors.
            explicit GLSLRuntimeError(const std::string& message);
        };
    }
}

#endif
