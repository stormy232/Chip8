cmake_minimum_required(VERSION 3.7)
project(Chip8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES src/main.cpp src/cpu.cpp src/SDL_PLATFORM.cpp)

add_executable(Chip8 ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS})
target_include_directories(Chip8 PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(Chip8 PRIVATE ${SDL2_LIBRARIES})
