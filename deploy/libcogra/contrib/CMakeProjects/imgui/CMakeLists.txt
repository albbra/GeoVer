project(imgui)
file(GLOB PROJECT_SOURCE 
${CMAKE_CURRENT_SOURCE_DIR}/../../submodules/imgui/imgui/*.cpp 
${CMAKE_CURRENT_SOURCE_DIR}/../../submodules/imgui/imgui/misc/*.cpp)
add_library(imgui STATIC ${PROJECT_SOURCE})
