cmake_minimum_required(VERSION 3.10)

project(stb)

set(root ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_FILES ${root}/include/STB/stb_image.h)

add_library(stb ${INCLUDE_FILES} src/stb_image.c)

target_include_directories(stb PUBLIC include/)
