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
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
   
    // Clear the screen (color buffer) and optionally the depth buffer
    GLCheckError();  // Checks for any OpenGL errors before execution
    glClearColor(0.1f, 3.1f, 3.1f, 3.3f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLCheckError();  // Checks for any OpenGL errors after execution
}



void Renderer::Draw(const Mesh& mesh, const Shader& shader) const
{
    GLCheckError();  // Error check before draw call

    // Bind the shader program
    shader.Bind();

    // Bind the mesh (vertex array object)
    mesh.Bind();

    // Draw the mesh with an index offset
    glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);

    // Unbind the mesh and shader for good practice

    GLCheckError();  // Error check after draw call
}

