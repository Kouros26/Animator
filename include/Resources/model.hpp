#pragma once
#include <map>

#include "resource.hpp"

#include <vector>

#include "Animation/boneInfo.hpp"
#include "assimp/scene.h"
#include "Rendering/OpenGL/mesh.hpp"

class Model : public IResource
{
public:
    Model();
    Model(const std::string& pPath);

    void Draw(const unsigned shaderProgram) const;

    std::map<std::string, BoneInfo>& GetBoneInfoMap();
    int& GetBoneCount();

private:

    std::vector<Mesh> meshes;
    std::map<std::string, BoneInfo> boneInfoMap;
    int boneCount = 0;

    void LoadModel();
    void ProcessNode(const aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(const aiMaterial* mat, aiTextureType type, const std::string& name);

    void SetVertexBoneData(Vertex& vertex, int boneId, float weight);
    void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
};
