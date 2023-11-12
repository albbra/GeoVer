include("../../buildutils/CreateApp.cmake")
project(ProjectWithTests)
set(ContribLibraries GLM COGRA)
CreateApp(ContribLibraries)
