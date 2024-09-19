
#version 330 core

layout (location = 0) in vec3 aPos;       // Position
layout (location = 1) in vec3 aColor;     // Color
layout (location = 2) in vec2 aTexCoords; // Texture coordinates

out vec3 ourColor;     // Pass color to the fragment shader
out vec2 TexCoords;    // Pass texture coordinates

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Transform the vertex position with model, view, and projection matrices
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
    // Pass the color and texture coordinates to the fragment shader
    ourColor = aColor;
    TexCoords = aTexCoords;
}