
#ifndef SHADER_H
#define SHADER_H
#include "GLFW/glfw3.h"
#include <string>


class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    GLuint GetProgramID() const { return m_ProgramID; }

private:
    GLuint m_ProgramID;
    std::string ParseShader(const std::string& filePath);
    GLuint CompileShader(GLenum type, const std::string& source);
    void LinkShaders(GLuint vertexShader, GLuint fragmentShader);
};

#endif // SHADER_H
