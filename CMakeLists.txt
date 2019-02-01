cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0072 NEW)

project(learnogl)

find_package(OpenGL)


add_subdirectory(glfw-3.2.1)
add_subdirectory(glm)

add_executable(ogl src/glad.c src/main.cc)

target_include_directories(ogl PUBLIC include)

target_link_libraries(ogl glfw glm_static OpenGL::OpenGL)
