#include <vector>
#include <glm/glm.hpp>

#include <vector>
#include <glm/glm.hpp>

class ShapeFactory {
public:
    struct ShapeData {
        std::vector<float> vertices;  // Positions, colors, texture coordinates, and normals
        std::vector<unsigned int> indices;
    };

    // Generate a cube with position, color, texture coordinates, and normals
    static ShapeData CreateCube(float size) {
        ShapeData shape;

        float halfSize = size / 2.0f;

        // Vertices for a cube
        shape.vertices = {
            // Front face
            -halfSize, -halfSize,  halfSize,  -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   // bottom-left (red)
             halfSize, -halfSize,  halfSize,   0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   // bottom-right (green)
             halfSize,  halfSize,  halfSize,    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   // top-right (blue)
            -halfSize,  halfSize,  halfSize,   -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   // top-left (yellow)

            // Back face
            -halfSize, -halfSize, -halfSize,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom-left (purple)
             halfSize, -halfSize, -halfSize,    0.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom-right (cyan)
             halfSize,  halfSize, -halfSize,    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top-right (white)
            -halfSize,  halfSize, -halfSize,    0.5f, 0.5f, 0.5f,   0.0f, 1.0f,   // top-left (gray)

            // Left face
            -halfSize, -halfSize, -halfSize,    0.5f, 0.0f, 0.5f,   0.0f, 0.0f,   // bottom-left (pink)
            -halfSize, -halfSize,  halfSize,    0.0f, 0.5f, 0.5f,   1.0f, 0.0f,   // bottom-right (light blue)
            -halfSize,  halfSize,  halfSize,    0.5f, 1.0f, 0.0f,   1.0f, 1.0f,   // top-right (orange)
            -halfSize,  halfSize, -halfSize,    1.0f, 0.5f, 0.0f,   0.0f, 1.0f,   // top-left (dark yellow)

            // Right face
             halfSize, -halfSize, -halfSize,    1.0f, 0.0f, 0.5f,   0.0f, 0.0f,   // bottom-left (purple)
             halfSize, -halfSize,  halfSize,    0.0f, 0.5f, 1.0f,   1.0f, 0.0f,   // bottom-right (light blue)
             halfSize,  halfSize,  halfSize,    1.0f, 0.5f, 0.0f,   1.0f, 1.0f,   // top-right (orange)
             halfSize,  halfSize, -halfSize,    0.5f, 1.0f, 1.0f,   0.0f, 1.0f,   // top-left (light green)

             // Top face
             -halfSize,  halfSize, -halfSize,    0.5f, 0.0f, 0.0f,   0.0f, 0.0f,   // bottom-left (dark red)
             -halfSize,  halfSize,  halfSize,    0.0f, 0.5f, 0.0f,   1.0f, 0.0f,   // bottom-right (light green)
              halfSize,  halfSize,  halfSize,    0.0f, 0.0f, 0.5f,   1.0f, 1.0f,   // top-right (dark blue)
              halfSize,  halfSize, -halfSize,    1.0f, 0.5f, 0.5f,   0.0f, 1.0f,   // top-left (light pink)

              // Bottom face
              -halfSize, -halfSize, -halfSize,    0.5f, 0.0f, 0.5f,   0.0f, 1.0f,   // bottom-left (dark purple)
              -halfSize, -halfSize,  halfSize,    0.5f, 0.5f, 0.0f,   1.0f, 1.0f,   // bottom-right (light yellow)
               halfSize, -halfSize,  halfSize,    0.0f, 1.0f, 0.5f,   1.0f, 0.0f,   // top-right (light pink)
               halfSize, -halfSize, -halfSize,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // top-left (dark blue)
        };


        // Indices for the cube (two triangles per face)
        shape.indices = {
     // Front face
     0, 1, 2,  2, 3, 0,

     // Back face
     4, 5, 6,  6, 7, 4,

     // Left face
     8, 9, 10, 10, 11, 8,

     // Right face
     12, 13, 14, 14, 15, 12,

     // Top face
     16, 17, 18, 18, 19, 16,

     // Bottom face
     20, 21, 22, 22, 23, 20,
        };

        return shape;
    }

    // Generate a plane (XZ plane by default) with position, texture coords, and normals
    static ShapeData CreatePlane(float width, float depth) {
        ShapeData shape;

        float halfWidth = width / 2.0f;
        float halfDepth = depth / 2.0f;

        // Vertices for a plane
        shape.vertices = {
            // Position               // Color           // Texture coords 
            -halfWidth, 0.0f, -halfDepth,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  
             halfWidth, 0.0f, -halfDepth,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  
             halfWidth, 0.0f,  halfDepth,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,   
            -halfWidth, 0.0f,  halfDepth,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 
        };

        // Indices for a plane (two triangles)
        shape.indices = {
            0, 1, 2, 2, 3, 0
        };

        return shape;
    }

    // Generate a wall (XY plane by default) with position, texture coords, and normals
    static ShapeData CreateWall(float width, float height) {
        ShapeData shape;

        float halfWidth = width / 2.0f;
        float halfHeight = height / 2.0f;

        // Vertices for a wall
        shape.vertices = {
            // Position               // Color           // Texture coords 
            -halfWidth, -halfHeight, 0.0f,  -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   // bottom-left (red)
             halfWidth, -halfHeight, 0.0f,   0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   // bottom-right (green)
             halfWidth,  halfHeight, 0.0f,    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   // top-right (blue)
            -halfWidth,  halfHeight, 0.0f,   -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   // top-left (yellow)
        };


        // Indices for a wall (two triangles)
        shape.indices = {
            0, 1, 2, 2, 3, 0
        };

        return shape;
    }
};

/*
std::vector<float> combinedVertices = {
    // Box vertices (24 vertices for the box with unique colors at each point)

  -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,   // bottom-left (red)
0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom-right (green)
0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,   // top-right (blue)
-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,   // top-left (yellow)

// Back face
-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // bottom-left (purple)
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,   // bottom-right (cyan)
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,   // top-right (white)
-0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,  0.0f, 1.0f,   // top-left (gray)

// Left face
-0.5f, -0.5f, -0.5f,  0.5f, 0.0f, 0.5f,  0.0f, 0.0f,   // bottom-left (pink)
-0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.5f,  1.0f, 0.0f,   // bottom-right (light blue)
-0.5f,  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  1.0f, 1.0f,   // top-right (orange)
-0.5f,  0.5f, -0.5f,  1.0f, 0.5f, 0.0f,  0.0f, 1.0f,   // top-left (dark yellow)

// Right face
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.5f,  0.0f, 0.0f,   // bottom-left (purple)
 0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 1.0f,  1.0f, 0.0f,   // bottom-right (light blue)
 0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,  1.0f, 1.0f,   // top-right (orange)
 0.5f,  0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  0.0f, 1.0f,   // top-left (light green)

 // Top face
 -0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, 0.0f,   // bottom-left (dark red)
 -0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,  1.0f, 0.0f,   // bottom-right (light green)
  0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f,  1.0f, 1.0f,   // top-right (dark blue)
  0.5f,  0.5f, -0.5f,  1.0f, 0.5f, 0.5f,  0.0f, 1.0f,   // top-left (light pink)

  // Bottom face
  -0.5f, -0.5f, -0.5f,  0.5f, 0.0f, 0.5f,  0.0f, 1.0f,   // bottom-left (dark purple)
  -0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.0f,  1.0f, 1.0f,   // bottom-right (light yellow)
   0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.5f,  1.0f, 0.0f,   // top-right (light pink)
   0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,    // top-left (dark blue)

        -1.0f,  0.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,   // bottom-left (red)
 1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom-right (green)
 1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,   // top-right (blue)
-1.0f,  0.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // top-left (yellow)
};



std::vector<unsigned int> combinedIndices = {
    // Box indices (36 indices for the box)
    // Front face
    0, 1, 2,  2, 3, 0,

    // Back face
    4, 5, 6,  6, 7, 4,

    // Left face
    8, 9, 10, 10, 11, 8,

    // Right face
    12, 13, 14, 14, 15, 12,

    // Top face
    16, 17, 18, 18, 19, 16,

    // Bottom face
    20, 21, 22, 22, 23, 20,

    // Plane indices (6 indices for the plane)
    24, 25, 26, 26, 27, 24
};

// Offsets and counts
unsigned int boxVertexOffset = 0;        // The box vertices start at the beginning of the array
unsigned int boxIndexOffset = 0;         // The box indices start at the beginning
unsigned int boxIndexCount = 36;         // Number of indices for the box

// Each vertex now has 8 floats (3 for position, 3 for color, 2 for texture coordinates)
unsigned int planeVertexOffset = 24 * 8; // Offset after box vertices (24 vertices * 8 floats per vertex)
unsigned int planeIndexOffset = 36;      // Offset after the box indices
unsigned int planeIndexCount = 6;
*/