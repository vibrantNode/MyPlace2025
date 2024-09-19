#pragma once
#include "Renderer/Renderer.h"
#include "Shader/Shader.h"
#include "Renderer/Types/Mesh.hpp"
#include "Core/Camera.h"

#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Texture.h"

class Renderer;
class Shader;
class Mesh;
class Camera;

class Scene {
public:
    Scene();
    ~Scene();

    void Init();
    void Update(float deltaTime);
    void Render(Renderer& renderer, Camera& camera);

private:
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Mesh> m_BoxMesh;
    std::unique_ptr<Mesh> m_PlaneMesh;
   // std::unique_ptr<Texture> m_PlaneTexture; 
};