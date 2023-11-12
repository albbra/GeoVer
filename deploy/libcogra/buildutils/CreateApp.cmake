# Adapted from http://cmake.3232098.n2.nabble.com/ADD-CUSTOM-COMMAND-cannot-depend-on-ADD-CUSTOM-TARGET-td6025751.html
function (AddShaderFiles shaderFiles contribLibs)
  	if (shaderFiles)
		 list(FIND ${contribLibs} VULKAN found)
    	 if(NOT(${found} EQUAL -1))
            find_package(Vulkan)
            string(REPLACE "Include" "Bin" Vulkan_BIN_DIR ${Vulkan_INCLUDE_DIRS} )
			foreach(shaderFile ${shaderFiles})				
        		ADD_CUSTOM_COMMAND(
					OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${shaderFile}.spv"
        			COMMAND ${Vulkan_BIN_DIR}\\glslc.exe                      
					"${CMAKE_CURRENT_SOURCE_DIR}/${shaderFile}" -o 
        			"${CMAKE_CURRENT_BINARY_DIR}/${shaderFile}.spv"
        			DEPENDS   "${CMAKE_CURRENT_SOURCE_DIR}/${shaderFile}"
        		)
        		list(APPEND shaderfile_dest "${CMAKE_CURRENT_BINARY_DIR}/${shaderFile}.spv")      
    		endforeach()
  
    		ADD_CUSTOM_TARGET(${PROJECT_NAME}_CopyResources ALL DEPENDS ${shaderfile_dest})
	
			set_target_properties (${PROJECT_NAME}_CopyResources PROPERTIES FOLDER CopyResources)	
		else()
    		foreach(shaderFile ${shaderFiles})
        		ADD_CUSTOM_COMMAND(
					OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${shaderFile}"
        			COMMAND cmake -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${shaderFile}"
        			"${CMAKE_CURRENT_BINARY_DIR}/${shaderFile}"
        			DEPENDS   "${CMAKE_CURRENT_SOURCE_DIR}/${shaderFile}"
        		)
        		list(APPEND shaderfile_dest "${CMAKE_CURRENT_BINARY_DIR}/${shaderFile}")      
    		endforeach()
  
    		ADD_CUSTOM_TARGET(${PROJECT_NAME}_CopyResources ALL DEPENDS ${shaderfile_dest})
	
			set_target_properties (${PROJECT_NAME}_CopyResources PROPERTIES FOLDER CopyResources)	
  		endif()
	endif()  
endfunction(AddShaderFiles)

function (AddGTESTIncludeDirs)
	include_directories(${COGRA_CONTRIB_DIR}/submodules/googletest/googletest/include)
endfunction(AddGTESTIncludeDirs)

# OpenGL

function (AddOpenGL projectName)
    include(FindOpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${projectName} PRIVATE ${OPENGL_gl_LIBRARY})
endfunction(AddOpenGL)

# GLFW

function(AddGLFW projectName)
    AddGLFWIncludes()
    target_link_libraries(${projectName} PRIVATE glfw)
endfunction(AddGLFW)

function(AddGLFWIncludes)
	include_directories(${COGRA_CONTRIB_DIR}/submodules/glfw/include)
endfunction(AddGLFWIncludes)

function(AddGLFWIfRequired contribLibs projectName)
    list(FIND ${contribLibs} GLFW found)
    if(NOT(${found} EQUAL -1))
        AddGLFW(${projectName})
    endif()
endfunction(AddGLFWIfRequired)

# GLM

function(AddGLM)
    include_directories(${COGRA_CONTRIB_DIR}/submodules/glm/)
endfunction(AddGLM)

function(AddGLMIfRequired contribLibs)
    list(FIND ${contribLibs} GLM found)
    if(NOT(${found} EQUAL -1))
        AddGLM()
    endif()
endfunction(AddGLMIfRequired)

# GLEW

function(AddGLEW projectName)
    AddGLEWIncludes()
    target_link_libraries(${projectName} PRIVATE glad)
endfunction(AddGLEW)

function(AddGLEWIncludes)	
    include_directories("${COGRA_CONTRIB_DIR}/CMakeProjects/glad/include")
endfunction(AddGLEWIncludes)

function(AddGLEWIfRequired contribLibs projectName)
    list(FIND ${contribLibs} GLEW found)
    if(NOT(${found} EQUAL -1))
        AddGLEW(${projectName})
    endif()
endfunction(AddGLEWIfRequired)

# Eigen

function(AddEigen projectName)
	AddEigenIncludes()	
	add_definitions(-DEIGEN_HAS_STD_RESULT_OF=0)
endfunction(AddEigen)

function(AddEigenIncludes)	
	include_directories("${COGRA_CONTRIB_DIR}/submodules/eigen")
endfunction(AddEigenIncludes)

function(AddEIGENIfRequired contribLibs projectName)
    list(FIND ${contribLibs} EIGEN found)
    if(NOT(${found} EQUAL -1))
        AddEigen(${projectName})
    endif()
endfunction(AddEIGENIfRequired)

# SPD Log

function(AddSPDLOGIncludes)
    include_directories(${COGRA_CONTRIB_DIR}/submodules/spdlog/include)
endfunction(AddSPDLOGIncludes)

function(AddSPDLOG projectName)
    AddSPDLOGIncludes()
    target_link_libraries(${projectName} PRIVATE spdlog)
endfunction(AddSPDLOG)

# IMGui

function(AddIMGUIIncludes)
    include_directories(${COGRA_CONTRIB_DIR}/submodules/imgui)
endfunction(AddIMGUIIncludes)

function(AddIMGUI projectName)
    AddIMGUIIncludes()
    target_link_libraries(${projectName} PRIVATE imgui)
endfunction(AddIMGUI)

function(AddIMGUIIfRequired contribLibs projectName)
    list(FIND ${contribLibs} IMGUI found)
    if(NOT(${found} EQUAL -1))
        AddIMGUI(${projectName})
    endif()
endfunction(AddIMGUIIfRequired)

# TinyFD

function(AddTINYFDIncludes)    
	include_directories(${COGRA_CONTRIB_DIR}/CMakeProjects/tinyfd)
endfunction(AddTINYFDIncludes)

function(AddTINYFD projectName)
    AddTINYFDIncludes()
    target_link_libraries(${projectName} PRIVATE tinyfd)
endfunction(AddTINYFD)

# Clip

function(AddClipIncludes)
    include_directories(${COGRA_CONTRIB_DIR}/submodules/clip)
endfunction(AddClipIncludes)

function(AddClip projectName)
    AddClipIncludes()
    target_link_libraries(${projectName} PRIVATE clip)
endfunction(AddClip)

# Cogra

function(AddCOGRA projectName)
    include_directories(${COGRA_INCLUDE_DIR})
    target_link_libraries(${projectName} PRIVATE cogra)
endfunction(AddCOGRA) 

function(AddCOGRAIfRequired contribLibs projectName)
    list(FIND ${contribLibs} COGRA found)
    if(NOT(${found} EQUAL -1))
        AddCOGRA(${projectName})
    endif()
endfunction(AddCOGRAIfRequired) 

# VTune

function(AddVTUNE projectName)	
    include_directories(${VTune_INCLUDE_DIRS})
    target_link_libraries(${projectName} PRIVATE ${VTune_LIBRARIES})
endfunction(AddVTUNE) 

function(AddVTUNEIfRequired contribLibs projectName)	
    list(FIND ${contribLibs} VTUNE found)
    if(NOT(${found} EQUAL -1))		
        AddVTUNE(${projectName})
    endif()
endfunction(AddVTUNEIfRequired) 

# IPP

function(AddIPP projectName)
    include_directories(${IPP_INCLUDE_DIR})	
    target_link_libraries(${projectName} PRIVATE ${IPP_LIBRARIES})
endfunction(AddIPP) 

function(AddIPPIfRequired contribLibs projectName)	
    list(FIND ${contribLibs} IPP found)
    if(NOT(${found} EQUAL -1))		
        AddIPP(${projectName})
    endif()
endfunction(AddIPPIfRequired) 

# TBB

function(AddTBB projectName)
    include_directories(${COGRA_CONTRIB_DIR}/submodules/tbb/include)
    target_link_libraries(${projectName} PRIVATE tbb_static)
endfunction(AddTBB) 

function(AddTBBIfRequired contribLibs projectName)	
    list(FIND ${contribLibs} TBB found)
    if(NOT(${found} EQUAL -1))		
        AddTBB(${projectName})
    endif()
endfunction(AddTBBIfRequired)

# MKL

function(AddMKL projectName)
    include_directories(${MKL_INCLUDE_DIR})	
	message("${MKL_LIBRARIES}")
    target_link_libraries(${projectName} PRIVATE ${MKL_LIBRARIES})
endfunction(AddMKL) 

function(AddMKLIfRequired contribLibs projectName)	
    list(FIND ${contribLibs} MKL found)
    if(NOT(${found} EQUAL -1))		
        AddMKL(${projectName})
    endif()
endfunction(AddMKLIfRequired) 
# GLI

function(AddGLI)
	include_directories(${COGRA_CONTRIB_DIR}/submodules/gli/)
endfunction(AddGLI)

function(AddGLIIfRequired contribLibs)
	list(FIND ${contribLibs} GLI found)
    if(NOT(${found} EQUAL -1))
        AddGLI()
    endif()
endfunction(AddGLIIfRequired)

# Assimp

function(AddAssimp projectName)
    AddAssimpIncludes()
    target_link_libraries(${projectName} PRIVATE assimp IrrXML zlibstatic)
endfunction(AddAssimp)

function(AddAssimpIncludes)
    include_directories("${COGRA_CONTRIB_DIR}/submodules/assimp/include")
	include_directories("${ASSIMP_BUILD_INCLUDE_DIRECTORY}")
endfunction(AddAssimpIncludes)

function(AddAssimpIfRequired contribLibs projectName)
    list(FIND ${contribLibs} ASSIMP found)
    if(NOT(${found} EQUAL -1))
        AddAssimp(${projectName})
    endif()
endfunction(AddAssimpIfRequired)

# STBImage

function(AddStbImage)
    set(STB_IMAGE_VERSION 2.19)
	include_directories(${COGRA_CONTRIB_DIR}/stb_image/${STB_IMAGE_VERSION}/header)
endfunction(AddStbImage)

function(AddStbImageIfRequired contribLibs projectName)
	list(FIND ${contribLibs} STBIMAGE found)
    if(NOT(${found} EQUAL -1))
        AddStbImage()
    endif()
endfunction(AddStbImageIfRequired)

# OpenCL

function(AddOpenCL projectName)
	find_package(OpenCL REQUIRED)
	target_link_libraries(${projectName} PRIVATE OpenCL::OpenCL)
endfunction(AddOpenCL)

function(AddOpenCLIfRequired contribLibs projectName)
	list(FIND ${contribLibs} OPENCL found)
    if(NOT(${found} EQUAL -1))
        AddOpenCL(${projectName})
    endif()
endfunction(AddOpenCLIfRequired)

# OpenMP
function(AddOpenMP projectName)
    find_package(OpenMP)
    if(OpenMP_CXX_FOUND)	
		target_compile_options(${projectName} INTERFACE ${OpenMP_CXX_FLAGS})
        target_link_libraries(${projectName} PRIVATE OpenMP::OpenMP_CXX)
    endif()
endfunction(AddOpenMP)

function(AddOpenMPIfRequired contribLibs)
	list(FIND ${contribLibs} OPENMP found)
    if(NOT(${found} EQUAL -1))
        AddOpenMP(${projectName})
    endif()
endfunction(AddOpenMPIfRequired)

# Vulkan
function(AddVulkan projectName)
	find_package(Vulkan)
	if(Vulkan_FOUND)
		target_link_libraries(${projectName} PRIVATE Vulkan::Vulkan)
	endif()
endfunction(AddVulkan)

function(AddVulkanIfRequired contribLibs projectName)	
	list(FIND ${contribLibs} VULKAN found)
    if(NOT(${found} EQUAL -1))		
        AddVulkan(${projectName})
        
    endif()
endfunction(AddVulkanIfRequired)


function (AddContribLibraries contribLibs projectName)	
    AddGLFWIfRequired(${contribLibs} ${projectName})
    AddGLEWIfRequired(${contribLibs} ${projectName})
    AddGLMIfRequired(${contribLibs})
	AddGLIIfRequired(${contribLibs})
    AddCOGRAIfRequired(${contribLibs} ${projectName})
    AddIMGUIIfRequired(${contribLibs} ${projectName})
    AddTINYFD(${projectName})
    AddClip(${projectName})
	AddAssimpIfRequired(${contribLibs} ${projectName})
	AddStbImageIfRequired(${contribLibs} ${projectName})
    AddEIGENIfRequired(${contribLibs} ${projectName})
	AddVTUNEIfRequired(${contribLibs} ${projectName})
	AddIPPIfRequired(${contribLibs} ${projectName})
	AddTBBIfRequired(${contribLibs} ${projectName})
	AddMKLIfRequired(${contribLibs} ${projectName})
	AddOpenCLIfRequired(${contribLibs} ${projectName})
	AddVulkanIfRequired(${contribLibs} ${projectName})
    AddOpenMPIfRequired(${contribLibs} ${projectName})
	AddOpenGL(${projectName})	
	AddSPDLOG(${projectName})	
endfunction(AddContribLibraries)

function (CreateTest contribLibs projectName)
    # Find all shaders and add copy them to the run-time directory.
    file(GLOB_RECURSE SHADER_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.glsl *.vert *.geom *.cont *.eval *.frag)
    AddShaderFiles("${SHADER_SOURCE}" ${contribLibs})

    # Add all source files to the project.
    source_group("Shaders" FILES ${SHADER_SOURCE})

    # Find all C++ sources
    file(GLOB_RECURSE PROJECT_SOURCE *.cpp *.h *.c)	
    
    enable_testing()  
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})
    AddGTESTIncludeDirs()    
	target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main)
    add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
    add_definitions(-D_VARIADIC_MAX=10)	
    AddContribLibraries(${contribLibs} ${projectName})
endfunction(CreateTest)

function (AddDataDirectoryIfExists)
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/data)
		file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	endif()
endfunction(AddDataDirectoryIfExists)

function (CreateContribSourceGroup)	
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/contrib")
		file(GLOB_RECURSE CONTRIB_SOURCE  "${CMAKE_CURRENT_SOURCE_DIR}/contrib/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/contrib/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/contrib/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/contrib/*.hpp")
		message("${CONTRIB_SOURCE}")
		source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/contrib PREFIX "Contrib" FILES ${CONTRIB_SOURCE})			
	endif()
endfunction(CreateContribSourceGroup)


function(CreateApp contribLibs)
	AddDataDirectoryIfExists()
	#SetCompilerLinkerFlags()	
    # Find all shaders and add copy them to the run-time directory.
    file(GLOB_RECURSE SHADER_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.glsl *.vert *.geom *.cont *.eval *.frag)
	list(LENGTH SHADER_SOURCE numberOfShaderFiles)
    AddShaderFiles("${SHADER_SOURCE}" ${contribLibs})

    # Add all source files to the project.
    source_group("Shaders" FILES ${SHADER_SOURCE})	
    
    # Find all C++ sources
    file(GLOB_RECURSE PROJECT_SOURCE *.cpp *.h *.c)
    
    # Find files that end with _test.cpp.
	file(GLOB_RECURSE TEST_FILES  *_test.cpp)
    list(LENGTH TEST_FILES numberOfTestFiles)
    # If the project has files that end with _test.cpp a test target.
    if(NOT(${numberOfTestFiles} EQUAL 0))
      # By convention, the file ${PROJECT_NAME}.cpp must contain the projects main
      set(MainFileName ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.cpp)
      
      # Remove the test and the main file
      list(REMOVE_ITEM PROJECT_SOURCE ${TEST_FILES})
      list(REMOVE_ITEM PROJECT_SOURCE ${MainFileName})
      
      # Create application library
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}${OUTPUT_SUB_DIR})
      add_library(${PROJECT_NAME}_lib STATIC ${PROJECT_SOURCE} ${SHADER_SOURCE})
      add_executable(${PROJECT_NAME} ${MainFileName})
      target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
      
      # Create test and link application library
      enable_testing()  
      add_executable(${PROJECT_NAME}_test ${TEST_FILES})
      AddGTESTIncludeDirs()
      target_link_libraries(${PROJECT_NAME}_test PRIVATE gtest gtest_main ${PROJECT_NAME}_lib)
      add_test(${PROJECT_NAME}_test ${PROJECT_NAME}_test)
      add_definitions(-D_VARIADIC_MAX=10)
      set_target_properties(${PROJECT_NAME}_test PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
      set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
      AddContribLibraries(${contribLibs} ${PROJECT_NAME}_test)	
	  AddContribLibraries(${contribLibs} ${PROJECT_NAME}_lib)	

	  set_target_properties(${PROJECT_NAME}_test PROPERTIES FOLDER ${PROJECT_NAME})
	  set_target_properties(${PROJECT_NAME}_lib PROPERTIES FOLDER ${PROJECT_NAME})
	  set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
	  
	  set_target_properties(${PROJECT_NAME}_test PROPERTIES CXX_STANDARD 20)
	  set_target_properties(${PROJECT_NAME}_lib PROPERTIES CXX_STANDARD 20)
	  set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
	  if(NOT(${numberOfShaderFiles} EQUAL 0))
	    add_dependencies(${PROJECT_NAME}_lib ${PROJECT_NAME}_CopyResources)
	  endif()
    else()
	  CreateContribSourceGroup()
	  
      set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}${OUTPUT_SUB_DIR})
      add_executable(${PROJECT_NAME} ${PROJECT_SOURCE} ${SHADER_SOURCE})
      set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
	  set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)	  
	  if(NOT(${numberOfShaderFiles} EQUAL 0))
	    add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_CopyResources)
	  endif()

    endif()
    AddContribLibraries(${contribLibs} ${PROJECT_NAME}) 

endfunction(CreateApp)
