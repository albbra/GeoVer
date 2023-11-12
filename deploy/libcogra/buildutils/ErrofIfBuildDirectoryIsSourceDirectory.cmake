# The build directory may not be the source directory.
function(ErrofIfBuildDirectoryIsSourceDirectory)  
  if(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
      message(FATAL_ERROR "Source and binary directories must be different")
  endif(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
endfunction()