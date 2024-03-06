#pragma once
#include "resource.hpp"

#include <vector>

#include "assimp/scene.h"
#include "Renderer/OpenGL/mesh.hpp"

class Model : public IResource
{
public:
    Model();
    Model(const std::string& pPath);

    void Draw() const;
private:

    std::vector<Mesh> meshes;

    void LoadModel();
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);
};
