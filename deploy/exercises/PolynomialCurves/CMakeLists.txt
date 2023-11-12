include("../../libcogra/buildutils/CreateApp.cmake")
project(PolynomialCurves)
set(ContribLibraries GLEW GLFW GLM IMGUI EIGEN COGRA)
CreateApp(ContribLibraries)
