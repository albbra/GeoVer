/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017-2018 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#ifndef COGRA_UI_GLFWWINDOWCONFIG_H_
#define COGRA_UI_GLFWWINDOWCONFIG_H_
#include <cogra/types.h>
namespace cogra
{
    namespace ui
    {
        /// <summary>
        /// Struct that configures important features of the Window that runs the OpenGL context.
        /// </summary>
        struct GLFWWindowConfig
        {
            /// <summary>
            /// OpenGL Major Version.
            /// </summary>
            int32 glMajorVersion = 4;

            /// <summary>
            /// OpenGL Minor Version.
            /// </summary>
            int32 glMinorVersion = 5;

            /// <summary>
            /// Load OpenGL Extensions. Turn this off, if you only want the OpenGL version that you specified with glMajorVersion.glMinorVersion.
            /// </summary>
            bool loadGLExtensions = true;
            
            /// <summary>
            /// Disable old OpenGL functions (also called Forward Compatibility).
            /// </summary>
            bool disableDeprecatedFunctions = true;
           
            /// <summary>
            /// Width of the window.
            /// </summary>
            uint32 width = 1024;

            /// <summary>
            /// Height of the window.
            /// </summary>
            uint32 height = 576;

            /// <summary>
            /// Title of the window.
            /// </summary>
            std::string windowTitle = "Title";

            /// <summary>
            /// Use sRGB Framebuffer.
            /// </summary>
            bool useSRGB = true;

            /// <summary>
            /// Number of samples for each fragment.
            /// </summary>
            uint32 samples = 1;
        };
    }
}
#endif
