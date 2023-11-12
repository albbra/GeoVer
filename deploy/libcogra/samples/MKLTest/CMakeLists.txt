include("../../buildutils/CreateApp.cmake")
project(MKLTest)
set(ContribLibraries OPENMP TBB MKL COGRA)
CreateApp(ContribLibraries)
