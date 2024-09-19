#version 330 core

out vec4 FragColor;     // Final output color

in vec3 ourColor;       // Color from the vertex shader
in vec2 TexCoords;      // Texture coordinates (if you want to use textures later)

void main() {
    // Set the fragment color based on the interpolated vertex color
    FragColor = vec4(ourColor, 1.0);
}