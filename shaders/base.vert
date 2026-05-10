#version 330 core

layout (location = 0) in vec3 aPos;    // vertex position
layout (location = 1) in vec3 aColor;  // vertex color

out vec3 fragColor;                    // passed to fragment shader
uniform mat4 model;                   // model transformation matrix
uniform mat4 view;                    // view matrix (camera)
uniform mat4 projection;              // projection matrix

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    fragColor   = aColor;
}

