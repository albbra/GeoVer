# - Find Intel MKL
# Find the MKL libraries
# Options:
#
#   MKL_STATIC: true if using static linking
#
#
#
# taken from https://github.com/hanjianwei/cmake-modules by Jianwei Han, https://hanjianwei.com/


if(WIN32)
  set(MKL_ROOT "C:/Program Files (x86)/IntelSWTools/compilers_and_libraries/windows/mkl" CACHE PATH "Folder contains MKL")
else()
  set(MKL_ROOT /opt/intel/mkl CACHE PATH "Folder contains MKL")
endif()

# Find header file dir
find_path(MKL_INCLUDE_DIR mkl.h PATHS ${MKL_ROOT}/include)

# Find libraries

# Handle suffix
set(_MKL_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})

if(WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .lib)
else()
    if(MKL_STATIC)
        set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
    else()
        set(CMAKE_FIND_LIBRARY_SUFFIXES .so)
    endif()
endif()


macro(find_mkl_library MKL_COMPONENT)
  string(TOLOWER ${MKL_COMPONENT} MKL_COMPONENT_LOWER)
  find_library(MKL_LIB_${MKL_COMPONENT} mkl_${MKL_COMPONENT_LOWER}${MKL_LIBNAME_SUFFIX}
               PATHS ${MKL_ROOT}/lib/intel64/)
endmacro()


find_mkl_library(INTEL_LP64)
find_mkl_library(INTEL_ILP64)
find_mkl_library(INTEL_THREAD)
find_mkl_library(CORE)
find_mkl_library(TBB_THREAD)
find_mkl_library(SEQUENTIAL)
find_mkl_library(RT)


set(MKL_LIBRARY
    ${MKL_LIB_INTEL_ILP64}	
	${MKL_LIB_SEQUENTIAL}
	${MKL_LIB_CORE}
	#${MKL_LIB_RT}
   )   

set(CMAKE_FIND_LIBRARY_SUFFIXES ${_MKL_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MKL DEFAULT_MSG MKL_INCLUDE_DIR MKL_LIBRARY)

#if (${MKL_FOUND})
    set(MKL_INCLUDE_DIRS ${MKL_INCLUDE_DIR} CACHE PATH PARENT_SCOPE FORCE)
    set(MKL_LIBRARIES ${MKL_LIBRARY} CACHE STRING PARENT_SCOPE FORCE)
#endif()

mark_as_advanced(MKL_INCLUDE_DIRS MKL_LIBRARIES)