#version 330 core

in vec3 fragPosition;   // Incoming world-space position
in vec2 TexCoord;

uniform float iTime;
uniform vec3 iResolution;  // Assuming iResolution is the screen resolution

out vec4 FragColor;

// Palette function
vec3 palette(float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);
    return a + b * cos(6.28318 * (c * t + d));
}

// Main shader function, adjusted for 3D
void main() {
    // Normalize the fragment position in world space to [-1, 1] space for UV mapping
    vec3 uv = fragPosition;
    
    // Scale the UV coordinates based on their world-space length
    vec3 uv0 = uv;
    vec3 finalColor = vec3(0.0);

    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;
        float d = length(uv) * exp(-length(uv0));

        // Compute the color using the palette function
        vec3 col = palette(length(uv0) + i * 0.4 + iTime * 0.4);

        d = sin(d * 8.0 + iTime) / 8.0;
        d = abs(d);
        d = pow(0.01 / d, 1.2);

        // Accumulate the color
        finalColor += col * d;
    }

    // Output the final color
    FragColor = vec4(finalColor, 1.0);
}