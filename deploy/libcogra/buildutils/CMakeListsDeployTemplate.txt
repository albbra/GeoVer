#-----------------------------------------------------------------------------------------------------------------------
# Copyright (C) 2017-2018 by Quirin Meyer - All Rights Reserved
#-----------------------------------------------------------------------------------------------------------------------
project(CograExercises)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
cmake_minimum_required(VERSION 3.4)

set (CMAKE_CXX_STANDARD 14)
if(APPLE)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(CMAKE_GENERATOR STREQUAL "Visual Studio 15 2017 Win64")    
    SET (OUTPUT_SUB_DIR "")
elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 14 2015 Win64")    
    SET (OUTPUT_SUB_DIR "")
elseif(CMAKE_GENERATOR STREQUAL  "MinGW Makefiles")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    SET (OUTPUT_SUB_DIR "/bin")
elseif(CMAKE_GENERATOR STREQUAL  "Unix Makefiles")    
    SET (OUTPUT_SUB_DIR "/bin")
else()
    message("${CMAKE_GENERATOR} not tested. Good luck!" )
endif()

add_subdirectory(libcogra)
add_subdirectory(exercises)