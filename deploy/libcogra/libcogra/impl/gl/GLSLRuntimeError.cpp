/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/gl/GLSLRuntimeError.h>
namespace cogra
{
    namespace gl
    {
        GLSLRuntimeError::GLSLRuntimeError(const std::string& message) : cogra::exceptions::RuntimeError(message)
        { }
    }
}
