cmake_minimum_required(VERSION 3.20)

project(dull_engine_workspace LANGUAGES CXX)

# ============================================================
# Global Settings
# ============================================================

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories (works for single-config generators)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Default build type if not specified (for MinGW / Ninja)
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ============================================================
# Vendor Dependencies
# ============================================================

add_subdirectory(vendor/zutil)

# ============================================================
# Dull Engine (Static Library)
# ============================================================

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/*.hpp
)

add_library(dull_engine STATIC ${ENGINE_SOURCES})

target_include_directories(dull_engine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(dull_engine
    PUBLIC zutil
)

target_compile_options(dull_engine PRIVATE
    -Wall
    -Wextra
    $<$<CONFIG:Debug>:-g -O0>
    $<$<CONFIG:Release>:-O3 -Werror>
)

target_compile_definitions(dull_engine PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

# ============================================================
# Application
# ============================================================

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/app/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/app/*.hpp
)

add_executable(application ${APP_SOURCES})

target_include_directories(application
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(application
    PRIVATE dull_engine
)

target_compile_options(application PRIVATE
    -Wall
    -Wextra
    $<$<CONFIG:Debug>:-g -O0>
    $<$<CONFIG:Release>:-O3 -Werror>
)

target_compile_definitions(application PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

# ============================================================
# Raylib (Manual Windows Linking)
# ============================================================

# Adjust path if needed
set(RAYLIB_PATH "C:/raylib/raylib/src")

target_include_directories(application PRIVATE
    ${RAYLIB_PATH}
)

target_link_directories(application PRIVATE
    ${RAYLIB_PATH}
)

target_link_libraries(application PRIVATE
    raylib
    winmm
    gdi32
    opengl32
)
