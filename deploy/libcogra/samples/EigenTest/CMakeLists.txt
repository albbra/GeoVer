include("../../buildutils/CreateApp.cmake")
project(EigenTest)
set(ContribLibraries GLEW GLFW GLM IMGUI COGRA EIGEN)
CreateApp(ContribLibraries)
