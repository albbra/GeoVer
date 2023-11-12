include("../../buildutils/CreateApp.cmake")
project(SimpleTriangleBinary)
set(ContribLibraries GLEW GLFW GLM IMGUI VULKAN COGRA)
CreateApp(ContribLibraries)
