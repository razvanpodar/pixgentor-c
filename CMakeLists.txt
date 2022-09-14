cmake_minimum_required(VERSION 3.10)

project(pixgentor)

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glad)
add_subdirectory(pixgentor)

target_include_directories(pixgentor PUBLIC $(CMAKE_CURRENT_SOURCE_DIR)/thirdparty/glfw/include)
target_include_directories(pixgentor PUBLIC $(CMAKE_CURRENT_SOURCE_DIR)/thirdparty/glad/include)
target_include_directories(pixgentor PUBLIC $(CMAKE_CURRENT_SOURCE_DIR)/pixgentor/render)
