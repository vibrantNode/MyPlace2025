
#include "RenderData.h"
#include "Renderer/Renderer.h"
#include "Shader/Shader.h"
#include "Types/CubeMap.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer/Types/Mesh.hpp"
#include <cmath>
#include <vector>
#include <stb_image.h>
#include "Types/Shapes.h"
#include "Common.h"
#include <random>
#include <glm/gtc/matrix_transform.hpp>  // For matrix transforms like rotate, translate
#include <glm/gtc/constants.hpp> 


void RenderData::Init() {
   
    // Change the following to stack allocation
    // Initialize shaders
    m_Shader = std::make_unique<Shader>(
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.vert",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/default.frag"
    );

    m_WallShader = std::make_unique<Shader>(
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/robin.vert",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Shaders/robin.frag"
    );

    // Load textures
    m_BoxTexture = std::make_unique<Texture>("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/stoneWall.jpg");
    m_PlaneTexture = std::make_unique<Texture>("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/spaceFloor.jpg");
    m_SphereTexture = std::make_unique<Texture>("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/Robin1.jpg");
    m_RobinTexture = std::make_unique<Texture>("D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/mystical1.jpg");


    // Skybox textures
    std::vector<std::string> facesCubemap = { 

        // Cloudy skybox
       /* "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CloudySkybox/bluecloud_ft.jpg",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CloudySkybox/bluecloud_bk.jpg",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CloudySkybox/bluecloud_dn.jpg",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CloudySkybox/bluecloud_up.jpg",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CloudySkybox/bluecloud_rt.jpg",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CloudySkybox/bluecloud_lf.jpg",*/
      
        // Hell skybox
       /* "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CoolSkybox/NightSky_Front.png",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CoolSkybox/NightSky_Back.png",

         "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CoolSkybox/NightSky_Top.png",
         "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CoolSkybox/NightSky_Bottom.png",
       
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CoolSkybox/NightSky_Left.png",
        "D:/Users/Admin/source/repos/MyHell2024/MyHell2024/res/Textures/CoolSkybox/NightSky_Right.png",
      */


        // Space Skybox
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


   
    std::vector<glm::mat4> planeModelMatrices(m_PlaneInstanceCount);
    std::vector<glm::mat4> sphereModelMatrices(m_SphereInstanceCount);
    std::vector<glm::mat4> wallModelMatricies(m_WallInstanceCount);
    
    // Model instances
    // Create a random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<float> dis(-300.0f, 200.0f); // Increase the range for more spread

    // Box instances
    for (int i = 0; i < m_BoxInstanceCount; ++i) {
        // Apply random translations
        float randomX = dis(gen);
        float randomY = dis(gen);
        float randomZ = dis(gen);
        boxModelMatrices[i] = glm::translate(glm::mat4(1.0f), glm::vec3(randomX, randomY, randomZ));
        //boxModelMatrices[i] = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
    }

    // Plane instances
    for (int i = 0; i < m_PlaneInstanceCount; ++i) {
        // Apply random translations

        float explicitY = 15.0f;
        float randomX = dis(gen);
        float randomY = dis(gen) - 5.0f; // Shift downwards
        float randomZ = dis(gen);
        planeModelMatrices[i] = glm::translate(glm::mat4(1.0f), glm::vec3(randomX, explicitY, randomZ));
        planeModelMatrices[i] = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 100.0f));
    }

    // Sphere instances
    for (int i = 0; i < m_SphereInstanceCount; ++i) {
        float randomX = dis(gen);
        float randomY = dis(gen);
        float randomZ = dis(gen);
        sphereModelMatrices[i] = glm::translate(glm::mat4(1.0f), glm::vec3(randomX, randomY, randomZ));
    }

    // Wall Instances
    for (int i = 0; i < m_WallInstanceCount; i++) {
        float y = 30.0f;
        float randomX = dis(gen);
        float randomY = dis(gen) + 5.0f;
        float randomZ = dis(gen);
        wallModelMatricies[i] = glm::translate(glm::mat4(1.0f), glm::vec3(randomX , y , randomZ));

    }

    // Set the model matrices for each mesh instance
    m_BoxMesh->SetInstanceModelMatrices(boxModelMatrices);
    m_PlaneMesh->SetInstanceModelMatrices(planeModelMatrices);
    m_SphereMesh->SetInstanceModelMatrices(sphereModelMatrices);
    m_WallMesh->SetInstanceModelMatrices(wallModelMatricies);
}

void RenderData::Update(float deltaTime) {
    glm::vec3 rotationAxis(0.0f, 1.0f, 0.0f);
    float rotationSpeed = glm::radians(50.0f) * deltaTime;

    // Update box model matrices with rotation (this part is working as expected)
    for (int i = 0; i < m_BoxInstanceCount; ++i) {
        boxModelMatrices[i] = glm::rotate(boxModelMatrices[i], rotationSpeed, rotationAxis);
    }


    // Update the meshes with the new model matrices
    m_BoxMesh->SetInstanceModelMatrices(boxModelMatrices);
    
}


RenderData::RenderData() 
    : m_Shader(nullptr),
    m_WallShader(nullptr),
    boxModelMatrices(m_BoxInstanceCount, glm::mat4(1.0f)),
    wallModelMatrices(m_WallInstanceCount, glm::mat4(1.0f))
  
{

    // Generate shape data
    ShapeFactory::ShapeData cube = ShapeFactory::CreateCube(1.7f);
    ShapeFactory::ShapeData plane = ShapeFactory::CreatePlane(2.0f, 2.0f);
    ShapeFactory::ShapeData skyboxCube = ShapeFactory::CreateCube(1.0f);
    ShapeFactory::ShapeData sphere = ShapeFactory::CreateSphere(1.0f, 32, 32);
    ShapeFactory::ShapeData wall = ShapeFactory::CreateWall(5.0, 5.0);
    

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

    // Sphere offsets and data appending
    size_t sphereVertexOffset = combinedVertices.size() / 8;  // Sphere vertex offset
    size_t sphereIndexOffset = combinedIndices.size();        // Sphere index offset
    size_t sphereIndexCount = sphere.indices.size();

    combinedVertices.insert(combinedVertices.end(), sphere.vertices.begin(), sphere.vertices.end());
    combinedIndices.insert(combinedIndices.end(), sphere.indices.begin(), sphere.indices.end());

    // Wall offsets and data appending
    size_t wallVertexOffset = combinedVertices.size() / 8;
    size_t wallIndexOffset = combinedIndices.size();
    size_t wallIndexCount = wall.indices.size();

    combinedVertices.insert(combinedVertices.end(), wall.vertices.begin(), wall.vertices.end());
    combinedIndices.insert(combinedIndices.end(), wall.indices.begin(), wall.indices.end());


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

    // Create Sphere Mesh object
    m_SphereMesh = std::make_unique<Mesh>(
        combinedVertices, combinedIndices, sphereVertexOffset, sphereIndexOffset, sphereIndexCount
    );

    m_WallMesh = std::make_unique<Mesh>(
        combinedVertices, combinedIndices, wallVertexOffset, wallIndexOffset, wallIndexCount
    );
    
}

void RenderData::Render(Renderer& renderer, Camera& camera) {


    // Calculate view and projection matrices
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), 1280.0f / 720.0f, 0.1f, 1000.0f);

    // Skybox
    glm::mat4 skyboxView = glm::mat4(glm::mat3(view)); // Remove translation from the view matrix
    m_SkyboxShader->Bind();
    m_SkyboxShader->SetUniformMat4f("view", skyboxView);
    m_SkyboxShader->SetUniformMat4f("projection", projection);
  

    // Set uniforms in the shader
    m_SkyboxShader->Bind(); // Make sure to bind the shader first
   
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
    m_PlaneMesh->Bind();
    renderer.DrawInstanced({ m_PlaneMesh.get() }, *m_Shader, m_PlaneInstanceCount);  // Drawing the plane instances

    // Render the sphere instances
    m_SphereTexture->Bind();
    m_SphereMesh->Bind();
    renderer.DrawInstanced({ m_SphereMesh.get() }, *m_Shader, m_SphereInstanceCount);  // Draw sphere instances


    // Render the wall
    m_WallShader->Bind();
    m_WallShader->SetUniformMat4f("view", view);
    m_WallShader->SetUniformMat4f("projection", projection);
   

    // Get camera position
    glm::vec3 cameraPosition = camera.GetPosition();

    m_WallShader->SetUniform3f("cameraPos", cameraPosition.x, cameraPosition.y, cameraPosition.z);

    m_RobinTexture->Bind();
    m_WallMesh->Bind();
    renderer.DrawInstanced({ m_WallMesh.get() }, *m_WallShader, m_WallInstanceCount); // Draw robin

    // Unbind the shader
    m_Shader->Unbind();
}





RenderData::~RenderData() {}


