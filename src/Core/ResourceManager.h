#include <memory>
#include <unordered_map>
#include <string>
#include "Texture.h"
#include "Mesh.hpp"

class ResourceManager {
public:
    ResourceManager() = default;

    std::shared_ptr<Texture> LoadTexture(const std::string& path) {
        auto texture = std::make_shared<Texture>(path);
        textures[path] = texture;
        return texture;
    }

    std::shared_ptr<Mesh> CreateMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices,
        unsigned int vertexOffset, unsigned int indexOffset, unsigned int indexCount) {
        auto mesh = std::make_shared<Mesh>(vertices, indices, vertexOffset, indexOffset, indexCount);
        meshes.push_back(mesh);
        return mesh;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    std::vector<std::shared_ptr<Mesh>> meshes;
};
