#include "Scene.h"
#include "Renderer/Renderer.h"
#include "Shader/Shader.h"
#include "Renderer/Types/Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Types/Mesh.hpp"



Scene::Scene() : m_Shader(nullptr), m_Mesh(nullptr) {
    // Define vertices and indices for the scene's mesh
    vertices = {
        -0.5f,  0.5f, 0.0f,  // Vertex 1 (Top-left)
         0.5f,  0.5f, 0.0f,  // Vertex 2 (Top-right)
         0.5f, -0.5f, 0.0f,  // Vertex 3 (Bottom-right)
        -0.5f, -0.5f, 0.0f   // Vertex 4 (Bottom-left)
    };

    indices = {
        0, 1, 2,  // First triangle (Top-right triangle)
        2, 3, 0   // Second triangle (Bottom-left triangle)
    };
}

Scene::~Scene() {}

void Scene::Init() {
    // Initialize shaders
    m_Shader = std::make_unique<Shader>(
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.vert",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.frag"
    );

    
    m_Mesh = std::make_unique<Mesh>(vertices, indices);

    // Any other scene-specific initialization (e.g., textures, lights)
}

void Scene::Update(float deltaTime) {
    // Update any animations, physics, etc. for the scene
}

void Scene::Render(Renderer& renderer, Camera& camera) {
    // Set up model, view, and projection matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), 1280.0f / 720.0f, 0.1f, 100.0f);

    // Bind shader and set uniforms
    m_Shader->Bind();
    m_Shader->SetUniformMat4f("model", model);
    m_Shader->SetUniformMat4f("view", view);
    m_Shader->SetUniformMat4f("projection", projection);

    // Render the mesh
    renderer.Draw(*m_Mesh, *m_Shader);
}
