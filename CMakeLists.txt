cmake_minimum_required(VERSION 2.6)
project(FreeSpace)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

set(CMAKE_C_FLAGS "-g -O2 -Wall -std=gnu11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(hashmap)
add_subdirectory(src)

add_executable(FreeSpace main.c)
target_link_libraries(FreeSpace src hashmap ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
