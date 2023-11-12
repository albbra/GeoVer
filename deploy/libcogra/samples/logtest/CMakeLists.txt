include("../../buildutils/CreateApp.cmake")
project(logtest)
set(ContribLibraries GLEW GLFW GLM IMGUI COGRA)
CreateApp(ContribLibraries)
