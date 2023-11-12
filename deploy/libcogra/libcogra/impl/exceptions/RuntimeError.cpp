/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <cogra/exceptions/RuntimeError.h>
#include <cogra/types.h>
namespace cogra
{
    namespace exceptions
    {
        RuntimeError::RuntimeError(const std::string& message)
            : std::runtime_error(message)
        { }

        RuntimeError::RuntimeError(const std::string& message, const char * fileName, int line, const char * functionName)
            : std::runtime_error("Runtime Error " + std::string(functionName) + "(" + std::string(fileName) + ","
                                 + std::to_string(static_cast<uint32>(line)) + "):" + message)
        { }
    }
}
