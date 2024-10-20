#pragma once
#include "Types/Mesh.hpp"
#include "Shader/shader.h"
#include "GLFW/glfw3.h"
#include <memory>
#include <glm/glm.hpp>

struct Ray {
    glm::vec3 origin;    // Starting point of the ray
    glm::vec3 direction; // Direction of the ray
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Clear() const;

    // Draws the skybox using the given mesh and shader
    void DrawSkybox(const Mesh& skyboxMesh, const Shader& shader) const;

    void DrawInstanced(const std::vector<Mesh*>& meshes, const Shader& shader, unsigned int instanceCount) const;
    void MultiDrawIndirectCommand() {}

    // Cast a ray along the Y-axis
    Ray CastRayY(const glm::vec3& origin, float length) const;

private:
    int instanceCount = 0;
};
