include("../../buildutils/CreateApp.cmake")
project(SimpleOpenCL)
set(ContribLibraries OPENCL COGRA)
CreateApp(ContribLibraries)
