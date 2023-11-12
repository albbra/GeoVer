project(libcogra_tests)
set(ContribLibraries COGRA GLM)
CreateTest(ContribLibraries ${PROJECT_NAME})
set_target_properties (libcogra_tests PROPERTIES FOLDER cogra/tests)
