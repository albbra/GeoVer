/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_EXCEPTIONS_RUNTIMEERROR_H_
#define COGRA_EXCEPTIONS_RUNTIMEERROR_H_
#include <stdexcept>
#include <string>
#include <sstream>
namespace cogra
{
    namespace exceptions
    {
        /// <summary>
        /// A class for runtime error exception.
        /// </summary>
        class RuntimeError : public std::runtime_error
        {
        public:
            /// <summary>
            /// Creates a runrime error exception with a specific message.
            /// </summary>
            /// <param name="message">Message to attach to the exception. Should contain more information (e.g. debug information) about the reason why the exception was thrown.</param>
            explicit RuntimeError(const std::string& message);

            /// <summary>
            /// Creates a runtime error exception with a message code information.
            /// </summary>
            /// This function is used by pre-processors marcos. So we recommend using this function not directly. Instead use the macros.
            /// <param name="message">Message to attach to the exception.</param>
            /// <param name="fileName">Source code file name wherer the exception occured.</param>
            /// <param name="line">Source code line numbrer where the exception occured.</param>
            /// <param name="functionName">Function in which the exception occured.</param>
            RuntimeError(const std::string& message, const char* fileName, int line, const char* functionName);
        };
    }

#define Throw(EXCEPTION_CLASS, EXCEPTION_MESSAGE) { std::ostringstream s; s << EXCEPTION_MESSAGE; throw EXCEPTION_CLASS(s.str(), __FILE__, __LINE__, __FUNCTION__);}
}
#endif
