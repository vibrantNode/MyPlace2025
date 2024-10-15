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

    // Textures
    std::unique_ptr<Texture> m_PlaneTexture;
    std::unique_ptr<Texture> m_BoxTexture;
    std::unique_ptr<Texture> m_Specular;
    std::unique_ptr<Texture> m_SphereTexture;


    // Meshes
    std::unique_ptr<Mesh> m_BoxMesh;
    std::unique_ptr<Mesh> m_PlaneMesh;
    std::unique_ptr<Mesh> m_SkyboxMesh;
    std::unique_ptr<Mesh> m_SphereMesh;


    //Instances
    int m_PlaneInstanceCount = 1;
    int m_BoxInstanceCount = 100;
    int m_SphereInstanceCount = 100;

    // Misc
    std::vector<glm::mat4> boxModelMatrices; // Declare as a member variable
   

    float rotationSpeed = 45.0f; // Degrees per second

  

    std::unique_ptr<Skybox> m_Skybox;

    // Multi draw indirect stuff
 
};






