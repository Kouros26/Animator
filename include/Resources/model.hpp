#pragma once
#include "resource.hpp"

#include <vector>

#include "assimp/material.h"
#include "assimp/scene.h"
#include "Rendering/OpenGL/mesh.hpp"

class Model : public IResource
{
public:
    Model();
    Model(const std::string& pPath);
    Model(const std::string& pPath, const std::string& pTexturePath);

    void Draw(const unsigned shaderProgram) const;

    void AddMesh(const std::string& pPath);
    void AddMesh(const std::string& pPath, const std::string& pTexturePath);

    std::vector<Mesh>& GetMeshes();

private:

    std::vector<Mesh> meshes;

    void LoadModel(const std::string& pTexturePath = "");
    void ProcessNode(const aiNode* node, const aiScene* scene, const std::string& pPath);
    Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene, const std::string& pPath);
    std::vector<Texture> LoadMaterialTextures(const aiMaterial* mat, aiTextureType type, const std::string& name) const;
    void LoadTexture(const std::string& path);
};
