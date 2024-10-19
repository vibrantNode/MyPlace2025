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
class Skybox;

class RenderData {
public:
    RenderData();
    ~RenderData();

 

    struct DrawIndexedIndirectCommand {
        GLuint indexCount;    // Number of indices to draw
        GLuint instanceCount; // Number of instances
        GLuint firstIndex;    // Starting index in index buffer
        GLuint baseVertex;    // Base vertex offset
        GLuint baseInstance;  // Instance offset
    };

    void Init();
    void Update(float deltaTime);
    void Render(Renderer& renderer, Camera& camera);

    // Misc

   
private:
    // Shaders
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Shader> m_LightingShader;
    std::unique_ptr<Shader> m_LightSourceShader;
    std::unique_ptr<Shader> m_SkyboxShader;
    std::unique_ptr<Shader> m_WallShader;

    // Textures
    std::unique_ptr<Texture> m_PlaneTexture;
    std::unique_ptr<Texture> m_BoxTexture;
    std::unique_ptr<Texture> m_Specular;
    std::unique_ptr<Texture> m_SphereTexture;
    std::unique_ptr<Texture> m_RobinTexture;

    // Meshes
    std::unique_ptr<Mesh> m_BoxMesh;
    std::unique_ptr<Mesh> m_PlaneMesh;
    std::unique_ptr<Mesh> m_SkyboxMesh;
    std::unique_ptr<Mesh> m_SphereMesh;
    std::unique_ptr<Mesh> m_WallMesh;


    //Instances
    int m_PlaneInstanceCount = 1;
    int m_BoxInstanceCount = 500;
    int m_SphereInstanceCount = 700;
    int m_WallInstanceCount = 1500;


    // Misc
    std::vector<glm::mat4> boxModelMatrices; // Declare as a member variable
    std::vector<glm::mat4> wallModelMatrices;
    std::vector<glm::vec3> wallPositions;

    float rotationSpeed = 60.0f; // Degrees per second

  

    std::unique_ptr<Skybox> m_Skybox;

    // Multi draw indirect stuff
 
};






