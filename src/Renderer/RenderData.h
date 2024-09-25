#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "Renderer/Renderer.h"
#include "Shader/Shader.h"
#include "Renderer/Types/Mesh.hpp"
#include "Core/Camera.h"
#include "Texture.h"

class Renderer;
class Shader;
class Mesh;
class Camera;

class RenderData {
public:
    RenderData();
    ~RenderData();

    void Init();
    void Update(float deltaTime);
    void Render(Renderer& renderer, Camera& camera);

private:
    // Shaders
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Shader> m_LightingShader;
    std::unique_ptr<Shader> m_LightSourceShader;


    // Textures
    std::unique_ptr<Texture> m_PlaneTexture;
    std::unique_ptr<Texture> m_BoxTexture;
    std::unique_ptr<Texture> m_Specular;


    // Meshes
    std::unique_ptr<Mesh> m_BoxMesh;
    std::unique_ptr<Mesh> m_PlaneMesh;


    //Instances
    int m_PlaneInstanceCount = 500;
    int m_BoxInstanceCount = 500;
};
