cmake_minimum_required(VERSION 3.20)

project(dull_engine_workspace LANGUAGES CXX)

# --- Global Settings ---

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)

# --- Vendor Dependencies ---

add_subdirectory(vendor/zutil)

# --- Dull Engine Static ---

file(GLOB_RECURSE ENGINE_SOURCES
    engine/*.cpp
    engine/*.hpp
)

add_library(dull_engine STATIC ${ENGINE_SOURCES})

target_include_directories(dull_engine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(dull_engine
    PUBLIC zutil
)

target_compile_options(dull_engine PRIVATE
    $<$<CONFIG:Debug>:-Wall -Wextra -g -O0>
)

target_compile_definitions(dull_engine PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_compile_options(dull_engine PRIVATE
    $<$<CONFIG:Release>:-Wall -Wextra -Werror -O3>
)

target_compile_definitions(dull_engine PRIVATE
    $<$<CONFIG:Release>:NDEBUG>
)

# --- Application ---

file(GLOB_RECURSE APP_SOURCES
    app/*.cpp
    app/*.hpp
)

add_executable(application ${APP_SOURCES})

target_include_directories(application
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(application
    PRIVATE
        dull_engine
)

# --- Raylib (Manual Windows Link – current setup) ---

target_link_directories(application PRIVATE
    "C:/raylib/raylib/src"
)

target_link_libraries(application PRIVATE
    raylib
    winmm
    gdi32
    opengl32
)

target_compile_options(application PRIVATE
    $<$<CONFIG:Debug>:-Wall -Wextra -g -O2>
)

target_compile_definitions(application PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_compile_options(application PRIVATE
    $<$<CONFIG:Release>:-Wall -Wextra -Werror -O3>
)

target_compile_definitions(application PRIVATE
    $<$<CONFIG:Release>:NDEBUG>
)
