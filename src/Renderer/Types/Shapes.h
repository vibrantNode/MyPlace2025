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



    static ShapeData createCubeMap(float size) {
        ShapeData shape;
        float halfWidth = size / 2.0f;

        float skyboxVertices[] = {
            // Coordinates
            -1000.0f, -1000.0f,  1000.0f,
             1000.0f, -1000.0f,  1000.0f,
             1000.0f, -1000.0f, -1000.0f,
            -1000.0f, -1000.0f, -1000.0f,
            -1000.0f,  1000.0f,  1000.0f,
             1000.0f,  1000.0f,  1000.0f,
             1000.0f,  1000.0f, -1000.0f,
            -1000.0f,  1000.0f, -1000.0f,
        };

        unsigned int skyboxIndices[] = {
            // Right
            1, 2, 6,
            6, 5, 1,
            // Left
            0, 4, 7,
            7, 3, 0,
            // Top
            4, 5, 6,
            6, 7, 4,
            // Bottom
            0, 3, 2,
            2, 1, 0,
            // Back
            0, 1, 5,
            5, 4, 0,
            // Front
            3, 7, 6,
            6, 2, 3,
        };
    };
};
