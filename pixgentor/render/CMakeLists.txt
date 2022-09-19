cmake_minimum_required(VERSION 3.10)

add_library(render
    render_buffers.c 
    render_shaders.c 
    render_viewport.c
)

target_include_directories(render PUBLIC render)

target_link_libraries(render glad)
