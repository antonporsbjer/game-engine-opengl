#version 330 core

in vec3 fragColor;          // interpolated from vertex shader
out vec4 color;             // final fragment color

void main()
{
    color = vec4(fragColor, 1.0);
}

