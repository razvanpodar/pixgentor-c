cmake_minimum_required(VERSION 3.10)

add_library(math
    math_vector2.c 
)

target_include_directories(math PUBLIC $(CMAKE_CURRENT_SOURCE_DIR)/include)

target_link_libraries(math glad)
