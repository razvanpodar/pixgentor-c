cmake_minimum_required(VERSION 3.10)

set(src 
    render_buffers
    render_shaders
    render_buffers
    render_shaders
)

set(inc 
    render_buffers.h
    render_shaders.h
)

add_library(render render_buffers.c render_shaders.c)

target_include_directories(render PUBLIC render)

target_link_libraries(render glad)
