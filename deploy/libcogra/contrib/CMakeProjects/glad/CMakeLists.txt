project(glad)
file(GLOB PROJECT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_library(glad STATIC ${PROJECT_SOURCE})
target_include_directories(glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)