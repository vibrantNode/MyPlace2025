#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <map>
#include "OpenGL/GLError.h"
#include "Renderer/Renderer.h"
#include "Renderer/Types/Mesh.hpp"


Renderer::Renderer()
{
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set depth function (optional)
    glDepthFunc(GL_LESS);
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{

    // Clear the screen (color buffer) and optionally the depth buffer
    GLCheckError();  // Checks for any OpenGL errors before execution
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLCheckError();  // Checks for any OpenGL errors after execution
}



void Renderer::DrawInstanced(const std::vector<Mesh*>& meshes, const Shader& shader, unsigned int instanceCount) const {
    GLCheckError();  // Error check before draw call

    for (const Mesh* mesh : meshes) {
        mesh->Bind();
        glDrawElementsInstanced(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, (void*)(mesh->GetIndexOffset() * sizeof(unsigned int)), instanceCount);
        mesh->Unbind();
    }
    
    GLCheckError();  // Error check after draw call
}

// Skybox

void Renderer::DrawSkybox(const Mesh& skyboxMesh, const Shader& shader) const {
    GLCheckError();  // Error check before draw call

    // Disable depth writing for the skybox
    glDepthFunc(GL_LEQUAL);

    // Bind the skybox shader
    shader.Bind();

    // Bind the skybox mesh (cube) and render it
    skyboxMesh.Bind();
    glDrawElements(GL_TRIANGLES, skyboxMesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
    skyboxMesh.Unbind();

    // Restore depth function
    glDepthFunc(GL_LESS);

    shader.Unbind();
    GLCheckError();  // Error check after draw call
}