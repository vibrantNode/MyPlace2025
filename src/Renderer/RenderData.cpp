#include "RenderData.h"
#include "Renderer/Renderer.h"
#include "Shader/Shader.h"
#include "Types/CubeMap.h"
#include "Renderer/Types/Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Types/Mesh.hpp"
#include <cmath>
#include <vector>
#include <stb_image.h>
#include "Types/Shapes.h"
#include "Common.h"
#include <random>



void RenderData::Init() {
   
    // Change the following to stack allocation
    // Initialize shaders
    m_Shader = std::make_unique<Shader>(
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.vert",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.frag"
    );
    // Load textures
    m_BoxTexture = std::make_unique<Texture>("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/AlienWall2.png");
    m_PlaneTexture = std::make_unique<Texture>("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/container2_specular.png");


    // Skybox textures
    std::vector<std::string> facesCubemap = {
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/SpaceSkybox/right.png",
         "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/SpaceSkybox/left.png",
         "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/SpaceSkybox/bot.png",
         "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/SpaceSkybox/top.png",
         "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/SpaceSkybox/front.png",
         "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/SpaceSkybox/back.png"
    };

    m_Skybox = std::make_unique<Skybox>(facesCubemap);

    // Initialize skybox shader
    m_SkyboxShader = std::make_unique<Shader>(
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/skybox.vert",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/skybox.frag"
    );


    std::vector<glm::mat4> boxModelMatrices(m_BoxInstanceCount);
    std::vector<glm::mat4> planeModelMatrices(m_PlaneInstanceCount);

    // Model instances
    // Create a random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<float> dis(-150.0f, 150.0f); // Increase the range for more spread

    // Box instances
    for (int i = 0; i < m_BoxInstanceCount; ++i) {
        // Apply random translations
        float randomX = dis(gen);
        float randomY = dis(gen);
        float randomZ = dis(gen);
        boxModelMatrices[i] = glm::translate(glm::mat4(1.0f), glm::vec3(randomX, randomY, randomZ));
    }

    // Plane instances
    for (int i = 0; i < m_PlaneInstanceCount; ++i) {
        // Apply random translations
        float randomX = dis(gen);
        float randomY = dis(gen) - 1.0f; // Shift downwards
        float randomZ = dis(gen);
        planeModelMatrices[i] = glm::translate(glm::mat4(1.0f), glm::vec3(randomX, randomY, randomZ));
    }

    // Set the model matrices for each mesh instance
    m_BoxMesh->SetInstanceModelMatrices(boxModelMatrices);
    m_PlaneMesh->SetInstanceModelMatrices(planeModelMatrices);
  
}

void RenderData::Update(float deltaTime) {
  

}
RenderData::RenderData() : m_Shader(nullptr) {

    // Generate shape data
    ShapeFactory::ShapeData cube = ShapeFactory::CreateCube(1.7f);
    ShapeFactory::ShapeData plane = ShapeFactory::CreatePlane(2.0f, 2.0f);
    ShapeFactory::ShapeData skyboxCube = ShapeFactory::CreateCube(1.0f);
   

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

    // Create Skybox Mesh object
    m_SkyboxMesh = std::make_unique<Mesh>(
        skyboxCube.vertices, skyboxCube.indices, 0, 0, skyboxCube.indices.size()
    );
}

void RenderData::Render(Renderer& renderer, Camera& camera) {
    // Calculate view and projection matrices
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), 1280.0f / 720.0f, 0.1f, 100.0f);

    // Skybox
     // Render Skybox
    glm::mat4 skyboxView = glm::mat4(glm::mat3(view)); // Remove translation from the view matrix
    m_SkyboxShader->Bind();
    m_SkyboxShader->SetUniformMat4f("view", skyboxView);
    m_SkyboxShader->SetUniformMat4f("projection", projection);
    renderer.DrawSkybox(*m_SkyboxMesh, *m_SkyboxShader);

    // Bind the shader and set the view and projection matrices
    m_Shader->Bind();
    m_Shader->SetUniformMat4f("view", view);
    m_Shader->SetUniformMat4f("projection", projection);

    // Bind the box mesh and render multiple instances using instanced rendering
    m_BoxMesh->Bind();
    m_BoxTexture->Bind();
    renderer.DrawInstanced({ m_BoxMesh.get() }, *m_Shader, m_BoxInstanceCount);  // Drawing the box instances

    // Bind the plane texture
    m_PlaneTexture->Bind();
    // Bind the plane mesh and render multiple instances using instanced rendering
    m_PlaneMesh->Bind();
    renderer.DrawInstanced({ m_PlaneMesh.get() }, *m_Shader, m_PlaneInstanceCount);  // Drawing the plane instances

    // Unbind the shader
    m_Shader->Unbind();
}





RenderData::~RenderData() {}


