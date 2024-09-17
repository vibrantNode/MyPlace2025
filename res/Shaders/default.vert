#version 330 core

layout(location = 0) in vec3 aPos;    // Position of the vertex in 3D space
layout(location = 1) in vec2 aTexCoord; // UV coordinates

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPosition;  // Pass the position to the fragment shader
out vec2 TexCoord;

void main() {
    fragPosition = vec3(model * vec4(aPos, 1.0));  // World-space position
    TexCoord = aTexCoord;

    gl_Position = projection * view * vec4(fragPosition, 1.0);  // Transform into clip space
}