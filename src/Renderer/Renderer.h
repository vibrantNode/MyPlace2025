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

    void Renderer::Draw(const std::vector<Mesh*>& meshes, const Shader& shader) const;

};