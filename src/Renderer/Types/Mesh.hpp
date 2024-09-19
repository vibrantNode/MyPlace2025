#pragma once
#include <vector>


class Mesh {
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices,
        unsigned int vertexOffset, unsigned int indexOffset, unsigned int indexCount);
    ~Mesh();
    void Bind() const;
    void Unbind() const;
    unsigned int GetIndexCount() const;
    unsigned int GetIndexOffset() const;

private:
    void SetupMesh();

    std::vector<float> m_Vertices;
    std::vector<unsigned int> m_Indices;
    unsigned int m_VAO, m_VBO, m_EBO;
    unsigned int m_IndexOffset;
    unsigned int m_IndexCount;
};