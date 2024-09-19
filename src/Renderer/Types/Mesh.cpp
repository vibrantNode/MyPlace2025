#include "glad/glad.h"
#include "GLFW/glfw3.h"  
#include "Mesh.hpp"
#include <vector>



Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices,
    unsigned int vertexOffset, unsigned int indexOffset, unsigned int indexCount)
    : m_Vertices(vertices), m_Indices(indices), m_IndexOffset(indexOffset), m_IndexCount(indexCount) {

    SetupMesh();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Mesh::SetupMesh() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::Bind() const {
    glBindVertexArray(m_VAO);
}

void Mesh::Unbind() const {
    glBindVertexArray(0);
}

unsigned int Mesh::GetIndexCount() const {
    return m_IndexCount;
}

unsigned int Mesh::GetIndexOffset() const {
    return m_IndexOffset;
}
