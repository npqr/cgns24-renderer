cmake_minimum_required(VERSION "3.16.3")

project(cgns24)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}/std:c++17")
endif(MSVC)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)

include_directories(includes)

if(WIN32)
  link_directories(lib)
endif()

add_executable(
  cgns24

  src/Main.cpp
  src/glad.c
)

target_link_libraries(
  cgns24 ${CMAKE_DL_LIBS}
)

if(WIN32)
  target_link_libraries(
    cgns24
    ${glfw_LIBRARIES}
  )
  target_link_libraries(cgns24 glfw3)
else()
  target_link_libraries(cgns24 glfw)
endif()