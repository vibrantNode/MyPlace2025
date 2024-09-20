#include "Cubemap.h"
#include <iostream>
#include <glad/glad.h>
#include "stb_image.h"

Cubemap::Cubemap(const std::vector<std::string>& faces)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    LoadCubemap(faces);
}

void Cubemap::Bind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void Cubemap::LoadCubemap(const std::vector<std::string>& faces)
{
    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load texture: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
}
