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
    void Draw(const Mesh& mesh, const Shader& shader) const;
};
