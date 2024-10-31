cmake_minimum_required(VERSION 3.30)

project(OpenGL_Learn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Dependence/glfw-3.4.bin.WIN64)
set(GLFW_INCLUDE_DIR ${GLFW_DIR}/include)
set(GLFW_LIBRARY_DIR ${GLFW_DIR}/lib-mingw-w64)
set(SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders)

# COPY SHADERS
file(COPY ${SHADERS_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "----------------- GLFW -----------------")
message(STATUS "GLFW_DIR: ${GLFW_DIR}")
message(STATUS "GLFW_INCLUDE_DIR: ${GLFW_INCLUDE_DIR}")
message(STATUS "GLFW_LIBRARY_DIR: ${GLFW_LIBRARY_DIR}")
message(STATUS "----------------- GLFW -----------------")

include_directories(
    "include"
    ${GLFW_INCLUDE_DIR}
)

link_directories(
    ${GLFW_LIBRARY_DIR}
)

add_executable(
    OpenGL_Learn 
    src/main.cpp
    src/glad.c
)

target_link_libraries(
    OpenGL_Learn
    glfw3
    opengl32
)