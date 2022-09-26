cmake_minimum_required(VERSION 3.10)

add_subdirectory(render)

add_executable(pixgentor pixgentor.c)

target_link_libraries(pixgentor glfw glad stb render)
