include("../../buildutils/CreateApp.cmake")
project(Helloimgui)
set(ContribLibraries GLEW GLFW GLM GLI IMGUI COGRA)
CreateApp(ContribLibraries)