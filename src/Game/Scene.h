#pragma once
#include "Renderer/Renderer.h"
#include "Shader/Shader.h"
#include "Renderer/Types/Mesh.hpp"
#include "Core/Camera.h"

#pragma once
#include <memory>
#include <glm/glm.hpp>

class Renderer;
class Shader;
class Mesh;
class Camera;

class Scene {
public:
    Scene();
    ~Scene();

    // Initialize scene-specific resources (e.g., shaders, meshes)
    void Init();

    // Update the scene (animations, physics, etc.)
    void Update(float deltaTime);

    // Render the scene using the renderer and camera
    void Render(Renderer& renderer, Camera& camera);

private:
    // Resources for the scene
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Mesh> m_Mesh;

    // Vertices and indices
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    glm::mat4 m_FixedRotation;

    // Other scene-specific variables (e.g., transformation matrices)
    glm::mat4 m_ModelMatrix;
};