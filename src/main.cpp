// src/main.cpp
// Minimal OpenGL program that draws a single colored triangle.
// Uses GLFW for window/context creation and GLAD for loading OpenGL functions.
#include <glad/gl.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"

// Now you can use GLM types
glm::vec3 position(0.0f, 0.0f, 0.0f);
glm::mat4 projection =
    glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

// Callback to adjust the viewport when the window is resized.
void framebuffer_size_callback(GLFWwindow * /*window*/, int width, int height) {
  glViewport(0, 0, width, height);
}

// Simple error‑callback for GLFW (optional but helpful).
void glfw_error_callback(int error, const char *description) {
  std::cerr << "GLFW error (" << error << "): " << description << std::endl;
}

int main() {
  // ----- Initialise GLFW ------
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    std::cerr << "Failed to initialise GLFW\n";
    return -1;
  }

  // Request an OpenGL 3.3 core profile context
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // ----- Create window -----
  const int SCR_WIDTH = 800;
  const int SCR_HEIGHT = 600;
  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Triangle",
                                        nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // ----- Load OpenGL functions via GLAD -----
  if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
    std::cerr << "Failed to initialise GLAD\n";
    glfwTerminate();
    return -1;
  }

  // ----- Define triangle geometry -----
  // Each vertex: position (x,y,z) + color (r,g,b)
  float vertices[] = {
      // positions          // colors
      0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // top    (red)
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // left   (green)
      0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // right  (blue)
  };

  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  // Bind VAO first, then VBO and set attribute pointers
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute (location = 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        reinterpret_cast<void *>(0));
  glEnableVertexAttribArray(0);

  // Color attribute (location = 1)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        reinterpret_cast<void *>(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind for safety
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // ----- Compile shaders -----
  // The shaders are copied next to the executable by CMake,
  // so we can refer to them with a relative path.
  Shader ourShader("shaders/base.vert", "shaders/base.frag");

  // ----- Render loop -----
  while (!glfwWindowShouldClose(window)) {
    // Input: close window on ESC
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }

    // Clear the screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();

    // Rotate the triangle over time (rotate around Z axis)
    glm::mat4 model =
        glm::rotate(glm::mat4(1.0f), static_cast<float>(glfwGetTime()),
                    glm::vec3(0.0f, 0.0f, 1.0f));

    // View matrix: move camera backwards
    glm::mat4 view =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

    ourShader.setMat4("model", model);
    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // ----- Cleanup -----
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(ourShader.ID);

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
