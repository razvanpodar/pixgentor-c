cmake_minimum_required(VERSION 3.10)

add_library(render
    render_buffers.c 
    render_shaders.c 
    render_viewport.c
    render_texture.c
)

target_include_directories(render PUBLIC $(CMAKE_CURRENT_SOURCE_DIR)/include)

target_link_libraries(render glad stb math)
