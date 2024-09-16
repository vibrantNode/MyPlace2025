#include "glad/glad.h"
#include "GLFW/glfw3.h"  
#include "Mesh.hpp"
#include <iostream>


Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
    : m_Vertices(vertices), m_Indices(indices) {

    // Initialize the mesh (set up VAO, VBO, and EBO)
    SetupMesh();
}

Mesh::~Mesh() {
    // Delete buffers when the mesh is destroyed
    
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Mesh::SetupMesh() {
    // Generate VAO, VBO, and EBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    // Bind the VAO (this will store the vertex attribute configuration)
    glBindVertexArray(m_VAO);

    // Bind the VBO and upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float), m_Vertices.data(), GL_STATIC_DRAW);

    // Bind the EBO and upload index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);

    // Set up vertex attributes (assuming the vertices are in the format [x, y, z])
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  // Enable the attribute at location 0 (position)

    // Unbind the VAO (to prevent accidental changes)
    glBindVertexArray(0);
}

void Mesh::Bind() const {
    // Bind the VAO (this binds the vertex attributes and index buffer)
    glBindVertexArray(m_VAO);
}

void Mesh::Unbind() const {
    // Unbind the VAO
    glBindVertexArray(0);
}
