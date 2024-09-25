#include "RenderData.h"
#include "Renderer/Renderer.h"
#include "Shader/Shader.h"
#include "Renderer/Types/Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Types/Mesh.hpp"
#include <cmath>
#include <vector>
#include <stb_image.h>
#include "Types/Shapes.h"
#include "Common.h"


void RenderData::Init() {
   
    
    // Initialize shaders
    m_Shader = std::make_unique<Shader>(
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.vert",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.frag"
    );
    // Load textures
    //m_BoxTexture = std::make_unique<Texture>("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/AlienWall2.png");
    m_PlaneTexture = std::make_unique<Texture>("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/AlienWall2.png");


    std::vector<glm::mat4> boxModelMatrices(m_BoxInstanceCount);
    std::vector<glm::mat4> planeModelMatrices(m_PlaneInstanceCount);

    // Generate model matrices for boxes
    for (int i = 0; i < m_BoxInstanceCount; ++i) {
        boxModelMatrices[i] = glm::translate(glm::mat4(1.0f), glm::vec3(i * 2.0f, 0.0f, 0.0f));  // Example translations
    }

    // For the plane, use a static model matrix
    for (int i = 0; i < m_PlaneInstanceCount; ++i) {
        planeModelMatrices[i] = glm::mat4(1.0f);  // Static for plane
    }

    // Set the model matrices for each mesh instance
    m_BoxMesh->SetInstanceModelMatrices(boxModelMatrices);
    m_PlaneMesh->SetInstanceModelMatrices(planeModelMatrices);
  
}

void RenderData::Update(float deltaTime) {
    // Update any animations, physics, etc. for the scene
}

void RenderData::Render(Renderer& renderer, Camera& camera) {
    // Calculate view and projection matrices
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), 1280.0f / 720.0f, 0.1f, 100.0f);

    // Bind the shader and set the view and projection matrices
    m_Shader->Bind();
    m_Shader->SetUniformMat4f("view", view);
    m_Shader->SetUniformMat4f("projection", projection);

    // Bind the box mesh and render multiple instances using instanced rendering
    m_BoxMesh->Bind();
    renderer.DrawInstanced({ m_BoxMesh.get() }, *m_Shader, m_BoxInstanceCount);  // Drawing the box instances

    // Bind the plane texture
    m_PlaneTexture->Bind();

    // Bind the plane mesh and render multiple instances using instanced rendering
    m_PlaneMesh->Bind();
    renderer.DrawInstanced({ m_PlaneMesh.get() }, *m_Shader, m_PlaneInstanceCount);  // Drawing the plane instances

    // Unbind the shader
    m_Shader->Unbind();
}
RenderData::RenderData() : m_Shader(nullptr) {

    // Generate shape data
    ShapeFactory::ShapeData cube = ShapeFactory::CreateCube(2.0f);
    ShapeFactory::ShapeData plane = ShapeFactory::CreatePlane(2.0f, 2.0f);

    // Offsets for vertex and index data (dynamic approach)
    size_t cubeVertexOffset = 0;
    size_t cubeIndexOffset = 0;
    size_t cubeIndexCount = cube.indices.size();

    // Combine the cube data and prepare offsets for the plane
    std::vector<float> combinedVertices = cube.vertices;  // Start with cube's vertices
    std::vector<unsigned int> combinedIndices = cube.indices;  // Start with cube's indices

    size_t planeVertexOffset = combinedVertices.size() / 8;  // Calculate vertex offset for plane
    size_t planeIndexOffset = combinedIndices.size();         // Calculate index offset for plane
    size_t planeIndexCount = plane.indices.size();

    // Append the plane data to the combined data
    combinedVertices.insert(combinedVertices.end(), plane.vertices.begin(), plane.vertices.end());
    combinedIndices.insert(combinedIndices.end(), plane.indices.begin(), plane.indices.end());

   

    // Create Cube Mesh object
    m_BoxMesh = std::make_unique<Mesh>(
        combinedVertices, combinedIndices, cubeVertexOffset, cubeIndexOffset, cubeIndexCount
    );

    // Create Plane Mesh object
    m_PlaneMesh = std::make_unique<Mesh>(
        combinedVertices, combinedIndices, planeVertexOffset, planeIndexOffset, planeIndexCount
    );
}





RenderData::~RenderData() {}


