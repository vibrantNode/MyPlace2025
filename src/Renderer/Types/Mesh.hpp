#pragma once

#include <vector>


class Mesh {
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Bind() const;
    void Unbind() const;

    //int GetIndexCount() const { return m_Indices.size(); }

private:
    GLuint m_VAO, m_VBO, m_EBO;
    std::vector<float> m_Vertices;
    std::vector<unsigned int> m_Indices;

    void SetupMesh();
};