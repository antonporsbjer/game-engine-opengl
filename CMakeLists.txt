cmake_minimum_required(VERSION 3.10)
project(HelloTriangle LANGUAGES C CXX)

# ----------------------------------------------------------------------
# Global compiler settings
# ----------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------------------------------------------------------------------
# GLAD (static library)
# ----------------------------------------------------------------------
add_library(glad STATIC
    external/glad/src/gl.c
)
target_include_directories(glad PUBLIC
    external/glad/include
)

# ----------------------------------------------------------------------
# GLFW (built from the git submodule)
# ----------------------------------------------------------------------
# The submodule lives in external/glfw.  We turn off its optional targets
# to keep the build fast.
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)   # <-- pulls in the submodule source

# ----------------------------------------------------------------------
# GLM (header-only math library)
# ----------------------------------------------------------------------
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE
    ${CMAKE_SOURCE_DIR}/external/glm
)

# ----------------------------------------------------------------------
# Main executable
# ----------------------------------------------------------------------
add_executable(hello_triangle
    src/main.cpp
    src/shader.h
)

target_include_directories(hello_triangle PRIVATE
    external/glad/include
    external/glfw/include
)

target_link_libraries(hello_triangle PRIVATE
    glad
    glfw
    glm
)

# ----------------------------------------------------------------------
# Copy shader files next to the binary (so the program can load them)
# ----------------------------------------------------------------------
add_custom_command(TARGET hello_triangle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:hello_triangle>/shaders
)

