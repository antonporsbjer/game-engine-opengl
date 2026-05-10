# Hello Triangle GL

A minimal OpenGL C++ project that renders a rotating, colored triangle. This repository serves as an introductory graphics application demonstrating window creation, OpenGL context initialization, shader compilation, and basic rendering loops.

## Technologies Used

This project is built using the following core technologies and libraries:

*   **C++17**: The primary programming language used for the application logic.
*   **CMake (3.10+)**: The build system generator used to configure and build the project across different platforms.
*   **OpenGL 3.3 (Core Profile)**: The cross-language, cross-platform API used for rendering 2D and 3D vector graphics.
*   **GLFW**: A multi-platform library for OpenGL, OpenGL ES, and Vulkan development on the desktop. It provides a simple API for creating windows, contexts, and handling input (keyboard, mouse, etc.).
*   **GLAD**: A multi-language GL/GLES/EGL/GLX/WGL loader-generator. It manages OpenGL function pointers and is used to load the OpenGL functions for the specific driver at runtime.
*   **GLM (OpenGL Mathematics)**: A header-only C++ mathematics library for graphics software. It is used here for computing mathematical operations like matrix transformations (model, view, and projection matrices).
*   **GLSL (OpenGL Shading Language)**: The C-style language used to write the vertex and fragment shaders (`.vert` and `.frag` files) that run directly on the GPU.

## Structure

*   `src/`: Contains the C++ source code (`main.cpp`, `shader.h`, etc.).
*   `shaders/`: Contains the GLSL vertex and fragment shaders.
*   `external/`: Contains third-party dependencies (GLAD, GLFW, GLM).
*   `CMakeLists.txt`: The main CMake build script.
