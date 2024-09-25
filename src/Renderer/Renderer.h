#pragma once
#include "Types/Mesh.hpp"
#include "Shader/shader.h"
#include "GLFW/glfw3.h"
#include <memory>


class Renderer {
public:
    Renderer();
    ~Renderer();

    void Clear() const;

    void Renderer::DrawInstanced(const std::vector<Mesh*>& meshes, const Shader& shader, unsigned int instanceCount) const;

private:
    int instanceCount = 100;
};