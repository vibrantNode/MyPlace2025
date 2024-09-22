#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <map>
#include "OpenGL/GLError.h"
#include "Renderer/Renderer.h"
#include "Renderer/Types/Mesh.hpp"
#include "Shader/Shader.h"

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



void Renderer::Draw(const std::vector<Mesh*>& meshes, const Shader& shader) const {
    GLCheckError();  // Error check before draw call

    shader.Bind();

    for (const Mesh* mesh : meshes) {
        mesh->Bind();
        glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, (void*)(mesh->GetIndexOffset() * sizeof(unsigned int)));
        
    }
    


    GLCheckError();  // Error check after draw call
}