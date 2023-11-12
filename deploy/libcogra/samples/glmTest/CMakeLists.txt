include("../../buildutils/CreateApp.cmake")
project(glmTest)
set(ContribLibraries GLEW GLFW GLM IMGUI COGRA EIGEN)
CreateApp(ContribLibraries)
