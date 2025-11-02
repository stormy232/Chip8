cmake_minimum_required(VERSION 3.16)
project(Chip8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    src/main.cpp
    src/cpu.cpp
    src/SDL_PLATFORM.cpp
)

add_executable(Chip8 ${SOURCE_FILES})

# --- Platform specific configuration ---
if (WIN32)
    message(STATUS "Configuring SDL2 for Windows")

    # If using MSYS2, this works automatically:
    find_package(SDL2 REQUIRED)

    # Otherwise (manual install), uncomment and adjust:
    # set(SDL2_PATH "C:/SDKs/SDL2")
    # set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")
    # set(SDL2_LIBRARY_DIR "${SDL2_PATH}/lib/x64")

    target_include_directories(Chip8 PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(Chip8 PRIVATE ${SDL2_LIBRARIES})

    # Copy SDL2.dll automatically to the build output folder (optional)
    if(EXISTS "${SDL2_LIBRARY_DIR}/SDL2.dll")
        add_custom_command(TARGET Chip8 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_LIBRARY_DIR}/SDL2.dll"
            $<TARGET_FILE_DIR:Chip8>
        )
    endif()

elseif(UNIX)
    message(STATUS "Configuring SDL2 for Linux/macOS")

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)

    target_include_directories(Chip8 PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(Chip8 PRIVATE ${SDL2_LIBRARIES})
endif()
