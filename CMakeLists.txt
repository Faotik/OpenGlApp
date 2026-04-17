cmake_minimum_required(VERSION 4.0)
include(FetchContent)

project(OpenGlApp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
        sdl3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.4
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(sdl3)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glm)

add_library(glad libs/glad/glad.c)
target_include_directories(glad
        PUBLIC
        libs/glad/include
)

add_executable(openglapp)

target_sources(openglapp
        PRIVATE
        src/app.cpp
        src/index_buffer.cpp
        src/shader.cpp
        src/vertex_attribute_object.cpp
        src/engine.cpp
        src/vertex_attribute_data.cpp
        src/compute_program.cpp
        src/main.cpp
        src/shader_program.cpp
        src/vertex_buffer.cpp
)

target_include_directories(openglapp
        PRIVATE
        src/
)

target_link_libraries(openglapp
        PRIVATE
        glad
        glm::glm
        SDL3::SDL3
)

set_target_properties(openglapp
        PROPERTIES
        DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

target_compile_options(openglapp PRIVATE
        -Wall
        -Wextra
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2

        -Wno-unused-parameter
)

target_compile_options(openglapp PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

target_link_options(openglapp PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)