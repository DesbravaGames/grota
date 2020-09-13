
cmake_minimum_required(VERSION 2.8)
project(RawRGB)
add_executable(rawrgb main.c stb_image.h)

include_directories(${PROJECT_SOURCE_DIR})

target_link_libraries(rawrgb m)

