include("../../buildutils/CreateApp.cmake")
project(SimpleTriangle)
set(ContribLibraries GLEW GLFW GLM IMGUI COGRA)
CreateApp(ContribLibraries)
