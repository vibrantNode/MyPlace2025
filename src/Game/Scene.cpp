#include "Scene.h"
#include "Renderer/Renderer.h"
#include "Shader/Shader.h"
#include "Renderer/Types/Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Types/Mesh.hpp"
#include <cmath>
#include <vector>
#include <stb_image.h>


void Scene::Init() {
    // Initialize shaders
    m_Shader = std::make_unique<Shader>(
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.vert",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.frag"
    );
    // Load textures
    //m_BoxTexture = std::make_unique<Texture>("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/AlienWall2.png");
    m_PlaneTexture = std::make_unique<Texture>("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/AlienWall2.png");
    
}

void Scene::Update(float deltaTime) {
    // Update any animations, physics, etc. for the scene
}

void Scene::Render(Renderer& renderer, Camera& camera) {
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), 1280.0f / 720.0f, 0.1f, 100.0f);

    m_Shader->Bind();
    m_Shader->SetUniformMat4f("view", view);
    m_Shader->SetUniformMat4f("projection", projection);

    // Set up model matrices for each mesh
    // Example transformations
    glm::mat4 boxModel = glm::mat4(1.0f);
    boxModel = glm::translate(boxModel, glm::vec3(0.0f, 0.0f, 0.0f)); // Position
    boxModel = glm::scale(boxModel, glm::vec3(1.0f, 1.0f, 1.0f)); // Scale

    glm::mat4 planeModel = glm::mat4(1.0f);
    planeModel = glm::translate(planeModel, glm::vec3(0.0f, -1.0f, 0.0f)); // Position
    planeModel = glm::scale(planeModel, glm::vec3(10.0f, 1.0f, 10.0f)); // Scale

    // Render Box Mesh
    m_Shader->SetUniformMat4f("model", boxModel);
    renderer.Draw({ m_BoxMesh.get() }, *m_Shader); // Drawing the box

    // Render Plane Mesh
    m_PlaneTexture->Bind();

    m_Shader->SetUniformMat4f("model", planeModel);
    renderer.Draw({ m_PlaneMesh.get() }, *m_Shader); // Drawing the plane
}

Scene::Scene() : m_Shader(nullptr) {

  

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
    // Create Mesh objects
    m_BoxMesh = std::make_unique<Mesh>(
        combinedVertices, combinedIndices, boxVertexOffset, boxIndexOffset, boxIndexCount
    );

    m_PlaneMesh = std::make_unique<Mesh>(
        combinedVertices, combinedIndices, planeVertexOffset, planeIndexOffset, planeIndexCount
    );
}


Scene::~Scene() {}