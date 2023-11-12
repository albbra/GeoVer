# Googletest
set(BUILD_GMOCK OFF CACHE BOOL OFF FORCE)
set(BUILD_GTEST ON CACHE BOOL ON FORCE)
set(gtest_force_shared_crt ON CACHE BOOL ON FORCE)
# This is only required in case we use mingw
set(gtest_disable_pthreads ON CACHE BOOL ON FORCE)
add_subdirectory(googletest)
set_target_properties (gtest PROPERTIES FOLDER cogra/contrib/googletest)
set_target_properties (gtest_main PROPERTIES FOLDER cogra/contrib/googletest)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL OFF FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL OFF FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL OFF FORCE)
set(GLFW_INSTALL OFF CACHE BOOL OFF FORCE)
add_subdirectory(glfw)
set_target_properties (glfw PROPERTIES FOLDER cogra/contrib)

# ASSIMP
IF(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assimp")
	set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL OFF FORCE)
	set(ASSIMP_BUILD_TESTS OFF CACHE BOOL OFF FORCE)
	set(ASSIMP_BUILD_ZLIB ON CACHE BOOL ON FORCE)
	set(BUILD_TESTING OFF CACHE BOOL OFF FORCE)
	add_subdirectory(assimp)
	set_target_properties (zlib PROPERTIES FOLDER cogra/contrib/assimp)
	set_target_properties (zlibstatic PROPERTIES FOLDER cogra/contrib/assimp)
	set_target_properties (IrrXML PROPERTIES FOLDER cogra/contrib/assimp)
	set_target_properties (uninstall PROPERTIES FOLDER cogra/contrib/assimp)
	if(WIN32 AND NOT MINGW)
		set_target_properties (UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER cogra/contrib/assimp)
	endif(WIN32 AND NOT MINGW)
	set_target_properties (assimp PROPERTIES FOLDER cogra/contrib/assimp)
	set(ASSIMP_BUILD_INCLUDE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assimp/include" CACHE STRING "")
ENDIF(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assimp")
	
# SPDLOG
set(SPDLOG_BUILD_EXAMPLES OFF CACHE BOOL OFF FORCE)
set(SPDLOG_BUILD_TESTING OFF CACHE BOOL OFF FORCE)
add_subdirectory(spdlog)
set_target_properties (spdlog_headers_for_ide PROPERTIES FOLDER cogra/contrib/spdlog)

# CLIP
set(CLIP_EXAMPLES OFF CACHE BOOL OFF FORCE)
set(CLIP_TESTS OFF CACHE BOOL OFF FORCE)
add_subdirectory(clip)
set_target_properties (clip PROPERTIES FOLDER cogra/contrib/clip)

# TBB
IF(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tbb")
	set(TBB_BUILD_SHARED OFF CACHE BOOL OFF FORCE)
	set(TBB_BUILD_STATIC ON CACHE BOOL ON FORCE)
	set(TBB_BUILD_MALLOC ON CACHE BOOL ON FORCE)
	set(TBB_BUILD_MALLOC_PROXY ON CACHE BOOL ON FORCE)
	set(TBB_BUILD_TESTS OFF CACHE BOOL OFF FORCE)
	set(TBB_CI_BUILD OFF CACHE BOOL OFF FORCE)
	add_subdirectory(tbb)
	set_target_properties(tbb_static PROPERTIES FOLDER cogra/contrib/tbb)
	set_target_properties(tbb_def_files PROPERTIES FOLDER cogra/contrib/tbb)
	set_target_properties(tbbmalloc_proxy_static PROPERTIES FOLDER cogra/contrib/tbb)
	set_target_properties(tbbmalloc_static PROPERTIES FOLDER cogra/contrib/tbb)
ENDIF(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tbb")