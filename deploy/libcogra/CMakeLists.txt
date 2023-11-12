#-----------------------------------------------------------------------------------------------------------------------
# Copyright (C) 2017-2018 by Quirin Meyer - All Rights Reserved
#-----------------------------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.4)

include("buildutils/ErrofIfBuildDirectoryIsSourceDirectory.cmake")
include("buildutils/DeploySourceCode.cmake")
include("buildutils/FindVTune.cmake")
include("buildutils/FindIPP.cmake")
include("buildutils/FindMKL.cmake")


ErrofIfBuildDirectoryIsSourceDirectory()
set (CMAKE_CXX_STANDARD 17)
if(APPLE)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()


# Make the Microsoft Visual Studio solution support solution folders.
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)


if(CMAKE_GENERATOR STREQUAL "Visual Studio 16 2019")    
    SET (OUTPUT_SUB_DIR "")
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 15 2017")    
    SET (OUTPUT_SUB_DIR "")
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 14 2015")    
    SET (OUTPUT_SUB_DIR "")
elseif(CMAKE_GENERATOR STREQUAL  "MinGW Makefiles")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    SET (OUTPUT_SUB_DIR "/bin")
elseif(CMAKE_GENERATOR STREQUAL  "Unix Makefiles")    
    SET (OUTPUT_SUB_DIR "/bin")
else()
    message("${CMAKE_GENERATOR} not tested. Good luck!" )
endif()

set(COGRA_CONTRIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/contrib" CACHE STRING "")

# compile the contribution libraries too.
add_subdirectory(contrib)

#copy data to runtime
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



add_subdirectory(libcogra)
get_directory_property(COGRA_INCLUDE_DIR DIRECTORY libcogra DEFINITION COGRA_INCLUDE_DIR)

#add_subdirectory(tests)
#add_subdirectory(samples)

SET(COGRA_DEPLOY 0 CACHE BOOL "Create Source Code Package to Deploy for students.")
if(${COGRA_DEPLOY})
  DepolySourceCode()
endif()