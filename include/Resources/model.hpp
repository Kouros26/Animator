#pragma once
#include "resource.hpp"

#include <vector>

#include "assimp/scene.h"
#include "Rendering/OpenGL/mesh.hpp"

class Model : public IResource
{
public:
    Model();
    Model(const std::string& pPath);

    void Draw(const unsigned shaderProgram) const;

private:

    std::vector<Mesh> meshes;

    void LoadModel();
    void ProcessNode(const aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(const aiMaterial* mat, aiTextureType type, const std::string& name);
};
